#pragma once


/*
 * Includes
 */

#include <stdint.h>  // uintX_t
#include <stddef.h>  // size_t


/*
 * Prototypes
 */

int base64_encode(uint8_t *ciphertext, const size_t len, const uint8_t *plaintext);
int base64_decode(uint8_t *plaintext, const size_t len, const uint8_t *ciphertext);
