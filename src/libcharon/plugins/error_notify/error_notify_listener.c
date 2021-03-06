/*
 * Copyright (C) 2012 Martin Willi
 * Copyright (C) 2012 revosec AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include "error_notify_listener.h"

#include <unistd.h>
#include <utils/process.h>
#include <daemon.h>
#include <config/child_cfg.h>

typedef struct private_error_notify_listener_t private_error_notify_listener_t;

/**
 * Private data of an error_notify_listener_t object.
 */
struct private_error_notify_listener_t {

	/**
	 * Public error_notify_listener_t interface.
	 */
	error_notify_listener_t public;

	/**
	 * Socket to send notifications over
	 */
	error_notify_socket_t *socket;
};


static void invoke_feedback(char *feedback_script,
	error_notify_msg_t *msg)
{
	FILE *shell;
	process_t *process;
	char *envp[128] = {};

	char connection[64];
	char type[32];
	char action[16];
	char *argv[5] = {feedback_script, action, connection, type, NULL};
	int out;

	snprintf(connection, sizeof(connection), "%s", msg->name);
	snprintf(type, sizeof(type), "%d", ntohl(msg->type));
	snprintf(action, sizeof(action), "ikev1_conn");

	process = process_start(argv, envp, NULL, &out, NULL, TRUE);
	if (process)
	{
		shell = fdopen(out, "r");
		if (shell)
		{
			while (TRUE)
			{
				char resp[128];

				if (fgets(resp, sizeof(resp), shell) == NULL)
				{
					if (ferror(shell))
					{
						DBG1(DBG_CHD, "error reading from feedback script");
					}
					break;
				}
				else
				{
					char *e = resp + strlen(resp);
					if (e > resp && e[-1] == '\n')
					{
						e[-1] = '\0';
					}
					DBG2(DBG_CHD, "feedback: %s", resp);
				}
			}
			fclose(shell);
		}
		else
		{
			close(out);
		}
		process->wait(process, NULL);
	}
}

