#ifndef MD5_H
#define MD5_H

/* For uintX_t */
#include <stdint.h>

/* For size_t */
#include <stddef.h>


/* Prototypes */
void md5( const uint8_t *data, size_t len, uint8_t hash[16] );


#endif
