/*************************************************************************
* Title     : payload.c
* Author    : Dimitri Dening
* Created   : 06.12.2022    
* Software  : Microchip Studio V7
* Hardware  : Atmega2560
        
DESCRIPTION:
    Payload definitions for different communication protocols.
USAGE:
    see <payload.h>
NOTES:
                       
*************************************************************************/

/* User defined libraries */
#include "payload.h"

payload_t* payload_create_spi(priority_t priority, device_t* device, uint8_t* data, uint8_t number_of_bytes, callback_fn callback) {

    payload_t* payload = (payload_t*)malloc(sizeof(payload_t));

    uint8_t* _data = (uint8_t*)malloc(sizeof(uint8_t) * number_of_bytes);
    
    if (payload == NULL || _data == NULL) {
        return NULL;
    }

    for (uint8_t i = 0; i < number_of_bytes; i++) {
        _data[i] = data[i];     

    }

    payload->priority = priority;
    payload->protocol.spi.device = device;
    payload->protocol.spi.data = _data;
    payload->protocol.spi.data_addr = _data;
    payload->protocol.spi.number_of_bytes = number_of_bytes;
    payload->protocol.spi.callback = callback;
    payload->protocol.spi.container = NULL;
    payload->protocol.spi.mode = -1;

    return payload;
}

payload_t* payload_create_i2c(priority_t priority, device_t* device, uint8_t* data, uint8_t number_of_bytes, callback_fn callback) {

    payload_t* payload = (payload_t*)malloc(sizeof(payload_t));

    uint8_t* _data = (uint8_t*)malloc(sizeof(uint8_t) * number_of_bytes);

    if (payload == NULL || _data == NULL) {
        return NULL;
    }

    payload->priority = priority;
    payload->protocol.i2c.device = device;
    payload->protocol.i2c.data = _data;
    payload->protocol.i2c.number_of_bytes = number_of_bytes;
    payload->protocol.i2c.callback = callback;

    return payload;
}

void payload_free_spi(payload_t* payload) {
    /* Pointer of data is always shifted when next bit is sent, therefore 
    free(payload->protocol.spi.data) no longer refers to the starting point of data.
    Instead data points to the shifted position. This does not free the allocated resources -> memory leak.
    That's why we save the original data address, to be able to restore or free the allocated memory correctly.
    Using number_of_bytes to restore the original address doesn't work, since we are using number_of_bytes to determine
    if the payload is empty by reducing it's value in each ISR occurence.
    */
    free(payload->protocol.spi.data_addr);
    free(payload);
}

void payload_free_i2c(payload_t* payload) {
    free(payload->protocol.i2c.data);
    free(payload);
}