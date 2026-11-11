#include "UART.h"
#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[]) {

  build(111, 187, 255);

  uint8_t val = check(build_buffer, 9);

  printf("good message : %u", val);

  return 0;
}
