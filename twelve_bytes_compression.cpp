/**
 * @file twelve_bytes_compression.cpp
 * @author Flavien Berwick (flavien@berwick.fr)
 * @brief Algorithm for compressing digital values for SigFox frames of 12 bytes.
 * @version 0.2
 * @date 2020-08-28
 * 
 * Under MIT license. See the full license here :
 * https://github.com/flavienbwk/12-bytes-compression
 */
#include "twelve_bytes_compression.h"

/**
 * @brief Performs a log2 operation.
 * 
 * @param n 
 * @return double 
 */
double Log2(double n)
{
    return log(n) / log(2);
}

/**
 * @brief Describes a TbcNumber struct for debugging purpose.
 * 
 * @param number 
 */
void tbc_struct_desc(TbcNumber number)
{
    printf("[TbcNumber] precision: %d, max_value: %d, min_value: %d, value: %d\n", number.precision, number.max_value, number.min_value, number.value);
    return;
}

/**
 * @brief Returns the decimal from a binary string.
 * 
 * @param str 
 * @param size 
 * @return unsigned int 
 */
unsigned int strbin_to_dec(char *str, unsigned int size)
{
    unsigned int result = 0;
    for (int i = size - 1, j = 0; i >= 0; i--, j++)
    {
        unsigned char k = str[i] - '0';
        k <<= j;
        result += k;
    }
    return result;
}

/**
 * @brief 
 * In case your number may be negative, put max_value at
 * its maximum absolute value. Then, you have to foresee
 * a 1 bit TbcNumber to know if your number is positive 
 * or negative.
 */
