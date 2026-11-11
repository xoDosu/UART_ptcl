#include "UART.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

uint8_t build_buffer[9];

// this function calculates the XOR of the elements in the buffer.
uint8_t XOR_calc(uint8_t *buffer, size_t buffer_size) {

  uint8_t cur = 0;

  for (size_t i = 0; i < buffer_size; i++) {
    cur = cur ^ buffer[i];
  }

  return cur;
}

// this is the receiving end on the ESP32
uint8_t check(uint8_t *buffer, size_t buffer_size) {

  // checks that the appropriate message length is passed
  if (buffer_size != 9) {
    return RX_ERROR;
  }

  if (buffer[0] == START) {

    uint8_t XOR_val = buffer[8];
    uint8_t node = 0;

    node = XOR_calc(buffer, buffer_size - 1);

    if (node == XOR_val) {
      // check to see if the message transmitted from the trasmitter is
      // corrupted

      return RX_OK;

    } else {
      // prints an error
      return RX_ERROR;
    }

  } else {
    // prints an error
    return RX_ERROR;
  }
}

uint8_t receive_byte(uint8_t byte, uint8_t *output_buffer) {

  // counts how many bytes have been transmitted.
  static uint8_t counter = 0;
  static uint8_t buffer_store[ARRAY_SIZE];

  if (counter == 0 && byte != START) {
    return RX_JUNK;
  } else {
    buffer_store[counter] = byte;
    counter++;

    if (counter < ARRAY_SIZE) {
      return RX_NONE;
    }

    if (counter == ARRAY_SIZE) {
      counter = 0;
      uint8_t return_val = check(buffer_store, ARRAY_SIZE);
      if (return_val == RX_OK) {
        memcpy(output_buffer, buffer_store, ARRAY_SIZE);
        return RX_OK;
      }
    }
  }

  return RX_ERROR;
}
