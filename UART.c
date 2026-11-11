#include "UART.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

uint8_t build_buffer[9];

// this function calculates the XOR of the elements in the buffer.
uint8_t XOR_calc(uint8_t *buffer, size_t buffer_size) {

  uint8_t cur = 0;

  for (size_t i = 0; i < buffer_size; i++) {
    cur = cur ^ buffer[i];
  }

  return cur;
}

// this function builds a 9-byte message from 3 parameters
void build(uint8_t type, uint8_t direction, uint8_t degree_of_confidence) {

  // build the array buffer to be transmitted
  build_buffer[0] = START;
  build_buffer[1] = type;
  build_buffer[2] = direction;
  build_buffer[3] = degree_of_confidence;
  build_buffer[4] = EMPTY;
  build_buffer[5] = EMPTY;
  build_buffer[6] = EMPTY;
  build_buffer[7] = EMPTY;
  build_buffer[8] = EMPTY;

  size_t size = sizeof(build_buffer) - 1;

  uint8_t XOR = XOR_calc(build_buffer, size);

  build_buffer[8] = XOR;
}

// this is the receiving end on the ESP32
uint8_t check(uint8_t *buffer, size_t buffer_size) {

  // checks that the appropriate message length is passed
  if (buffer_size != 9) {
    return 0;
  }

  if (buffer[0] == START) {

    uint8_t XOR_val = buffer[8];
    uint8_t node = 0;

    for (size_t i = 0; i < buffer_size - 1; i++) {

      node = node ^ buffer[i];
    }
    if (node == XOR_val) {
      // check to see if the message transmitted from the trasmitter is
      // corrupted

      return 1;

    } else {
      // prints an error
      return 0;
    }

  } else {
    // prints an error
    return 0;
  }
}
