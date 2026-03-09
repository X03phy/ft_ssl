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

static const uint8_t BASE64_DECODING_TABLE[128] = {
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,  // 0 - 15
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80,  // 16 - 31
	80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 80, 62, 80, 80, 80, 63,  // 32 - 47
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 80, 80, 80, 64, 80, 80,  // 48 - 63
	80,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,  // 64 - 79
	15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 80, 80, 80, 80, 80,  // 80 - 96
	80, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,  // 87 - 111
	41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 80, 80, 80, 80, 80   // 112 - 127
};

/*
 * Functions
 */

int base64_encode(uint8_t *ciphertext, const uint8_t *plaintext, const size_t len)
{
	size_t idx, i, j;

	if (!ciphertext || !plaintext)
		return (0);

	if (len == 0) {
		ciphertext[0] = '\0';
		return (1);
	}

	idx = (len / 3) * 3;
	for (i = 0, j = 0; i < idx; i += 3, j += 4) {
		ciphertext[j] = BASE64_ENCODING_TABLE[plaintext[i] >> 2];
		ciphertext[j + 1] = BASE64_ENCODING_TABLE[((plaintext[i] & 0x03) << 4) | (plaintext[i + 1] >> 4)];
		ciphertext[j + 2] = BASE64_ENCODING_TABLE[((plaintext[i + 1]  & 0x0F) << 2) | (plaintext[i + 2] >> 6)];
		ciphertext[j + 3] = BASE64_ENCODING_TABLE[plaintext[i + 2] & 0x3F];
	}

	switch (len - i) {
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


int base64_decode(uint8_t *plaintext, const uint8_t *ciphertext, const size_t len)
{
	size_t idx, i;
	bool    = false;

	if (len == 0) {
		plaintext[0] = '\0';
		return (1);
	}

	if (!((len >> 1) & 0x2)) {
		return (1);
	}

	if (ciphertext[len - 1] == BASE64_PADDING) {
		idx = (len / 4) * 4
	} else {
		idx = (len / 4) * 4
	}
	for (i = 0, i < len, i++) {

	}

}


int main()
{
	uint8_t plaintext1[] = "a";
	uint8_t plaintext2[] = "abcd";
	uint8_t ciphertext[50];
	base64_encode(ciphertext, plaintext1, 1);
	printf("%s\n", ciphertext);
	base64_encode(ciphertext, plaintext2, 4);
	printf("%s\n", ciphertext);
}
