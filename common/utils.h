#pragma once
#include <stdbool.h>
#include <stdint.h>

/*** Defines ***/
#define Button_HeldExclusively(button_mask) \
    uint8_t check_buttons[] = { button_mask }; \
    uint16_t required_buttons = 0; \
    uint16_t held_buttons = 0; \
    \
    for (uint8_t i = 0; i < sizeof(check_buttons); i++) { \
      const uint16_t mask = (1 << check_buttons[i]); \
      required_buttons |= mask; \
      if (Button_GetRaw(check_buttons[i])) \
        held_buttons |= mask; \
    } \
    \
    if (held_buttons == required_buttons) \
      return true; \
    return false

#define Button_HeldInclusively(button_mask) \
    uint8_t check_buttons[] = { button_mask }; \
    uint16_t required_buttons = 0; \
    uint16_t held_buttons = 0; \
    \
    for (uint8_t i = 0; i < sizeof(check_buttons); i++) { \
      const uint16_t mask = (1 << check_buttons[i]); \
      required_buttons |= mask; \
      if (Button_GetRaw(check_buttons[i])) \
        held_buttons |= mask; \
    } \
    \
    if ((held_buttons & required_buttons) == required_buttons) \
      return true; \
    return false


/*** Functions ***/
// Given a current and max value, map the current value to the range 0-255 based on the max.
static inline uint8_t Utils_RangeToU8(uint16_t curr, const uint16_t max) {
  const uint16_t reciprocal = (0xFFFF / max);
        uint16_t result     = curr * reciprocal;

  return result >> 8;
}

uint16_t Utils_Random(void);
