#include "utils.h"

// Returns a random 16-bit number
uint16_t Utils_Random(void) {
  static uint16_t rand;
  if (!rand) rand = 0x5a5a;

  rand ^= rand >> 7;
  rand ^= rand << 9;
  rand ^= rand >> 13;
  return rand;
}
