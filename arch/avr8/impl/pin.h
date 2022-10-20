#pragma once
#include <avr/io.h>
#include <stdbool.h>

typedef uint16_t _pin_t;

#pragma push_macro("_SFR_IO8")
#undef  _SFR_IO8
#define _SFR_IO8(x) x
#ifdef PINA
static const uint16_t __BASEADDR_A = PINA;
#endif
#ifdef PINB
static const uint16_t __BASEADDR_B = PINB;
#endif
#ifdef PINC
static const uint16_t __BASEADDR_C = PINC;
#endif
#ifdef PIND
static const uint16_t __BASEADDR_D = PIND;
#endif
#ifdef PINE
static const uint16_t __BASEADDR_E = PINE;
#endif
#ifdef PINF
static const uint16_t __BASEADDR_F = PINF;
#endif
#pragma pop_macro("_SFR_IO8")

#define __PIN(port, pin) ((__BASEADDR_##port << 4) | (pin & 0x0F))
#define __PIN_ADDR(pin, offset) _SFR_IO8((pin >> 4) + offset)

#define REG_PIN(pin)  __PIN_ADDR(pin, 0)
#define REG_DDR(pin)  __PIN_ADDR(pin, 1)
#define REG_PORT(pin) __PIN_ADDR(pin, 2)

#ifdef PINA
#define PIN_A0 __PIN(A, 0)
#define PIN_A1 __PIN(A, 1)
#define PIN_A2 __PIN(A, 2)
#define PIN_A3 __PIN(A, 3)
#define PIN_A4 __PIN(A, 4)
#define PIN_A5 __PIN(A, 5)
#define PIN_A6 __PIN(A, 6)
#define PIN_A7 __PIN(A, 7)
#endif
#ifdef PINB
#define PIN_B0 __PIN(B, 0)
#define PIN_B1 __PIN(B, 1)
#define PIN_B2 __PIN(B, 2)
#define PIN_B3 __PIN(B, 3)
#define PIN_B4 __PIN(B, 4)
#define PIN_B5 __PIN(B, 5)
#define PIN_B6 __PIN(B, 6)
#define PIN_B7 __PIN(B, 7)
#endif
#ifdef PINC
#define PIN_C0 __PIN(C, 0)
#define PIN_C1 __PIN(C, 1)
#define PIN_C2 __PIN(C, 2)
#define PIN_C3 __PIN(C, 3)
#define PIN_C4 __PIN(C, 4)
#define PIN_C5 __PIN(C, 5)
#define PIN_C6 __PIN(C, 6)
#define PIN_C7 __PIN(C, 7)
#endif
#ifdef PIND
#define PIN_D0 __PIN(D, 0)
#define PIN_D1 __PIN(D, 1)
#define PIN_D2 __PIN(D, 2)
#define PIN_D3 __PIN(D, 3)
#define PIN_D4 __PIN(D, 4)
#define PIN_D5 __PIN(D, 5)
#define PIN_D6 __PIN(D, 6)
#define PIN_D7 __PIN(D, 7)
#endif
#ifdef PINE
#define PIN_E0 __PIN(E, 0)
#define PIN_E1 __PIN(E, 1)
#define PIN_E2 __PIN(E, 2)
#define PIN_E3 __PIN(E, 3)
#define PIN_E4 __PIN(E, 4)
#define PIN_E5 __PIN(E, 5)
#define PIN_E6 __PIN(E, 6)
#define PIN_E7 __PIN(E, 7)
#endif
#ifdef PINF
#define PIN_F0 __PIN(F, 0)
#define PIN_F1 __PIN(F, 1)
#define PIN_F2 __PIN(F, 2)
#define PIN_F3 __PIN(F, 3)
#define PIN_F4 __PIN(F, 4)
#define PIN_F5 __PIN(F, 5)
#define PIN_F6 __PIN(F, 6)
#define PIN_F7 __PIN(F, 7)
#endif

#define PIN_NC -1
#define PINPAIR(a,b) {a, b}

/*** Device-Specific ***/
// SPI
#define PIN_SPI_SS    PIN_B0
#define PIN_SPI_SCLK  PIN_B1
#define PIN_SPI_MOSI  PIN_B2
#define PIN_SPI_MISO  PIN_B3

typedef struct {
  _pin_t a;
  _pin_t b;
} _pin_pair_t;

static inline bool Pin_Read(_pin_t pin) {
  if (pin == PIN_NC) return 0;
  return !!(REG_PIN(pin) & _BV(pin & 0x0F));
}

static inline void Pin_WriteLow(_pin_t pin) {
  if (pin == PIN_NC) return;
  REG_PORT(pin) &= ~_BV(pin & 0x0F);
}

static inline void Pin_WriteHigh(_pin_t pin) {
  if (pin == PIN_NC) return;
  REG_PORT(pin) |=  _BV(pin & 0x0F);
}

static inline void Pin_Toggle(_pin_t pin) {
  if (pin == PIN_NC) return;
  REG_PORT(pin) ^=  _BV(pin & 0x0F);
}

static inline void Pin_Input(_pin_t pin) {
  if (pin == PIN_NC) return;
  REG_DDR(pin) &= ~_BV(pin & 0x0F);
}

static inline void Pin_Output(_pin_t pin) {
  if (pin == PIN_NC) return;
  REG_DDR(pin) |=  _BV(pin & 0x0F);
}

#define Pin_InputFloat(pin)   ((pin == PIN_NC) ? 0 : (Pin_Input(pin),   Pin_WriteLow(pin)))
#define Pin_InputPullup(pin)  ((pin == PIN_NC) ? 0 : (Pin_Input(pin),  Pin_WriteHigh(pin)))
#define Pin_OutputLow(pin)    ((pin == PIN_NC) ? 0 : (Pin_Output(pin),  Pin_WriteLow(pin)))
#define Pin_OutputHigh(pin)   ((pin == PIN_NC) ? 0 : (Pin_Output(pin), Pin_WriteHigh(pin)))

#define PIN_H_QUOTE(x)   #x
#define PIN_H(x)         PIN_H_QUOTE(x)
#define PIN_H_INCLUDE(x) PIN_H(pin/x.h)

#include PIN_H_INCLUDE(MCU)
