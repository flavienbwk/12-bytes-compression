#include "twelve_bytes_compression.h"

int main(int argc, char const *argv[])
{
    TbcNumber numbers[12];

    // Some sensor values on a maximum of 96 bits

    TbcNumber in_water_flag = { 
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
        .value = 88                 // current value (8.8)
    };

    TbcNumber pression = { 
        .precision = 0,
        .max_value = 11000,
        .min_value = 8700,
        .value = 10356              // current value measured (10356X) - 8500X (min value), rounded at 1033.2 hP
    };

    TbcNumber temperature = { 
        .precision = 0,
        .max_value = 800,
        .min_value = 0,
        .value = 235                // current value (23.5)
    };

    TbcNumber redox = { 
        .precision = 2,
        .max_value = 400,
        .min_value = 0,
        .value = 3006               // current value (3006), rounded to 3000 (precision of 5)
    };

    TbcNumber antenna_battery = { 
        .precision = 0,
        .max_value = 4,
        .min_value = 0,
        .value = 1
    };

    TbcNumber floater_battery = { 
        .precision = 0,
        .max_value = 4,
        .min_value = 0,
        .value = 1
    };

    numbers[0] = pression;
    numbers[1] = turbidity;
    numbers[2] = temperature;
    numbers[3] = gps_lat;
    numbers[4] = gps_long;
    numbers[5] = gps_long_sign;
    numbers[6] = gps_lat_sign;
    numbers[7] = ph;
    numbers[8] = in_water_flag;
    numbers[9] = redox;
    numbers[10] = antenna_battery;
    numbers[11] = floater_battery;

    twelve_bytes_compression(numbers, 12U);

    return 0;
}
