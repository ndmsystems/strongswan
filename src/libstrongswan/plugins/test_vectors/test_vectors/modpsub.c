/*
 * Copyright (C) 2015 Martin Willi
 * Copyright (C) 2015 revosec AG
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the Licenseor (at your
 * option) any later version.  See <http://www.fsf.org/copyleft/gpl.txt>.
 *
 * This program is distributed in the hope that it will be usefulbut
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 */

#include <crypto/crypto_tester.h>

/**
 * Test vectors from RFC5114
 */

dh_test_vector_t modp1024_160 = {
	.group = MODP_1024_160, .priv_len = 20, .pub_len = 128, .shared_len = 128,
	.priv_a	= "\xB9\xA3\xB3\xAE\x8F\xEF\xC1\xA2\x93\x04\x96\x50\x70\x86\xF8\x45"
			  "\x5D\x48\x94\x3E",
	.priv_b	= "\x93\x92\xC9\xF9\xEB\x6A\x7A\x6A\x90\x22\xF7\xD8\x3E\x72\x23\xC6"
			  "\x83\x5B\xBD\xDA",
	.pub_a	= "\x2A\x85\x3B\x3D\x92\x19\x75\x01\xB9\x01\x5B\x2D\xEB\x3E\xD8\x4F"
			  "\x5E\x02\x1D\xCC\x3E\x52\xF1\x09\xD3\x27\x3D\x2B\x75\x21\x28\x1C"
			  "\xBA\xBE\x0E\x76\xFF\x57\x27\xFA\x8A\xCC\xE2\x69\x56\xBA\x9A\x1F"
			  "\xCA\x26\xF2\x02\x28\xD8\x69\x3F\xEB\x10\x84\x1D\x84\xA7\x36\x00"
			  "\x54\xEC\xE5\xA7\xF5\xB7\xA6\x1A\xD3\xDF\xB3\xC6\x0D\x2E\x43\x10"
			  "\x6D\x87\x27\xDA\x37\xDF\x9C\xCE\x95\xB4\x78\x75\x5D\x06\xBC\xEA"
			  "\x8F\x9D\x45\x96\x5F\x75\xA5\xF3\xD1\xDF\x37\x01\x16\x5F\xC9\xE5"
			  "\x0C\x42\x79\xCE\xB0\x7F\x98\x95\x40\xAE\x96\xD5\xD8\x8E\xD7\x76",
	.pub_b	= "\x71\x7A\x6C\xB0\x53\x37\x1F\xF4\xA3\xB9\x32\x94\x1C\x1E\x56\x63"
			  "\xF8\x61\xA1\xD6\xAD\x34\xAE\x66\x57\x6D\xFB\x98\xF6\xC6\xCB\xF9"
			  "\xDD\xD5\xA5\x6C\x78\x33\xF6\xBC\xFD\xFF\x09\x55\x82\xAD\x86\x8E"
			  "\x44\x0E\x8D\x09\xFD\x76\x9E\x3C\xEC\xCD\xC3\xD3\xB1\xE4\xCF\xA0"
			  "\x57\x77\x6C\xAA\xF9\x73\x9B\x6A\x9F\xEE\x8E\x74\x11\xF8\xD6\xDA"
			  "\xC0\x9D\x6A\x4E\xDB\x46\xCC\x2B\x5D\x52\x03\x09\x0E\xAE\x61\x26"
			  "\x31\x1E\x53\xFD\x2C\x14\xB5\x74\xE6\xA3\x10\x9A\x3D\xA1\xBE\x41"
			  "\xBD\xCE\xAA\x18\x6F\x5C\xE0\x67\x16\xA2\xB6\xA0\x7B\x3C\x33\xFE",
	.shared	= "\x5C\x80\x4F\x45\x4D\x30\xD9\xC4\xDF\x85\x27\x1F\x93\x52\x8C\x91"
			  "\xDF\x6B\x48\xAB\x5F\x80\xB3\xB5\x9C\xAA\xC1\xB2\x8F\x8A\xCB\xA9"
			  "\xCD\x3E\x39\xF3\xCB\x61\x45\x25\xD9\x52\x1D\x2E\x64\x4C\x53\xB8"
			  "\x07\xB8\x10\xF3\x40\x06\x2F\x25\x7D\x7D\x6F\xBF\xE8\xD5\xE8\xF0"
			  "\x72\xE9\xB6\xE9\xAF\xDA\x94\x13\xEA\xFB\x2E\x8B\x06\x99\xB1\xFB"
			  "\x5A\x0C\xAC\xED\xDE\xAE\xAD\x7E\x9C\xFB\xB3\x6A\xE2\xB4\x20\x83"
			  "\x5B\xD8\x3A\x19\xFB\x0B\x5E\x96\xBF\x8F\xA4\xD0\x9E\x34\x55\x25"
			  "\x16\x7E\xCD\x91\x55\x41\x6F\x46\xF4\x08\xED\x31\xB6\x3C\x6E\x6D",
};

