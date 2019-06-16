#include "twelve_bytes_compression.h"
#include <math.h>

double Log2(double n)
{
    return log(n) / log(2);
}

/*
 * Describes a TbcNumber struct for debugging purpose.
 */
void tbc_struct_desc(TbcNumber number)
{
    printf("[TbcNumber] precision: %d, max_value: %d, min_value: %d, value: %d\n", number.precision, number.max_value, number.min_value, number.value);
    return;
}

/*
 * In case your number may be negative, put max_value at
 * its maximum absolute value. Then, you have to foresee
 * a 1 bit TbcNumber to know if your number is positive 
 * or negative.
 */
unsigned int *twelve_bytes_compression(TbcNumber *numbers, unsigned int size_numbers)
{

    unsigned short max_bytes = 12; // SigFox maximum payload size
    unsigned int tbc_result[12] = {0U};

    // Do your numbers enter inside 96 bits (12 bytes) ?
    printf("Checking arithmetic validity...\n");

    unsigned int total_nb_bits = 0;
    unsigned int tmp_val_diff = 0;
    for (unsigned int c_numbers = 0; c_numbers < size_numbers; c_numbers++)
    {
        TbcNumber number = numbers[c_numbers];
        tmp_val_diff = number.max_value - number.min_value;
        // Checking maximum validity
        if (number.precision % 2 != 0)
        {
            printf("You set a precision of %d, precisions must be multiples of 2. Ignoring.\n", number.precision);
            tbc_struct_desc(number);
            number.precision = 0;
        }
        number.bits = (number.precision == 0) ? ceil(Log2(number.max_value)) : ceil(Log2(number.max_value * number.precision));
        total_nb_bits += number.bits;
        // Checking current value validity
        if (number.precision == 0)
        {
            if (!(number.value <= number.max_value && number.value >= number.min_value))
            {
                printf("%d is not between %d and %d, stopping.\n", number.value, number.min_value, number.max_value);
                tbc_struct_desc(number);
                return tbc_result;
            }
        }
        else
        {
            unsigned int tmp_cmpt_val = ceil(number.value * number.precision / 10);
            if (tmp_cmpt_val < number.min_value || tmp_cmpt_val > pow(2, number.bits) - 1)
            {
                printf("%d is not between %d and %d, stopping.\n", tmp_cmpt_val, number.min_value, pow(2, number.bits) - 1);
                tbc_struct_desc(number);
                return tbc_result;
            }
            number.cmpt_value = tmp_cmpt_val;
        }
    }

    if (total_nb_bits > max_bytes * 8)
    {
        printf("%d bits out of %d maximum, stopping.\n", total_nb_bits, max_bytes * 8);
        return tbc_result;
    }
    printf("Reached %d bits out of %d maximum, OK.\n", total_nb_bits, max_bytes * 8);
    printf("This payload will use %d bytes.\n\n", (1 + ((total_nb_bits - 1) / 8U)));

    printf("Determining optimized possibility...\n");
    // Looking for numbers bits summing 8 by 8.
    printf("Ignored for the moment.\n\n");

    printf("Computing integers...\n");
    for (unsigned int c_numbers = 0; c_numbers < size_numbers; c_numbers++)
    {
        TbcNumber number = numbers[c_numbers];
    }

    return tbc_result;
}