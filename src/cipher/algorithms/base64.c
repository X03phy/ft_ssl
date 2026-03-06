#include "cipher/base64.h"


/*
 * Global variables
 */

 static const uint8_t BASE64_TABLE[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// static const int UNBASE64[132] = {
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
111111 00 0000 1111 11 000000

int base64_encode(uint8_t *ciphertext, const size_t len, const uint8_t *plaintext)
{
	size_t idx, i, j;

	idx = (len / 3) * 3;
	for (i = 0, j = 0; i < idx; i += 3, j += 4) {
		ciphertext[j] = BASE64[plaintext[i] >> 2];
		ciphertext[j + 1] = BASE64[((plaintext[i] & 0x03) << 4) | (plaintext[i + 1] >> 4)];
		ciphertext[j + 2] = BASE64[((plaintext[i + 1]  & 0x0F) << 2) | (plaintext[i + 2] >> 6)];
		ciphertext[j + 3] = BASE64[plaintext[i + 2] & 0x3F];
	}

	return (1);
}
