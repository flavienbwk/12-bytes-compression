# 12-bytes-compression
Algorithm for compressing digital values for SigFox frames of 12 bytes.

Use [twelve_bytes_compression.cpp](./twelve_bytes_compression.cpp) on the embedded software side of your SigFox project.

Then, use one of the `api_decompress.*` available to decompress the frame as you want on the server side.

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

Thank you @ for your work on the theorical algorithm.