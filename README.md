# 12-bytes-compression
Algorithm for compressing digital values for SigFox frames of 12 bytes.

Use [twelve_bytes_compression.cpp](./twelve_bytes_compression.cpp) on the embedded software side of your SigFox project.

Then, use one of the `api_decompress.*` available to decompress the frame as you want on the server side.

## Special thanks

Thank you @ for your work on the theorical algorithm.