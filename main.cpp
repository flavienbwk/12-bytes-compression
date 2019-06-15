#include "twelve_bytes_compression.h"

int main(int argc, char const *argv[])
{
    TbcNumber numbers[13];

    // Some sensor values on a maximum of 96 bits

    TbcNumber downlink_flag = { 
        .precision = 0,
        .max_value = 1,
        .min_value = 0,
        .value = 1
    };

    TbcNumber inner_water_flag = { 
        .precision = 0,
        .max_value = 1,
        .min_value = 0,
        .value = 1
    };

    TbcNumber outer_water_flag = { 
        .precision = 0,
        .max_value = 1,
        .min_value = 0,
        .value = 1
    };

    TbcNumber turbidity = {
        .precision = 2,             // within 0.5 accuracy
        .max_value = 2000,
        .min_value = 0,
        .value = 180
    };

    TbcNumber acceleration  = {
        .precision = 0,
        .max_value = 7,
        .min_value = 0,
        .value = 1
    };

    TbcNumber gps_long_sign = { 
        .precision = 0,
        .max_value = 1,
        .min_value = 0,
        .value = 1
    };

    TbcNumber gps_long  = {
        .precision = 4,             // within 0.25 accuracy
        .max_value = 90000,        
        .min_value = 0,
        .value = 96456
    };

    TbcNumber gps_lat_sign = { 
        .precision = 0,
        .max_value = 1,
        .min_value = 0,
        .value = 1
    };

    TbcNumber gps_lat = {
        .precision = 4,             // within 0.25 accuracy
        .max_value = 180000,
        .min_value = 0,
        .value = 96456
    };

    TbcNumber ph = { 
        .precision = 0,
        .max_value = 127,
        .min_value = 0,
        .value = 88
    };

    TbcNumber pression = { 
        .precision = 2,             // within 0.5 accuracy
        .max_value = 105000,
        .min_value = 87000,
        .value = 103000             // current value measured - 87000 (minimum)
    };

    TbcNumber conductance = { 
        .precision = 2,             // within 0.5 accuracy
        .max_value = 500,
        .min_value = 0,
        .value = 112
    };

    TbcNumber temperature = { 
        .precision = 0,
        .max_value = 99,
        .min_value = 0,
        .value = 234
    };

    numbers[0] = downlink_flag;
    numbers[1] = inner_water_flag;
    numbers[2] = outer_water_flag;
    numbers[3] = turbidity;
    numbers[4] = acceleration;
    numbers[5] = gps_long_sign;
    numbers[6] = gps_long;
    numbers[7] = gps_lat_sign;
    numbers[8] = gps_lat;
    numbers[9] = ph;
    numbers[10] = pression;
    numbers[11] = conductance;
    numbers[12] = temperature;

    twelve_bytes_compression(numbers, 13U);

    return 0;
}
