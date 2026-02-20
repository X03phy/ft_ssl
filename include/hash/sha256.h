#ifndef SHA256_H
#define SHA256_H

/* For uintX_t */
#include <stdint.h>

/* For size_t */
#include <stddef.h>


/* Prototypes */
void sha256( const uint8_t *data, size_t len, uint8_t hash[32] );


#endif
