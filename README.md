Embedded-Circular-Buffer
========================

Circular Buffer Library for 8-bit Microcontroller

This library, designed to ANSI-C standards, allows the user to create a circular buffers of size ranging from 0-255 members. Multiple buffers can be created. The size and data type of the buffer is defined in the header file, and cannot be changed at runtime. Adding new members to a full buffer does not change the contents of the the buffer. Attempting to remove a member from an empty buffer results in a default return value, as defined in the source file.
