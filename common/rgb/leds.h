#pragma once

typedef struct {
  union { uint8_t r, red;   };
  union { uint8_t g, green; };
  union { uint8_t b, blue;  };
} RGB_LED_Default_t;

#if defined(RGB_LED_TYPE)
#define _RGB_LED(LED) RGB_LED_ ## LED ## _t
#define  RGB_LED(LED) _RGB_LED(LED)

/*** RGB LED definitions ***/
typedef struct {
  union { uint8_t g, green; };
  union { uint8_t r, red;   };
  union { uint8_t b, blue;  };
} RGB_LED_WS2812_t;

typedef RGB_LED(RGB_LED_TYPE) RGB_LED_t;
#else
typedef RGB_LED_Default_t RGB_LED_t;
#endif