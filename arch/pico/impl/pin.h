#pragma once
#include "pico/stdlib.h"

typedef uint16_t _pin_t;

#define PIN_NC -1
#define PINPAIR(a,b) {a, b}

typedef struct {
  _pin_t a;
  _pin_t b;
} _pin_pair_t;

static inline bool Pin_Read(_pin_t pin) {
  if (pin == PIN_NC) return 0;
  return gpio_get(pin);
}

static inline void Pin_WriteLow(_pin_t pin) {
  if (pin == PIN_NC) return;
  if (gpio_is_dir_out(pin))
    gpio_put(pin, 0);
  else
    gpio_set_pulls(pin, false, false);
}

static inline void Pin_WriteHigh(_pin_t pin) {
  if (pin == PIN_NC) return;
  if (gpio_is_dir_out(pin))
    gpio_put(pin, 1);
  else
    gpio_set_pulls(pin, true, false);
}

static inline void Pin_Toggle(_pin_t pin) {
  if (pin == PIN_NC) return;
  gpio_xor_mask(1 << pin);
}

static inline void Pin_Input(_pin_t pin) {
  if (pin == PIN_NC) return;
  gpio_init(pin);
  gpio_set_dir(pin, false);
}

static inline void Pin_Output(_pin_t pin) {
  if (pin == PIN_NC) return;
  gpio_init(pin);
  gpio_set_dir(pin, true);
}

static inline void Pin_InputFloat(_pin_t pin) {
  if (pin == PIN_NC) return;
  Pin_Input(pin);
  gpio_set_pulls(pin, false, false);
}

static inline void Pin_InputPullup(_pin_t pin) {
  if (pin == PIN_NC) return;
  Pin_Input(pin);
  gpio_set_pulls(pin, true, false);
}

static inline void Pin_OutputLow(_pin_t pin) {
  if (pin == PIN_NC) return;
  Pin_Output(pin);
  gpio_put(pin, 0);
}

static inline void Pin_OutputHigh(_pin_t pin) {
  if (pin == PIN_NC) return;
  Pin_Output(pin);
  gpio_put(pin, 1);
}

// #define PIN_H_QUOTE(x)   #x
// #define PIN_H(x)         PIN_H_QUOTE(x)
// #define PIN_H_INCLUDE(x) PIN_H(pin/x.h)

// #include PIN_H_INCLUDE(MCU)
