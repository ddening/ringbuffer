/*************************************************************************
* Title		: payload.h
* Author	: Dimitri Dening
* Created	: 06.12.2022
* Software	: Microchip Studio V7
* Hardware	: Atmega2560
* License	: MIT License
* Usage		: see Doxygen manual
*
*       Copyright (C) 2023 Dimitri Dening
*
*       Permission is hereby granted, free of charge, to any person obtaining a copy
*       of this software and associated documentation files (the "Software"), to deal
*       in the Software without restriction, including without limitation the rights
*       to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
*       copies of the Software, and to permit persons to whom the Software is
*       furnished to do so, subject to the following conditions:
*
*       The above copyright notice and this permission notice shall be included in all
*       copies or substantial portions of the Software.
*
*       THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
*       IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
*       FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
*       AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
*       LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*       OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
*       SOFTWARE.
*
*************************************************************************/

#ifndef PAYLOAD_H_
#define PAYLOAD_H_

/* General libraries */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

typedef void (*callback_fn)(void* context);

typedef struct device_t device_t;

typedef enum priority_t {
    PRIORITY_LOW,
    PRIORITY_NORMAL,
    PRIORITY_HIGH
} priority_t;

typedef enum read_write_t {
    WRITE,
    READ,
    READ_WRITE
} read_write_t;

typedef struct spi_payload_t {
    device_t* device;
    uint8_t* data;
    uint8_t* data_addr; // required to free data
    uint8_t number_of_bytes;  
    uint8_t* container;
    read_write_t mode;
    callback_fn callback;
} spi_payload_t;

typedef struct i2c_payload_t {
    device_t* device;
    uint8_t* data;
	uint8_t* data_addr; // required to free data
    uint8_t number_of_bytes;
	read_write_t mode;
    callback_fn callback;
} i2c_payload_t;

typedef struct hd44780_payload_t {
	uint8_t opcode;
	uint8_t instruction;
} hd44780_payload_t;

typedef struct payload_t {
    priority_t priority;
	spi_payload_t spi;
	i2c_payload_t i2c;
	hd44780_payload_t hd44780;
} payload_t;

payload_t* payload_create_spi(priority_t priority, device_t* device, uint8_t* data, uint8_t number_of_bytes, callback_fn callback);
payload_t* payload_create_i2c(priority_t priority, device_t* device, uint8_t* data, uint8_t number_of_bytes, callback_fn callback);
payload_t* payload_create_hd44780(priority_t priority, uint8_t opcode, uint8_t instruction);

void payload_free_spi(payload_t* payload);
void payload_free_i2c(payload_t* payload);
void payload_free_hd44780(payload_t* payload);

#endif /* PAYLOAD_H_ */