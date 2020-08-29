#include "twelve_bytes_compression.h"

int main(int argc, char const *argv[])
{
    // The fact there are 12 elements is a coincidence. You can put more or less elements.
    TbcNumber numbers[12];

    /* Some sensor values on a maximum of 96 bits */

    TbcNumber pression = { 
        .precision = 0,
        .max_value = 11000,
        .min_value = 8700,
        .value = 10356              // current value measured (10356X) - 8500X (min value), rounded at 1033.2 hP
    };

    TbcNumber turbidity = {
        .precision = 0,
        .max_value = 1023,
        .min_value = 0,
        .value = 625
    };

    TbcNumber temperature = { 
        .precision = 0,
        .max_value = 800,
        .min_value = 0,
        .value = 235                // current value (23.5)
    };

    TbcNumber gps_lat = {
        .precision = 4,             // within 0.25 accuracy
        .max_value = 180000,
        .min_value = 0,
        .value = 964566             // current value (96456) + precision decimal (6)
    };

    TbcNumber gps_long  = {
        .precision = 4,             // within 0.25 accuracy
        .max_value = 90000,        
        .min_value = 0,
        .value = 856327             // current value (85632) + precision decimal (7)
    };

    TbcNumber gps_long_sign = { 
        .precision = 0,
        .max_value = 1,
        .min_value = 0,
        .value = 1
    };

    TbcNumber gps_lat_sign = { 
        .precision = 0,
        .max_value = 1,
        .min_value = 0,
        .value = 1
    };

    TbcNumber ph = { 
        .precision = 0,
        .max_value = 127,           // pH is here measured with a max value of 12.7 (normally 14)
        .min_value = 0,
        .value = 88                 // current value (8.8)
    };

    TbcNumber redox = { 
        .precision = 2,             // Precision of 5 by 5 steps
        .max_value = 400,           // Redox is normally measure from -2000mv to 2000mv, we're normalizing the measure out of 4000 (400 is because we want a 5 by 5 steps precision) 
        .min_value = 0,
        .value = 3006               // current value is 300 + 6 (precision unit)
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
        .value = 3
    };

    // Storing all 11 values
    // You can put more or less elements.
    numbers[0] = pression;
    numbers[1] = turbidity;
    numbers[2] = temperature;
    numbers[3] = gps_lat;
    numbers[4] = gps_long;
    numbers[5] = gps_long_sign;
    numbers[6] = gps_lat_sign;
    numbers[7] = ph;
    numbers[8] = redox;
    numbers[9] = antenna_battery;
    numbers[10] = floater_battery;

    twelve_bytes_compression(numbers, 11U);

    return 0;
}
