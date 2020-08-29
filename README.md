# 12-bytes-compression
Algorithm for compressing digital values for SigFox frames of 12 bytes.  
Allows as well to sacrifice unit value for it to be coded on 2/4/8 values instead of 10. 

Use [twelve_bytes_compression.cpp](./twelve_bytes_compression.cpp) on the embedded software side of your SigFox project.  
Then, use one of the librairies in `/decompress` to decompress the frame on the server side.

## Run example

Just run the following command :

```
g++ main.cpp twelve_bytes_compression.cpp && ./a.out
```

`main.cpp's a.out` example output :

```
Checking arithmetic validity...
Value 0 occupies 12 bits.
Value 1 occupies 10 bits.
Value 2 occupies 10 bits.
Value 3 occupies 20 bits.
Value 4 occupies 19 bits.
Value 5 occupies 1 bits.
Value 6 occupies 1 bits.
Value 7 occupies 7 bits.
Value 8 occupies 10 bits.
Value 9 occupies 2 bits.
Value 10 occupies 2 bits.

Reached 94 bits out of 96 maximum, OK.
This payload will use 12 bytes.

Computing frame...
Aggregating bytes...
OK, you just have to individually send these data :
[byte 1] 103    (01100111)
[byte 2] 137    (10001001)
[byte 3] 196    (11000100)
[byte 4] 235    (11101011)
[byte 5] 94     (01011110)
[byte 6] 50     (00110010)
[byte 7] 42     (00101010)
[byte 8] 116    (01110100)
[byte 9] 5      (00000101)
[byte 10] 216   (11011000)
[byte 11] 150   (10010110)
[byte 12] 84    (010101)

[Binary payload] [94/96] 0110011110001001110001001110101101011110001100100010101001110100000001011101100010010110010101
```

## Compatibility

This library was created to be compatible with most of the embedded microprocessors.

Compatibilities :
- :heavy_check_mark: Cortex M0+ (32 bits)
- :white_circle: atmega168
- :white_circle: atmega328
- :white_circle: atmega644
- :white_circle: atmega1280
- :white_circle: atmega1284
- :white_circle: atmega2560

:heavy_check_mark: = verified  
:white_circle: = should operate  
:x: = not compatible

> Please address an issue which title starts with `[Compatibility]` to send me your compatibility results. Your name will be listed below to thank you !

## Special thanks

Special thanks to [Eliot Courtel ()](https://github.com/) for his work on the theorical algorithm.
