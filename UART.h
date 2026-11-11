
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

extern uint8_t build_buffer[9];

void build(uint8_t type, uint8_t direction, uint8_t degree_of_correctness);
uint8_t check(uint8_t *buffer, size_t buffer_size);
uint8_t XOR_calc(uint8_t *buffer, size_t buffer_size);

#endif
