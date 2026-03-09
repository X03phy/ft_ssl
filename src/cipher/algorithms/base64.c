//#include "cipher/base64.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>


/*
 * Macros
 */

#define BASE64_PADDING '='


/*
 * Global variables
 */

static const uint8_t BASE64_ENCODING_TABLE[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// static const int BASE64_DECODING_TABLE[132] = {
// 	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0-11
// 	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 12-23
// 	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 24-35
// 	-1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, // 36-47
// 	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -2, // 48-59
// 	-1,  0, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6, // 60-71
// 	7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, // 72-83
// 	19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // 84-95
// 	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, // 96-107
// 	37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, // 108-119
// 	49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 120-131
// };


/*
 * Functions
 */

int base64_encode(uint8_t *ciphertext, const uint8_t *plaintext, const size_t len)
{
	size_t idx, i, j;

	idx = (len / 3) * 3;
	for (i = 0, j = 0; i < idx; i += 3, j += 4) {
		ciphertext[j] = BASE64_ENCODING_TABLE[plaintext[i] >> 2];
		ciphertext[j + 1] = BASE64_ENCODING_TABLE[((plaintext[i] & 0x03) << 4) | (plaintext[i + 1] >> 4)];
		ciphertext[j + 2] = BASE64_ENCODING_TABLE[((plaintext[i + 1]  & 0x0F) << 2) | (plaintext[i + 2] >> 6)];
		ciphertext[j + 3] = BASE64_ENCODING_TABLE[plaintext[i + 2] & 0x3F];
	}

	switch (len % 3) {
	case 1:
		ciphertext[j] = BASE64_ENCODING_TABLE[plaintext[i] >> 2];
		ciphertext[j + 1] = BASE64_ENCODING_TABLE[(plaintext[i] & 0x03) << 4];
		ciphertext[j + 2] = BASE64_PADDING;
		ciphertext[j + 3] = BASE64_PADDING;
		j += 4;
		break;
	case 2:
		ciphertext[j] = BASE64_ENCODING_TABLE[plaintext[i] >> 2];
		ciphertext[j + 1] = BASE64_ENCODING_TABLE[((plaintext[i] & 0x03) << 4) | (plaintext[i + 1] >> 4)];
		ciphertext[j + 2] = BASE64_ENCODING_TABLE[(plaintext[i + 1]  & 0x0F) << 2];
		ciphertext[j + 3] = BASE64_PADDING;
		j += 4;
		break;
	}

	ciphertext[j] = '\0';
	return (1);
}


#include <string.h>
int main()
{
	uint8_t plaintext1[] = "a";
	uint8_t plaintext2[] = "ab";
	uint8_t ciphertext[50];
	base64_encode(ciphertext, plaintext1, 1);
	printf("%s\n", ciphertext);
	base64_encode(ciphertext, plaintext2, 2);
	printf("%s\n", ciphertext);
}
