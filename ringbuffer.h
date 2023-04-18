/*************************************************************************
* Title		: ringbuffer.h
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

#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>
#include "payload.h"

#define QUEUE_SIZE 250

typedef struct payload_t payload_t;

typedef struct queue_t {
    uint8_t head;
    uint8_t tail;
    payload_t* payload[QUEUE_SIZE];
} queue_t;

queue_t* queue_init(queue_t*);

void queue_flush(queue_t*);

uint8_t queue_empty(queue_t*);

uint8_t queue_full(queue_t*);

uint8_t queue_enqueue(queue_t*, payload_t*);

payload_t* queue_dequeue(queue_t*);

#endif /* RINGBUFFER_H_ */