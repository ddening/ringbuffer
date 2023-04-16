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