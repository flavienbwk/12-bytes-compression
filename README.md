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
Value 1 occupies 11 bits.
Value 2 occupies 10 bits.
Value 3 occupies 20 bits.
Value 4 occupies 19 bits.
Value 5 occupies 1 bits.
Value 6 occupies 1 bits.
Value 7 occupies 7 bits.
Value 8 occupies 1 bits.
Value 9 occupies 10 bits.
Value 10 occupies 2 bits.
Value 11 occupies 2 bits.

Reached 96 bits out of 96 maximum, OK.
This payload will use 12 bytes.

Computing frame...
OK, you just have to individually send theses data :
[byte 1] 103
[byte 2] 132
[byte 3] 36
[byte 4] 117
[byte 5] 175
[byte 6] 25
[byte 7] 21
[byte 8] 58
[byte 9] 2
[byte 10] 236
[byte 11] 101
[byte 12] 149

[Binary payload] [96/96] 011001111000010000100100011101011010111100011001000101010011101000000010111011000110010110010101
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
