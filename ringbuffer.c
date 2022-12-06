#include <stdio.h>
#include <stdlib.h>
#include "ringbuffer.h"

queue_t* queue_init(queue_t* queue) {
    queue->head = 0;
    queue->tail = 0;

    return queue;
}

void queue_flush(queue_t* queue) {   
    queue->head = 0;
    queue->tail = 0;
}

// Check if the queue is empty
uint8_t queue_empty(queue_t* queue) {
    return queue->head == queue->tail;
}

// Check if the queue is full
uint8_t queue_full(queue_t* queue) {
    return (queue->tail + 1) % QUEUE_SIZE == queue->head;
}

uint8_t queue_enqueue(queue_t* queue, payload_t* payload) {

    if (queue_full(queue)) {
        printf("Queue is full, can't enqueue.\n");
        return 1;
    }

    // Add the item to the queue in the correct position according to its priority
    int i = queue->tail;
    while (i > queue->head && queue->payload[i-1]->priority < payload->priority) {
        queue->payload[i] = queue->payload[i-1];
        i--;
    }
    queue->payload[i] = payload;
    queue->tail = (queue->tail + 1) % QUEUE_SIZE;

    return 0;
}

payload_t* queue_dequeue(queue_t* queue) {

    if (queue_empty(queue)) {
        printf("Queue is empty, can't dequeue.\n");
        return NULL;
    }

    // Remove the item from the front of the queue
    payload_t* payload = queue->payload[queue->head];
    queue->head = (queue->head + 1) % QUEUE_SIZE;

    return payload;
}