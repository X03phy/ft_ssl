#pragma once

/* For uintX_t */
#include <stdint.h>

/* For size_t */
#include <stddef.h>


/* Prototypes */
void base64_encode( const uint8_t *data, size_t len, uint8_t *ciphertext );
int base64_decode( const uint8_t *ciphertext, size_t len, uint8_t *plaintext );
