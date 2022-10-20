#pragma once

typedef struct {
  volatile uint16_t mask;                     // Calculated mask of all 16 buttons
  volatile uint8_t  curr;                     // Current button to scan
  volatile uint8_t  debounce[BUTTONS_ACTIVE]; // Debounce state of all buttons
} _button_t;