METHOD(listener_t, alert, bool,
	private_error_notify_listener_t *this, ike_sa_t *ike_sa,
	alert_t alert, va_list args)
{
	error_notify_msg_t msg;
	message_t *message;
	host_t *host;
	identification_t *id;
	linked_list_t *list, *list2;
	peer_cfg_t *peer_cfg;
	certificate_t *cert;
	time_t not_before, not_after;

	memset(&msg, 0, sizeof(msg));

	switch (alert)
	{
		case ALERT_RADIUS_NOT_RESPONDING:
			msg.type = htonl(ERROR_NOTIFY_RADIUS_NOT_RESPONDING);
			snprintf(msg.str, sizeof(msg.str),
					 "a RADIUS request message timed out");
			break;
		case ALERT_LOCAL_AUTH_FAILED:
			msg.type = htonl(ERROR_NOTIFY_LOCAL_AUTH_FAILED);
			snprintf(msg.str, sizeof(msg.str),
					 "creating local authentication data failed");
			break;
		case ALERT_PEER_AUTH_FAILED:
			msg.type = htonl(ERROR_NOTIFY_PEER_AUTH_FAILED);
			snprintf(msg.str, sizeof(msg.str), "peer authentication failed");
			break;
		case ALERT_PARSE_ERROR_HEADER:
			msg.type = htonl(ERROR_NOTIFY_PARSE_ERROR_HEADER);
			message = va_arg(args, message_t*);
			snprintf(msg.str, sizeof(msg.str), "parsing IKE header from "
					 "%#H failed", message->get_source(message));
			break;
		case ALERT_PARSE_ERROR_BODY:
			msg.type = htonl(ERROR_NOTIFY_PARSE_ERROR_BODY);
			message = va_arg(args, message_t*);
			snprintf(msg.str, sizeof(msg.str), "parsing IKE message from "
					 "%#H failed", message->get_source(message));
			break;
		case ALERT_RETRANSMIT_SEND:
			msg.type = htonl(ERROR_NOTIFY_RETRANSMIT_SEND);
			snprintf(msg.str, sizeof(msg.str), "IKE message retransmission "
					 "number %u", va_arg(args, u_int));
			break;
		case ALERT_RETRANSMIT_SEND_TIMEOUT:
			msg.type = htonl(ERROR_NOTIFY_RETRANSMIT_SEND_TIMEOUT);
			snprintf(msg.str, sizeof(msg.str),
					 "IKE message retransmission timed out");
			break;
		case ALERT_HALF_OPEN_TIMEOUT:
			msg.type = htonl(ERROR_NOTIFY_HALF_OPEN_TIMEOUT);
			snprintf(msg.str, sizeof(msg.str), "IKE_SA timed out before it "
					 "could be established");
			break;
		case ALERT_PROPOSAL_MISMATCH_IKE:
			msg.type = htonl(ERROR_NOTIFY_PROPOSAL_MISMATCH_IKE);
			list = va_arg(args, linked_list_t*);
			snprintf(msg.str, sizeof(msg.str), "the received IKE_SA proposals "
					 "did not match: %#P", list);
			break;
		case ALERT_PROPOSAL_MISMATCH_CHILD:
			msg.type = htonl(ERROR_NOTIFY_PROPOSAL_MISMATCH_CHILD);
			list = va_arg(args, linked_list_t*);
			snprintf(msg.str, sizeof(msg.str), "the received CHILD_SA proposals "
					 "did not match: %#P", list);
			break;
		case ALERT_TS_MISMATCH:
			msg.type = htonl(ERROR_NOTIFY_TS_MISMATCH);
			list = va_arg(args, linked_list_t*);
			list2 = va_arg(args, linked_list_t*);
			snprintf(msg.str, sizeof(msg.str), "the received traffic selectors "
					 "did not match: %#R === %#R", list, list2);
			break;
		case ALERT_INSTALL_CHILD_SA_FAILED:
			msg.type = htonl(ERROR_NOTIFY_INSTALL_CHILD_SA_FAILED);
			snprintf(msg.str, sizeof(msg.str), "installing IPsec SA failed");
			break;
		case ALERT_INSTALL_CHILD_POLICY_FAILED:
			msg.type = htonl(ERROR_NOTIFY_INSTALL_CHILD_POLICY_FAILED);
			snprintf(msg.str, sizeof(msg.str), "installing IPsec policy failed");
			break;
		case ALERT_UNIQUE_REPLACE:
			msg.type = htonl(ERROR_NOTIFY_UNIQUE_REPLACE);
			snprintf(msg.str, sizeof(msg.str),
					 "replaced old IKE_SA due to uniqueness policy");
			break;
		case ALERT_UNIQUE_KEEP:
			msg.type = htonl(ERROR_NOTIFY_UNIQUE_KEEP);
			snprintf(msg.str, sizeof(msg.str), "keep existing in favor of "
					 "rejected new IKE_SA due to uniqueness policy");
			break;
		case ALERT_VIP_FAILURE:
			msg.type = htonl(ERROR_NOTIFY_VIP_FAILURE);
			list = va_arg(args, linked_list_t*);
			if (list->get_first(list, (void**)&host) == SUCCESS)
			{
				snprintf(msg.str, sizeof(msg.str),
					"allocating a virtual IP failed, requested was %H", host);
			}
			else
			{
				snprintf(msg.str, sizeof(msg.str),
					"expected a virtual IP request, but none found");
			}
			break;
		case ALERT_AUTHORIZATION_FAILED:
			msg.type = htonl(ERROR_NOTIFY_AUTHORIZATION_FAILED);
			snprintf(msg.str, sizeof(msg.str), "an authorization plugin "
					 "prevented establishment of an IKE_SA");
			break;
		case ALERT_CERT_EXPIRED:
			msg.type = htonl(ERROR_NOTIFY_CERT_EXPIRED);
			cert = va_arg(args, certificate_t*);
			cert->get_validity(cert, NULL, &not_before, &not_after);
			snprintf(msg.str, sizeof(msg.str), "certificate expired: '%Y' "
					 "(valid from %T to %T)", cert->get_subject(cert),
					 &not_before, TRUE, &not_after, TRUE);
			break;
		case ALERT_CERT_REVOKED:
			msg.type = htonl(ERROR_NOTIFY_CERT_REVOKED);
			cert = va_arg(args, certificate_t*);
			snprintf(msg.str, sizeof(msg.str), "certificate revoked: '%Y'",
					 cert->get_subject(cert));
			break;
		case ALERT_CERT_NO_ISSUER:
			msg.type = htonl(ERROR_NOTIFY_NO_ISSUER_CERT);
			cert = va_arg(args, certificate_t*);
			snprintf(msg.str, sizeof(msg.str), "no trusted issuer certificate "
					 "found: '%Y'", cert->get_issuer(cert));
			break;

		case ALERT_CHILDSA_ESTABLISHED:
			msg.type = htonl(ERROR_NOTIFY_CHILDSA_ESTABLISHED);
			snprintf(msg.str, sizeof(msg.str), "child SA established");
			break;
		case ALERT_WRONG_REMOTE_ID_IKEV1:
			msg.type = htonl(ERROR_NOTIFY_WRONG_REMOTE_ID_IKEV1);
			snprintf(msg.str, sizeof(msg.str), "remote ID mismatch");
			break;
		case ALERT_REMOTE_NOTIFY_AUTH_FAILED:
			msg.type = htonl(ERROR_NOTIFY_REMOTE_NOTIFY_AUTH_FAILED);
			snprintf(msg.str, sizeof(msg.str), "remote send auth failed");
			break;
		case ALERT_PROPOSAL_MISMATCH_IKEV1_IKE:
			msg.type = htonl(ERROR_NOTIFY_PROPOSAL_MISMATCH_IKEV1_IKE);
			snprintf(msg.str, sizeof(msg.str), "IKE no proposal chosen");
			break;
		case ALERT_PROPOSAL_MISMATCH_IKEV1_IPSEC:
			msg.type = htonl(ERROR_NOTIFY_PROPOSAL_MISMATCH_IKEV1_IPSEC);
			snprintf(msg.str, sizeof(msg.str), "IPsec no proposal chosen");
			break;
		case ALERT_NO_ROUTE:
			msg.type = htonl(ERROR_NOTIFY_NO_ROUTE);
			snprintf(msg.str, sizeof(msg.str), "no route to remote gateway");
			break;
		case ALERT_XAUTH_CLIENT_FAILED:
			msg.type = htonl(ERROR_NOTIFY_XAUTH_CLIENT_FAILED);
			snprintf(msg.str, sizeof(msg.str), "XAuth client auth was failed");
			break;
		case ALERT_XAUTH_SERVER_FAILED:
			msg.type = htonl(ERROR_NOTIFY_XAUTH_SERVER_FAILED);
			snprintf(msg.str, sizeof(msg.str), "XAuth server auth was failed");
			break;
		case ALERT_INVALID_TRAFFIC_SELECTORS_IKEV1:
			msg.type = htonl(ERROR_NOTIFY_INVALID_TRAFFIC_SELECTORS_IKEV1);
			snprintf(msg.str, sizeof(msg.str), "Invalid traffic selectors");
			break;

		case ALERT_PROPOSAL_MISMATCH_IKEV2_IKE:
			msg.type = htonl(ERROR_NOTIFY_PROPOSAL_MISMATCH_IKEV2_IKE);
			snprintf(msg.str, sizeof(msg.str), "IKEv2 proposal mismatch");
			break;
		case ALERT_PROPOSAL_MISMATCH_IKEV2_IPSEC:
			msg.type = htonl(ERROR_NOTIFY_PROPOSAL_MISMATCH_IKEV2_IPSEC);
			snprintf(msg.str, sizeof(msg.str), "IKEv2 Phase2 proposal mismatch");
			break;
		case ALERT_INVALID_TRAFFIC_SELECTORS_IKEV2:
			msg.type = htonl(ERROR_NOTIFY_INVALID_TRAFFIC_SELECTORS_IKEV2);
			snprintf(msg.str, sizeof(msg.str), "Invalid traffic selectors");
			break;
		case ALERT_INVALID_DH_GROUP_IKEV2_IPSEC:
			msg.type = htonl(ERROR_NOTIFY_INVALID_DH_GROUP_IKEV2_IPSEC);
			snprintf(msg.str, sizeof(msg.str), "Invalid DH group");
			break;
		case ALERT_CHILD_SA_FAILURE:
			msg.type = htonl(ERROR_NOTIFY_CHILD_SA_FAILURE);
			snprintf(msg.str, sizeof(msg.str), "CHILD_SA installation failure");
			break;

		case ALERT_INVALID_KEY:
			msg.type = htonl(ERROR_NOTIFY_INVALID_KEY);
			snprintf(msg.str, sizeof(msg.str), "Invalid key");
			break;

		case ALERT_PEER_ADDR_FAILED:
			msg.type = htonl(ERROR_NOTIFY_PEER_ADDRESS_FAILED);
			snprintf(msg.str, sizeof(msg.str), "Error in address resolving");
			break;

		case ALERT_GENERAL_ERROR:
			msg.type = htonl(ERROR_NOTIFY_GENERAL_ERROR);
			snprintf(msg.str, sizeof(msg.str), "General connection error");
			break;

		default:
			return TRUE;
	}

	if (ike_sa)
	{
		id = ike_sa->get_other_eap_id(ike_sa);
		if (id->get_type(id) != ID_ANY)
		{
			snprintf(msg.id, sizeof(msg.id), "%Y", id);
		}
		host = ike_sa->get_other_host(ike_sa);
		if (!host->is_anyaddr(host))
		{
			snprintf(msg.ip, sizeof(msg.ip), "%#H", host);
		}
		peer_cfg = ike_sa->get_peer_cfg(ike_sa);
		if (peer_cfg)
		{
			snprintf(msg.name, sizeof(msg.name), "%s",
					 peer_cfg->get_name(peer_cfg));
		}
	}

	if (this->socket->has_listeners(this->socket))
	{
		this->socket->notify(this->socket, &msg);
	}
	invoke_feedback("/tmp/ipsec/charon.feedback", &msg);

	return TRUE;
}

METHOD(error_notify_listener_t, destroy, void,
	private_error_notify_listener_t *this)
{
	free(this);
}

/**
 * See header
 */
error_notify_listener_t *error_notify_listener_create(error_notify_socket_t *s)
{
	private_error_notify_listener_t *this;

	INIT(this,
		.public = {
			.listener = {
				.alert = _alert,
			},
			.destroy = _destroy,
		},
		.socket = s,
	);

	return &this->public;
}
