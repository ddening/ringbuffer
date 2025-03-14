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
#include "memory.h"

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
    payload->spi.device = device;
    payload->spi.data = _data;
    payload->spi.data_addr = _data;
    payload->spi.number_of_bytes = number_of_bytes;
    payload->spi.callback = callback;
    payload->spi.container = NULL;
    payload->spi.mode = -1;

    return payload;
}

payload_t* payload_create_i2c(priority_t priority, device_t* device, uint8_t* data, uint8_t number_of_bytes, callback_fn callback) {

    payload_t* payload = (payload_t*)malloc(sizeof(payload_t));

    uint8_t* _data = (uint8_t*)malloc(sizeof(uint8_t) * number_of_bytes);

    if (payload == NULL || _data == NULL) {
        return NULL;
    }
    
    for (uint8_t i = 0; i < number_of_bytes; i++) {
        _data[i] = data[i];
    }

    payload->priority = priority;
    payload->i2c.device = device;
    payload->i2c.data = _data;
	payload->spi.data_addr = _data;
    payload->i2c.number_of_bytes = number_of_bytes;
    payload->i2c.mode = -1;
    payload->i2c.callback = callback;

    return payload;
}

payload_t* payload_create_hd44780(priority_t priority, uint8_t opcode, uint8_t instruction) {
	
	payload_t* payload = (payload_t*)malloc(sizeof(payload_t));
	
	if (payload == NULL) {
		return NULL;
	}
	
	payload->priority = priority;
	payload->hd44780.opcode = opcode;
	payload->hd44780.instruction = instruction;
	
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
    free(payload->spi.data_addr);
    free(payload);
}

void payload_free_i2c(payload_t* payload) {
	free(payload->i2c.data_addr);
    free(payload);
}

void payload_free_hd44780(payload_t* payload) {
	free(payload);
}