dh_test_vector_t modp2048_224 = {
	.group = MODP_2048_224, .priv_len = 28, .pub_len = 256, .shared_len = 256,
	.priv_a	= "\x22\xe6\x26\x01\xdb\xff\xd0\x67\x08\xa6\x80\xf7\x47\xf3\x61\xf7"
			  "\x6d\x8f\x4f\x72\x1a\x05\x48\xe4\x83\x29\x4b\x0c",
	.priv_b	= "\x4f\xf3\xbc\x96\xc7\xfc\x6a\x6d\x71\xd3\xb3\x63\x80\x0a\x7c\xdf"
			  "\xef\x6f\xc4\x1b\x44\x17\xea\x15\x35\x3b\x75\x90",
	.pub_a	= "\x1b\x3a\x63\x45\x1b\xd8\x86\xe6\x99\xe6\x7b\x49\x4e\x28\x8b\xd7"
			  "\xf8\xe0\xd3\x70\xba\xdd\xa7\xa0\xef\xd2\xfd\xe7\xd8\xf6\x61\x45"
			  "\xcc\x9f\x28\x04\x19\x97\x5e\xb8\x08\x87\x7c\x8a\x4c\x0c\x8e\x0b"
			  "\xd4\x8d\x4a\x54\x01\xeb\x1e\x87\x76\xbf\xee\xe1\x34\xc0\x38\x31"
			  "\xac\x27\x3c\xd9\xd6\x35\xab\x0c\xe0\x06\xa4\x2a\x88\x7e\x3f\x52"
			  "\xfb\x87\x66\xb6\x50\xf3\x80\x78\xbc\x8e\xe8\x58\x0c\xef\xe2\x43"
			  "\x96\x8c\xfc\x4f\x8d\xc3\xdb\x08\x45\x54\x17\x1d\x41\xbf\x2e\x86"
			  "\x1b\x7b\xb4\xd6\x9d\xd0\xe0\x1e\xa3\x87\xcb\xaa\x5c\xa6\x72\xaf"
			  "\xcb\xe8\xbd\xb9\xd6\x2d\x4c\xe1\x5f\x17\xdd\x36\xf9\x1e\xd1\xee"
			  "\xdd\x65\xca\x4a\x06\x45\x5c\xb9\x4c\xd4\x0a\x52\xec\x36\x0e\x84"
			  "\xb3\xc9\x26\xe2\x2c\x43\x80\xa3\xbf\x30\x9d\x56\x84\x97\x68\xb7"
			  "\xf5\x2c\xfd\xf6\x55\xfd\x05\x3a\x7e\xf7\x06\x97\x9e\x7e\x58\x06"
			  "\xb1\x7d\xfa\xe5\x3a\xd2\xa5\xbc\x56\x8e\xbb\x52\x9a\x7a\x61\xd6"
			  "\x8d\x25\x6f\x8f\xc9\x7c\x07\x4a\x86\x1d\x82\x7e\x2e\xbc\x8c\x61"
			  "\x34\x55\x31\x15\xb7\x0e\x71\x03\x92\x0a\xa1\x6d\x85\xe5\x2b\xcb"
			  "\xab\x8d\x78\x6a\x68\x17\x8f\xa8\xff\x7c\x2f\x5c\x71\x64\x8d\x6f",
	.pub_b	= "\x4d\xce\xe9\x92\xa9\x76\x2a\x13\xf2\xf8\x38\x44\xad\x3d\x77\xee"
			  "\x0e\x31\xc9\x71\x8b\x3d\xb6\xc2\x03\x5d\x39\x61\x18\x2c\x3e\x0b"
			  "\xa2\x47\xec\x41\x82\xd7\x60\xcd\x48\xd9\x95\x99\x97\x06\x22\xa1"
			  "\x88\x1b\xba\x2d\xc8\x22\x93\x9c\x78\xc3\x91\x2c\x66\x61\xfa\x54"
			  "\x38\xb2\x07\x66\x22\x2b\x75\xe2\x4c\x2e\x3a\xd0\xc7\x28\x72\x36"
			  "\x12\x95\x25\xee\x15\xb5\xdd\x79\x98\xaa\x04\xc4\xa9\x69\x6c\xac"
			  "\xd7\x17\x20\x83\xa9\x7a\x81\x66\x4e\xad\x2c\x47\x9e\x44\x4e\x4c"
			  "\x06\x54\xcc\x19\xe2\x8d\x77\x03\xce\xe8\xda\xcd\x61\x26\xf5\xd6"
			  "\x65\xec\x52\xc6\x72\x55\xdb\x92\x01\x4b\x03\x7e\xb6\x21\xa2\xac"
			  "\x8e\x36\x5d\xe0\x71\xff\xc1\x40\x0a\xcf\x07\x7a\x12\x91\x3d\xd8"
			  "\xde\x89\x47\x34\x37\xab\x7b\xa3\x46\x74\x3c\x1b\x21\x5d\xd9\xc1"
			  "\x21\x64\xa7\xe4\x05\x31\x18\xd1\x99\xbe\xc8\xef\x6f\xc5\x61\x17"
			  "\x0c\x84\xc8\x7d\x10\xee\x9a\x67\x4a\x1f\xa8\xff\xe1\x3b\xdf\xba"
			  "\x1d\x44\xde\x48\x94\x6d\x68\xdc\x0c\xdd\x77\x76\x35\xa7\xab\x5b"
			  "\xfb\x1e\x4b\xb7\xb8\x56\xf9\x68\x27\x73\x4c\x18\x41\x38\xe9\x15"
			  "\xd9\xc3\x00\x2e\xbc\xe5\x31\x20\x54\x6a\x7e\x20\x02\x14\x2b\x6c",
	.shared	= "\x34\xd9\xbd\xdc\x1b\x42\x17\x6c\x31\x3f\xea\x03\x4c\x21\x03\x4d"
			  "\x07\x4a\x63\x13\xbb\x4e\xcd\xb3\x70\x3f\xff\x42\x45\x67\xa4\x6b"
			  "\xdf\x75\x53\x0e\xde\x0a\x9d\xa5\x22\x9d\xe7\xd7\x67\x32\x28\x6c"
			  "\xbc\x0f\x91\xda\x4c\x3c\x85\x2f\xc0\x99\xc6\x79\x53\x1d\x94\xc7"
			  "\x8a\xb0\x3d\x9d\xec\xb0\xa4\xe4\xca\x8b\x2b\xb4\x59\x1c\x40\x21"
			  "\xcf\x8c\xe3\xa2\x0a\x54\x1d\x33\x99\x40\x17\xd0\x20\x0a\xe2\xc9"
			  "\x51\x6e\x2f\xf5\x14\x57\x79\x26\x9e\x86\x2b\x0f\xb4\x74\xa2\xd5"
			  "\x6d\xc3\x1e\xd5\x69\xa7\x70\x0b\x4c\x4a\xb1\x6b\x22\xa4\x55\x13"
			  "\x53\x1e\xf5\x23\xd7\x12\x12\x07\x7b\x5a\x16\x9b\xde\xff\xad\x7a"
			  "\xd9\x60\x82\x84\xc7\x79\x5b\x6d\x5a\x51\x83\xb8\x70\x66\xde\x17"
			  "\xd8\xd6\x71\xc9\xeb\xd8\xec\x89\x54\x4d\x45\xec\x06\x15\x93\xd4"
			  "\x42\xc6\x2a\xb9\xce\x3b\x1c\xb9\x94\x3a\x1d\x23\xa5\xea\x3b\xcf"
			  "\x21\xa0\x14\x71\xe6\x7e\x00\x3e\x7f\x8a\x69\xc7\x28\xbe\x49\x0b"
			  "\x2f\xc8\x8c\xfe\xb9\x2d\xb6\xa2\x15\xe5\xd0\x3c\x17\xc4\x64\xc9"
			  "\xac\x1a\x46\xe2\x03\xe1\x3f\x95\x29\x95\xfb\x03\xc6\x9d\x3c\xc4"
			  "\x7f\xcb\x51\x0b\x69\x98\xff\xd3\xaa\x6d\xe7\x3c\xf9\xf6\x38\x69",
};

