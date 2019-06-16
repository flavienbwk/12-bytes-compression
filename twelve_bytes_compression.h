#ifndef _TWELVE_BYTES_COMPRESSION_
#define _TWELVE_BYTES_COMPRESSION_

#include <stdio.h>
#include <cstdlib>

typedef struct      tbc_number {
    unsigned int    precision;
    unsigned int    max_value;
    unsigned int    min_value;
    unsigned int    value;
    unsigned int    bits;
    unsigned int    cmpt_value;
}                   TbcNumber;

double              Log2(double n);
unsigned int*       twelve_bytes_compression(TbcNumber* numbers, unsigned int size_numbers);

#endif /* _TWELVE_BYTES_COMPRESSION_ */