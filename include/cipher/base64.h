#pragma once


/*
 * Includes
 */

#include <stdint.h>  // uintX_t
#include <stddef.h>  // size_t


/*
 * Prototypes
 */

/* cipher/algorithms/base64.c */
int base64_encode(uint8_t *ciphertext, const uint8_t *plaintext, const size_t len);
int base64_decode(uint8_t *plaintext, const size_t len, const uint8_t *ciphertext);
