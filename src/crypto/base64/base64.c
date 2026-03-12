////#include "cipher/base64.h"

//#include <stddef.h>
//#include <stdint.h>
//#include <stdio.h>
//#include <stdbool.h>


///*
// * Macros
// */

//#define BASE64_PADDING '='


///*
// * Global variables
// */

//static const uint8_t BASE64[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

//static uint8_t UNBASE64[256] = {
//	[0 ... 255] = 0xFF,

//	['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,
//	['E'] = 4,  ['F'] = 5,  ['G'] = 6,  ['H'] = 7,
//	['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11,
//	['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15,
//	['Q'] = 16, ['R'] = 17, ['S'] = 18, ['T'] = 19,
//	['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23,
//	['Y'] = 24, ['Z'] = 25,

//	['a'] = 26, ['b'] = 27, ['c'] = 28, ['d'] = 29,
//	['e'] = 30, ['f'] = 31, ['g'] = 32, ['h'] = 33,
//	['i'] = 34, ['j'] = 35, ['k'] = 36, ['l'] = 37,
//	['m'] = 38, ['n'] = 39, ['o'] = 40, ['p'] = 41,
//	['q'] = 42, ['r'] = 43, ['s'] = 44, ['t'] = 45,
//	['u'] = 46, ['v'] = 47, ['w'] = 48, ['x'] = 49,
//	['y'] = 50, ['z'] = 51,

//	['0'] = 52, ['1'] = 53, ['2'] = 54, ['3'] = 55,
//	['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59,
//	['8'] = 60, ['9'] = 61,

//	['+'] = 62,
//	['/'] = 63
//};

///*
// * Functions
// */

//int base64_encode(uint8_t *ciphertext, const uint8_t *plaintext,
//	          const size_t len)
//{
//	size_t idx, i, j;

//	if (!ciphertext || !plaintext)
//		return (0);

//	if (len == 0) {
//		ciphertext[0] = '\0';
//		return (1);
//	}

//	idx = (len / 3) * 3;
//	for (i = 0, j = 0; i < idx; i += 3, j += 4) {
//		ciphertext[j] = BASE64[plaintext[i] >> 2];
//		ciphertext[j + 1] = BASE64[((plaintext[i] & 0x03) << 4) |
//		                           (plaintext[i + 1] >> 4)];
//		ciphertext[j + 2] = BASE64[((plaintext[i + 1] & 0x0F) << 2) |
//		                           (plaintext[i + 2] >> 6)];
//		ciphertext[j + 3] = BASE64[plaintext[i + 2] & 0x3F];
//	}

//	switch (len - i) {
//	case 1:
//		ciphertext[j] = BASE64[plaintext[i] >> 2];
//		ciphertext[j + 1] = BASE64[(plaintext[i] & 0x03) << 4];
//		ciphertext[j + 2] = BASE64_PADDING;
//		ciphertext[j + 3] = BASE64_PADDING;
//		j += 4;
//		break;
//	case 2:
//		ciphertext[j] = BASE64[plaintext[i] >> 2];
//		ciphertext[j + 1] = BASE64[((plaintext[i] & 0x03) << 4) |
//		                           (plaintext[i + 1] >> 4)];
//		ciphertext[j + 2] = BASE64[(plaintext[i + 1]  & 0x0F) << 2];
//		ciphertext[j + 3] = BASE64_PADDING;
//		j += 4;
//		break;
//	}

//	ciphertext[j] = '\0';
//	return (1);
//}


//int base64_decode(uint8_t *plaintext, const uint8_t *ciphertext,
//	          const size_t len)
//{
//	size_t i, j;
//	uint32_t block;
//	uint8_t b1, b2, b3, b4;

//	if (len == 0) {
//		plaintext[0] = '\0';
//		return (1);
//	}

//	if (len % 4)
//		return (0);

//	for (i = j = 0; i < len; i += 4) {
//		b1 = UNBASE64[ciphertext[i]];
//		b2 = UNBASE64[ciphertext[i + 1]];
//		b3 = UNBASE64[ciphertext[i + 2]];
//		b4 = UNBASE64[ciphertext[i + 3]];

//		block = (b1 << 18) | (b2 << 12) | (b3 << 6) | b4;

//		plaintext[j++] = (block >> 16) & 0xFF;
//		plaintext[j++] = (block >> 8) & 0xFF;
//		plaintext[j++] = block & 0xFF;
//	}

//	plaintext[j] = '\0';
//	return (1);
//}


//int main()
//{
//	uint8_t plaintext1[50] = "ab";
//	uint8_t plaintext2[50] = "abcdef";
//	uint8_t ciphertext1[50];
//	uint8_t ciphertext2[50];

//	base64_encode(ciphertext1, plaintext1, 2);
//	printf("%s\n", ciphertext1);
//	base64_encode(ciphertext2, plaintext2, 6);
//	printf("%s\n", ciphertext2);

//	uint8_t plaintext3[50];
//	uint8_t plaintext4[50];

//	base64_decode(plaintext3, ciphertext1, 4);
//	printf("%s\n", plaintext3);
//	base64_decode(plaintext4, ciphertext2, 8);
//	printf("%s\n", plaintext4);
//}
