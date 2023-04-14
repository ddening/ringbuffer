#ifndef PAYLOAD_H_
#define PAYLOAD_H_

/* General libraries */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

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

typedef void (*callback_fn)(void);

typedef struct device_t device_t;

typedef struct spi_payload_t {
    device_t* device;
    uint8_t* data;
    uint8_t number_of_bytes;  
    uint8_t* container;
    read_write_t mode;
    callback_fn callback;
} spi_payload_t;

typedef struct i2c_payload_t {
    device_t* device;
    uint8_t* data;
    uint8_t number_of_bytes;
    callback_fn callback;
} i2c_payload_t;

typedef struct payload_t {
    priority_t priority;
    union {
        spi_payload_t spi;
        i2c_payload_t i2c;
    } protocol;
} payload_t;

payload_t* payload_create_spi(priority_t priority, device_t* device, uint8_t* data, uint8_t number_of_bytes, callback_fn callback);
payload_t* payload_create_i2c(priority_t priority, device_t* device, uint8_t* data, uint8_t number_of_bytes, callback_fn callback);

void payload_free_spi(payload_t* payload);
void payload_free_i2c(payload_t* payload);

#endif /* PAYLOAD_H_ */