
#include <cstdint>
#ifndef UART_h

#include <stddef.h>
#include <stdint.h>

#define START 7
#define AVOID 117
#define KICK 155
#define HOLD 123
#define DANCE 111
#define APPROACH 156
#define EMPTY 0

#define RX_NONE 0
#define RX_OK 1
#define RX_ERROR 2
#define RX_JUNK 3

#define ARRAY_SIZE 9

extern uint8_t build_buffer[9];

uint8_t check(uint8_t *buffer, size_t buffer_size);
uint8_t XOR_calc(uint8_t *buffer, size_t buffer_size);
uint8_t receive_byte(uint8_t byte, uint8_t *output_buffer);

#endif
