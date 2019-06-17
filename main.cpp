#include "twelve_bytes_compression.h"

int main(int argc, char const *argv[])
{
    TbcNumber numbers[13];

    // Some sensor values on a maximum of 96 bits

    TbcNumber downlink_flag = { 
        .precision = 0,
        .max_value = 1,
        .min_value = 0,
        .value = 0
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
        .max_value = 999,           // can reduce to 500
        .min_value = 0,
        .value = 2653               // current value (265) + precision decimal (3)
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
        .value = 856327             // current value (85632) + precision decimal (7)
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
        .value = 964566             // current value (96456) + precision decimal (6)
    };

    TbcNumber ph = { 
        .precision = 0,
        .max_value = 127,
        .min_value = 0,
        .value = 88
    };

    TbcNumber pression = { 
        .precision = 2,             // within 0.25 accuracy
        .max_value = 110000,
        .min_value = 85000,
        .value = 1033210            // current value measured (103321) - 87000 (min value) + precision compression on unit (0)
    };

    TbcNumber conductance = { 
        .precision = 2,
        .max_value = 50,
        .min_value = 0,
        .value = 112                // current value (11) + precision compression on unit (2)
    };

    TbcNumber temperature = { 
        .precision = 0,
        .max_value = 999,
        .min_value = 0,
        .value = 232
    };

    numbers[0] = downlink_flag;
    numbers[1] = turbidity;
    numbers[2] = gps_lat;
    numbers[3] = acceleration;
    numbers[4] = gps_long;
    numbers[5] = gps_long_sign;
    numbers[6] = gps_lat_sign;
    numbers[7] = ph;
    numbers[8] = inner_water_flag;
    numbers[9] = pression;
    numbers[10] = conductance;
    numbers[11] = temperature;
    numbers[12] = outer_water_flag;

    twelve_bytes_compression(numbers, 13U);

    return 0;
}
