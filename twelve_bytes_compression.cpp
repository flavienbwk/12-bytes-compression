#include "twelve_bytes_compression.h"
#include <math.h>

double Log2(double n) {  
    return log(n) / log(2);  
}  

/*
 * In case your number may be negative, put max_value at
 * its maximum absolute value. Then, you have to foresee
 * a 1 bit TbcNumber to know if your number is positive 
 * or negative.
 */

unsigned int* twelve_bytes_compression(TbcNumber* numbers, unsigned int size_numbers) {

    unsigned short max_bytes = 12; // SigFox twelve bytes
    unsigned int tbc_result[12] = { 0U };

    // Do your numbers enter inside 96 bits (12 bytes) ?
    printf("Determining arithmetic possibility...\n");

    unsigned int nb_bits = 0;
    unsigned int tmp_val_diff = 0;
    for (unsigned int c_numbers = 0; c_numbers < size_numbers; c_numbers++) {
        TbcNumber number = numbers[c_numbers];
        tmp_val_diff = number.max_value - number.min_value;
        nb_bits += (number.precision == 0) ? ceil(Log2(number.max_value)) : ceil(Log2(number.max_value * number.precision));
    }

    if (nb_bits > max_bytes * 8) {
        printf("%d bits out of %d maximum, cancelling.\n", nb_bits, max_bytes * 8);
        return tbc_result;
    }
    printf("Reached %d bits out of %d maximum, OK.\n\n", nb_bits, max_bytes * 8);

    printf("Determining optimized possibility...\n");
    // Looking for numbers bits summing 8 by 8.
    printf("Ignored for the moment.\n");

    return tbc_result;
}