unsigned int *twelve_bytes_compression(TbcNumber *numbers, unsigned int size_numbers)
{

    unsigned short max_bytes = 12; // SigFox maximum payload size
    unsigned int tbc_result[max_bytes] = {0U};

    // Do your values fit in 96 bits (12 bytes) ?
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
            printf("You set a precision of %d, precisions must be multiples of 2. Stopping.\n", number.precision);
            exit(1);
            tbc_struct_desc(number);
            number.precision = 0;
        }

        if (number.min_value == 0)
        {
            number.bits = (number.precision == 0) ? ceil(Log2(number.max_value)) : ceil(Log2(number.max_value * number.precision));
        }
        else
        {
            number.bits = (number.precision == 0) ? ceil(Log2(tmp_val_diff)) : ceil(Log2(((number.max_value * number.precision) / 10 - (number.min_value * number.precision) / 10)));
        }
        number.bits = (number.bits == 0) ? 1 : number.bits;
        printf("Value %d occupies %d bits.\n", c_numbers, number.bits);
        total_nb_bits += number.bits;

        // Checking current value validity
        unsigned int tmp_cmpt_val;
        unsigned int tmp_precision = (number.precision > 0) ? number.precision : 1;
        if (number.precision == 0)
        {
            if (number.min_value == 0)
            {
                tmp_cmpt_val = number.value;
                tmp_cmpt_val = (ROUND_BOUND_HIGH && tmp_cmpt_val > number.max_value) ? number.max_value : tmp_cmpt_val;
                tmp_cmpt_val = (ROUND_BOUND_LOW && tmp_cmpt_val < number.min_value) ? number.min_value : tmp_cmpt_val;
                if (ENABLE_VALUES_CHECKS && (tmp_cmpt_val > number.max_value || tmp_cmpt_val < number.min_value))
                {
                    printf("%d is not between %d and %d, stopping.\n", tmp_cmpt_val, number.min_value, number.max_value);
                    tbc_struct_desc(number);
                    return tbc_result;
                }
            }
            else
            {
                tmp_cmpt_val = number.value - number.min_value;
                tmp_cmpt_val = (ROUND_BOUND_HIGH && tmp_cmpt_val > tmp_val_diff) ? tmp_val_diff : tmp_cmpt_val;
                tmp_cmpt_val = (ROUND_BOUND_LOW && tmp_cmpt_val < 0) ? 0 : tmp_cmpt_val;
                if (ENABLE_VALUES_CHECKS && (tmp_cmpt_val > tmp_val_diff) || (tmp_cmpt_val < 0))
                {
                    printf("%d is not between %d and %d, stopping.\n", tmp_cmpt_val, 0, (tmp_val_diff * tmp_precision));
                    tbc_struct_desc(number);
                    return tbc_result;
                }
            }
        }
        else
        {
            if (number.min_value == 0)
            {
                tmp_cmpt_val = ceil(number.value * tmp_precision / 10);
                tmp_cmpt_val = (ROUND_BOUND_HIGH && tmp_cmpt_val > ceil(number.max_value * tmp_precision)) ? ceil(number.max_value * tmp_precision) : tmp_cmpt_val;
                tmp_cmpt_val = (ROUND_BOUND_LOW && tmp_cmpt_val < number.min_value) ? 0 : tmp_cmpt_val;
                if (ENABLE_VALUES_CHECKS && (tmp_cmpt_val < number.min_value || tmp_cmpt_val > pow(2, number.bits) - 1))
                {
                    printf("%d is not between %d and %f, stopping.\n", tmp_cmpt_val, number.min_value, ceil(number.max_value * tmp_precision / 10));
                    tbc_struct_desc(number);
                    return tbc_result;
                }
            }
            else
            {
                tmp_cmpt_val = ceil(number.value * tmp_precision / 10) - ceil(number.min_value * tmp_precision);
                tmp_cmpt_val = (ROUND_BOUND_HIGH && tmp_cmpt_val > (tmp_val_diff)*tmp_precision) ? (tmp_val_diff)*tmp_precision : tmp_cmpt_val;
                tmp_cmpt_val = (ROUND_BOUND_LOW && tmp_cmpt_val < number.min_value) ? 0 : tmp_cmpt_val;
                if (ENABLE_VALUES_CHECKS && (tmp_cmpt_val > (tmp_val_diff * tmp_precision) || (tmp_cmpt_val < 0)))
                {
                    printf("%d is not between %d and %d, stopping.\n", (tmp_cmpt_val), 0, (tmp_val_diff * tmp_precision));
                    tbc_struct_desc(number);
                    return tbc_result;
                }
            }
        }
        (&numbers[c_numbers])->cmpt_value = tmp_cmpt_val;
        (&numbers[c_numbers])->bits = number.bits;
    }

    // Showing some verification details
    if (total_nb_bits > max_bytes * 8)
    {
        printf("%d bits out of %d maximum, stopping.\n", total_nb_bits, max_bytes * 8);
        return tbc_result;
    }
    printf("\nReached %d bits out of %d maximum, OK.\n", total_nb_bits, max_bytes * 8);
    printf("This payload will use %d bytes.\n\n", (1 + ((total_nb_bits - 1) / 8U)));

    printf("Computing frame...\n");
    char str_bits[max_bytes * 8];
    unsigned int str_bits_counter = 0;
    for (unsigned int c_numbers = 0; c_numbers < size_numbers; c_numbers++)
    {
        TbcNumber number = numbers[c_numbers];
        for (int i = number.bits - 1; i >= 0; i--)
        {
            unsigned int k = number.cmpt_value >> i;
            str_bits[str_bits_counter] = (k & 1) ? '1' : '0';
            str_bits_counter += 1;
        }
    }

    printf("Aggregating bytes...\n");
    unsigned int c_tbc_result = 0;
    char tmp_tbc_result[8] = {'0'};
    for (unsigned int c_numbers = 0; c_numbers <= str_bits_counter; c_numbers++)
    {
        if (c_numbers != 0 && c_numbers % 8 == 0)
        {
            tbc_result[c_tbc_result] = strbin_to_dec(tmp_tbc_result, 8);
            c_tbc_result++;
        }
        tmp_tbc_result[c_numbers % 8] = str_bits[c_numbers];
    }

    // Filling missing zeros if payload isn't full
    if (total_nb_bits % 8 != 0)
    {
        for (unsigned int c_numbers = (total_nb_bits % 8); c_numbers < 8; c_numbers++)
            tmp_tbc_result[c_numbers] = '0';
        tbc_result[c_tbc_result] = strbin_to_dec(tmp_tbc_result, 8);
    }

    // Displaying results
    printf("OK, you just have to individually send these data :\n");
    for (unsigned int i = 0; i < max_bytes; i++)
    {
        printf("[byte %d] %d\n", i + 1, tbc_result[i]);
    }
    printf("\n[Binary payload] [%d/%d] %s\n", str_bits_counter, max_bytes * 8, str_bits);

    return tbc_result;
}