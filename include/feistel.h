#ifndef FEISTEL_H
#define FEISTEL_H

/* For uintX_t */
#include <stdint.h>

/* For size_t */
#include <stddef.h>


/* Prototypes */
int feistel_encrypt( const uint8_t *plaintext, size_t len, uint8_t *ciphertext, const uint8_t *key, int rounds );


#endif
