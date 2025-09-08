#ifndef BASE64_H
#define BASE64_H

/* For uintX_t */
#include <stdint.h>

/* For size_t */
#include <stddef.h>

/* For printf() */
#include <stdio.h> 

static const char BASE64[64] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static const int UNBASE64[132] = {
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 0-11
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 12-23
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 24-35
	-1, -1, -1, -1, -1, -1, -1, 62, -1, -1, -1, 63, // 36-47
	52, 53, 54, 55, 56, 57, 58, 59, 60, 61, -1, -2, // 48-59
	-1,  0, -1, -1, -1,  0,  1,  2,  3,  4,  5,  6, // 60-71
	7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, // 72-83
	19, 20, 21, 22, 23, 24, 25, -1, -1, -1, -1, -1, // 84-95
	-1, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, // 96-107
	37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, // 108-119
	49, 50, 51, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 120-131
};

void base64_encode( const uint8_t *data, size_t len, uint8_t *ciphertext );
int base64_decode( const uint8_t *ciphertext, size_t len, uint8_t *plaintext );

#endif
