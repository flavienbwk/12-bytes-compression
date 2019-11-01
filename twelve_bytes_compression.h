/**
 * @file twelve_bytes_compression.h
 * @author Flavien Berwick (flavien@berwick.fr)
 * @brief Algorithm for compressing digital values for SigFox frames of 12 bytes.
 * @version 0.1
 * @date 2019-06-17
 * 
 * Under MIT license. See the full license here :
 * https://github.com/flavienbwk/12-bytes-compression
 */

#ifndef _TWELVE_BYTES_COMPRESSION_
#define _TWELVE_BYTES_COMPRESSION_

#include <stdio.h>
#include <cstdlib>
#include <math.h>

#define ENABLE_VALUES_CHECKS    1  // Set it to 0 if you are SURE of the data to fasten the algorithm
#define ROUND_BOUND_HIGH        0  // If set to 1, won't throw an error if the value exceeds this bound
#define ROUND_BOUND_LOW         0  // If set to 1, won't throw an error if the value exceeds this bound

typedef struct      tbc_number {
    unsigned int    precision;
    unsigned int    max_value;
    unsigned int    min_value;
    unsigned int    value;
    unsigned int    bits;
    unsigned int    cmpt_value;
}                   TbcNumber;

double              Log2(double n);
void                tbc_struct_desc(TbcNumber number);
unsigned int        strbin_to_dec(char *str, unsigned int size);
unsigned int*       twelve_bytes_compression(TbcNumber* numbers, unsigned int size_numbers);

#endif /* _TWELVE_BYTES_COMPRESSION_ */