dh_test_vector_t modp2048_256 = {
	.group = MODP_2048_256, .priv_len = 32, .pub_len = 256, .shared_len = 256,
	.priv_a	= "\x08\x81\x38\x2c\xdb\x87\x66\x0c\x6d\xc1\x3e\x61\x49\x38\xd5\xb9"
			  "\xc8\xb2\xf2\x48\x58\x1c\xc5\xe3\x1b\x35\x45\x43\x97\xfc\xe5\x0e",
	.priv_b	= "\x7d\x62\xa7\xe3\xef\x36\xde\x61\x7b\x13\xd1\xaf\xb8\x2c\x78\x0d"
			  "\x83\xa2\x3b\xd4\xee\x67\x05\x64\x51\x21\xf3\x71\xf5\x46\xa5\x3d",
	.pub_a	= "\x2e\x93\x80\xc8\x32\x3a\xf9\x75\x45\xbc\x49\x41\xde\xb0\xec\x37"
			  "\x42\xc6\x2f\xe0\xec\xe8\x24\xa6\xab\xdb\xe6\x6c\x59\xbe\xe0\x24"
			  "\x29\x11\xbf\xb9\x67\x23\x5c\xeb\xa3\x5a\xe1\x3e\x4e\xc7\x52\xbe"
			  "\x63\x0b\x92\xdc\x4b\xde\x28\x47\xa9\xc6\x2c\xb8\x15\x27\x45\x42"
			  "\x1f\xb7\xeb\x60\xa6\x3c\x0f\xe9\x15\x9f\xcc\xe7\x26\xce\x7c\xd8"
			  "\x52\x3d\x74\x50\x66\x7e\xf8\x40\xe4\x91\x91\x21\xeb\x5f\x01\xc8"
			  "\xc9\xb0\xd3\xd6\x48\xa9\x3b\xfb\x75\x68\x9e\x82\x44\xac\x13\x4a"
			  "\xf5\x44\x71\x1c\xe7\x9a\x02\xdc\xc3\x42\x26\x68\x47\x80\xdd\xdc"
			  "\xb4\x98\x59\x41\x06\xc3\x7f\x5b\xc7\x98\x56\x48\x7a\xf5\xab\x02"
			  "\x2a\x2e\x5e\x42\xf0\x98\x97\xc1\xa8\x5a\x11\xea\x02\x12\xaf\x04"
			  "\xd9\xb4\xce\xbc\x93\x7c\x3c\x1a\x3e\x15\xa8\xa0\x34\x2e\x33\x76"
			  "\x15\xc8\x4e\x7f\xe3\xb8\xb9\xb8\x7f\xb1\xe7\x3a\x15\xaf\x12\xa3"
			  "\x0d\x74\x6e\x06\xdf\xc3\x4f\x29\x0d\x79\x7c\xe5\x1a\xa1\x3a\xa7"
			  "\x85\xbf\x66\x58\xaf\xf5\xe4\xb0\x93\x00\x3c\xbe\xaf\x66\x5b\x3c"
			  "\x2e\x11\x3a\x3a\x4e\x90\x52\x69\x34\x1d\xc0\x71\x14\x26\x68\x5f"
			  "\x4e\xf3\x7e\x86\x8a\x81\x26\xff\x3f\x22\x79\xb5\x7c\xa6\x7e\x29",
	.pub_b	= "\x57\x5f\x03\x51\xbd\x2b\x1b\x81\x74\x48\xbd\xf8\x7a\x6c\x36\x2c"
			  "\x1e\x28\x9d\x39\x03\xa3\x0b\x98\x32\xc5\x74\x1f\xa2\x50\x36\x3e"
			  "\x7a\xcb\xc7\xf7\x7f\x3d\xac\xbc\x1f\x13\x1a\xdd\x8e\x03\x36\x7e"
			  "\xff\x8f\xbb\xb3\xe1\xc5\x78\x44\x24\x80\x9b\x25\xaf\xe4\xd2\x26"
			  "\x2a\x1a\x6f\xd2\xfa\xb6\x41\x05\xca\x30\xa6\x74\xe0\x7f\x78\x09"
			  "\x85\x20\x88\x63\x2f\xc0\x49\x23\x37\x91\xad\x4e\xdd\x08\x3a\x97"
			  "\x8b\x88\x3e\xe6\x18\xbc\x5e\x0d\xd0\x47\x41\x5f\x2d\x95\xe6\x83"
			  "\xcf\x14\x82\x6b\x5f\xbe\x10\xd3\xce\x41\xc6\xc1\x20\xc7\x8a\xb2"
			  "\x00\x08\xc6\x98\xbf\x7f\x0b\xca\xb9\xd7\xf4\x07\xbe\xd0\xf4\x3a"
			  "\xfb\x29\x70\xf5\x7f\x8d\x12\x04\x39\x63\xe6\x6d\xdd\x32\x0d\x59"
			  "\x9a\xd9\x93\x6c\x8f\x44\x13\x7c\x08\xb1\x80\xec\x5e\x98\x5c\xeb"
			  "\xe1\x86\xf3\xd5\x49\x67\x7e\x80\x60\x73\x31\xee\x17\xaf\x33\x80"
			  "\xa7\x25\xb0\x78\x23\x17\xd7\xdd\x43\xf5\x9d\x7a\xf9\x56\x8a\x9b"
			  "\xb6\x3a\x84\xd3\x65\xf9\x22\x44\xed\x12\x09\x88\x21\x93\x02\xf4"
			  "\x29\x24\xc7\xca\x90\xb8\x9d\x24\xf7\x1b\x0a\xb6\x97\x82\x3d\x7d"
			  "\xeb\x1a\xff\x5b\x0e\x8e\x4a\x45\xd4\x9f\x7f\x53\x75\x7e\x19\x13",
	.shared	= "\x86\xc7\x0b\xf8\xd0\xbb\x81\xbb\x01\x07\x8a\x17\x21\x9c\xb7\xd2"
			  "\x72\x03\xdb\x2a\x19\xc8\x77\xf1\xd1\xf1\x9f\xd7\xd7\x7e\xf2\x25"
			  "\x46\xa6\x8f\x00\x5a\xd5\x2d\xc8\x45\x53\xb7\x8f\xc6\x03\x30\xbe"
			  "\x51\xea\x7c\x06\x72\xca\xc1\x51\x5e\x4b\x35\xc0\x47\xb9\xa5\x51"
			  "\xb8\x8f\x39\xdc\x26\xda\x14\xa0\x9e\xf7\x47\x74\xd4\x7c\x76\x2d"
			  "\xd1\x77\xf9\xed\x5b\xc2\xf1\x1e\x52\xc8\x79\xbd\x95\x09\x85\x04"
			  "\xcd\x9e\xec\xd8\xa8\xf9\xb3\xef\xbd\x1f\x00\x8a\xc5\x85\x30\x97"
			  "\xd9\xd1\x83\x7f\x2b\x18\xf7\x7c\xd7\xbe\x01\xaf\x80\xa7\xc7\xb5"
			  "\xea\x3c\xa5\x4c\xc0\x2d\x0c\x11\x6f\xee\x3f\x95\xbb\x87\x39\x93"
			  "\x85\x87\x5d\x7e\x86\x74\x7e\x67\x6e\x72\x89\x38\xac\xbf\xf7\x09"
			  "\x8e\x05\xbe\x4d\xcf\xb2\x40\x52\xb8\x3a\xef\xfb\x14\x78\x3f\x02"
			  "\x9a\xdb\xde\x7f\x53\xfa\xe9\x20\x84\x22\x40\x90\xe0\x07\xce\xe9"
			  "\x4d\x4b\xf2\xba\xce\x9f\xfd\x4b\x57\xd2\xaf\x7c\x72\x4d\x0c\xaa"
			  "\x19\xbf\x05\x01\xf6\xf1\x7b\x4a\xa1\x0f\x42\x5e\x3e\xa7\x60\x80"
			  "\xb4\xb9\xd6\xb3\xce\xfe\xa1\x15\xb2\xce\xb8\x78\x9b\xb8\xa3\xb0"
			  "\xea\x87\xfe\xbe\x63\xb6\xc8\xf8\x46\xec\x6d\xb0\xc2\x6c\x5d\x7c",
};
