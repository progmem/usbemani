#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#if defined(RGB_DRIVER) && defined(RGB_LED_TYPE)
#include "rgb/defs.h"
#include "color/defs.h"
#include "impl/rgb.h"

/*** Declarations ***/
// Storage for RGB LEDs
extern RGB_LED_t _rgb[RGB_LEDS];
// Storage for the status of the RGB driver
extern _rgb_status_t            _rgb_status;

/*** Functions ***/
// Initializes RGB
static inline void RGB_Init(void) {
#if (RGB_LEDS > 0)
  memset(_rgb, 0, RGB_LEDS * sizeof(RGB_LED_t));
  _impl_rgb_init();
#endif
}
// Determines if the next frame's values should be calculated
static inline bool RGB_ReadyToCalculate(void) {
  bool tick = _rgb_status.tick;
  _rgb_status.tick = false;

  return tick;
}
// Determines if the next frame is ready to be drawn
static inline bool RGB_ReadyToDraw(void) {
  return _impl_rgb_ready() && _rgb_status.vsync;
}
// Renders RGB
static inline void RGB_Render(void) {
  _rgb_status.vsync = false;
  _impl_rgb_render();
}
// Regularly-schedule RGB status update task
static inline void RGB_UpdateStatus(void) {
  static const uint16_t wait = (TASK_TIMER_FREQUENCY / RGB_FRAMERATE_TARGET);
  static       uint16_t curr = wait;

  if (curr) {
    curr--;
    return;
  }


  curr = wait;
  _rgb_status.tick   = true;

  if (_impl_rgb_ready())
    _rgb_status.vsync  = true;
}
// Returns the offset in the RGB buffer for a given channel
static inline const uint16_t _rgb_channelOffset(const uint8_t channel) {
  const uint8_t per_channel[RGB_CHANNELS_ACTIVE] = { RGB_LEDS_PER_CHANNEL };
  if (channel >= RGB_CHANNELS_ACTIVE) return 0;

  uint16_t offset = 0;
  for (int i = 0; i < channel; i++)
    offset += per_channel[i];

  return offset;
}
// Returns the count of LEDs for a given channel
static inline const uint8_t _rgb_channelCount(const uint8_t channel) {
  const uint8_t per_channel[RGB_CHANNELS_ACTIVE] = { RGB_LEDS_PER_CHANNEL };
  if (channel >= RGB_CHANNELS_ACTIVE) return 0;
  return per_channel[channel];
}
// Sets an RGB LED on a given channel/position to a specific color
static inline void RGB_Set(const uint8_t channel, const uint8_t index, RGB_Color_t color) {
  if (index >= _rgb_channelCount(channel)) return;
  const uint16_t offset = _rgb_channelOffset(channel);

  _rgb[index + offset].r = color.r,
  _rgb[index + offset].g = color.g,
  _rgb[index + offset].b = color.b;
}

static inline RGB_Color_t RGB_Get(const uint8_t channel, const uint8_t index) {
  RGB_Color_t color = {.r=0,.g=0,.b=0};

  if (index >= _rgb_channelCount(channel)) return color;
  const uint16_t offset = _rgb_channelOffset(channel);


  color.r = _rgb[index + offset].r,
  color.g = _rgb[index + offset].g,
  color.b = _rgb[index + offset].b;

  return color;
}
// Sets a range of LEDs on a given channel to a specific color
static inline void RGB_SetRange(const uint8_t channel, const uint8_t start, const uint8_t count, RGB_Color_t color) {
  const uint8_t  chanSize = _rgb_channelCount(channel);
  const uint16_t offset   = _rgb_channelOffset(channel);

  for (uint8_t i = 0; i < count; i++) {
    if ((start + i) >= chanSize) return;
    _rgb[offset + start + i].r = color.r,
    _rgb[offset + start + i].g = color.g,
    _rgb[offset + start + i].b = color.b;
  }
}
// Clears all LEDs on a given channel
static inline void RGB_Clear(const uint8_t channel) {
  const uint16_t count  = _rgb_channelCount(channel);
  const uint16_t offset = _rgb_channelOffset(channel);

  if (count)
    memset(&_rgb[offset], 0, count * 3);
}
#else
static inline void RGB_Init(void) { }
static inline bool RGB_ReadyToCalculate(void) { return false; }
static inline bool RGB_ReadyToDraw(void) { return false; }
static inline void RGB_Render(void) { }
static inline void RGB_UpdateStatus(void) { }
static inline void RGB_Set(const uint8_t channel, const uint8_t index, RGB_Color_t color) { }
static inline void RGB_SetRange(const uint8_t channel, const uint8_t start, const uint8_t count, RGB_Color_t color) { }
static inline void RGB_Clear(const uint8_t channel) { }
#endif