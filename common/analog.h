#pragma once
#include <stdint.h>

#include "error/analog.h"
#include "impl/analog.h"

extern volatile _analog_t _analogs[ANALOG_CHANNELS_ACTIVE];
// TODO:  This variable is currently held by each arch's analog files
//        However, the arch no longer writes to these values. Can we move this out?
extern volatile _analog_digital_t _analogs_digital;

// Initializes the analog subsystem
static inline void Analog_Init(void) {
#if (ANALOG_CHANNELS_ACTIVE > 0)
  for (uint8_t i = 0; i < ANALOG_CHANNELS_ACTIVE; i++) {
    // Reset values
    _analogs[i].filtered = 0;

    // Reset averages
    _analogs[i].average.sum   = 0;
    _analogs[i].average.index = 0;
    for (uint8_t j = 0; j < (1 << ANALOG_AVERAGE_STRENGTH); j++)
      _analogs[i].average.values[j] = 0;

    // Set thresholds to "safe values"
    _analogs[i].threshold.enable  = 128;
    _analogs[i].threshold.disable = 96;

    // Set calibration to an initial state
    _analogs[i].calibration.min = 96;
    _analogs[i].calibration.max = 224;
    _analogs[i].calibration.reciprocal = 0xFFFF / (224-96+1);
  }

  _impl_analog_init();
#endif
}

// Given an index, return the analog value after filtering
static inline int8_t Analog_Get(const uint8_t i) {
  if (i >= ANALOG_CHANNELS_ACTIVE) return 128;
  return _analogs[i].filtered;
}

// Given an index, return the analog value after filtering and calibration
static inline int8_t Analog_GetCalibrated(const uint8_t i) {
  if (i >= ANALOG_CHANNELS_ACTIVE) return 128;
  if (_analogs[i].filtered <= _analogs[i].calibration.min) return 0;
  if (_analogs[i].filtered >= _analogs[i].calibration.max) return 255;

  uint8_t delta = _analogs[i].filtered - _analogs[i].calibration.min;
  return (delta * _analogs[i].calibration.reciprocal) >> 8;
}

// Given an index, return the raw analog value without filtering
static inline uint8_t Analog_GetRaw(const uint8_t i) {
  if (i >= ANALOG_CHANNELS_ACTIVE) return 128;
  return _analogs[i].raw;
}

// Given an index, return the digital representation of the analog value
static inline bool Analog_GetDigital(const uint8_t i) {
  if (i >= ANALOG_CHANNELS_ACTIVE) return false;
  return !!(_analogs_digital & (1 << i));
}

// Return the digital representation of all analog values
static inline _analog_digital_t Analog_GetAllDigital(void) {
  return _analogs_digital;
}

// Given an index, reset the min/max for calibration
static inline void Analog_CalibrationStart(const uint8_t i) {
  _analogs[i].calibration.min = 255;
  _analogs[i].calibration.max = 0;
}

// Given an index, update analog range calibration
static inline void Analog_CalibrationUpdate(const uint8_t i) {
  register uint8_t val = Analog_Get(i);

  if (_analogs[i].calibration.min > val)
    _analogs[i].calibration.min = val;
  if (_analogs[i].calibration.max < val)
    _analogs[i].calibration.max = val;

  register uint8_t delta = _analogs[i].calibration.max - _analogs[i].calibration.min;
  delta++;
  _analogs[i].calibration.reciprocal = 0xFFFF / delta;
}

// Update analog data
static inline void Analog_Task(void) {
  for (int i = 0; i < ANALOG_CHANNELS_ACTIVE; i++) {
    // The MSB of the index indicates whether a new ADC reading is available
    if (!(_analogs[i].average.index & 0x80)) continue;

    register uint8_t raw = Analog_GetRaw(i);
    register uint8_t index = _analogs[i].average.index & ((1 << ANALOG_AVERAGE_STRENGTH)-1);

    //// Averaging
    // Subtract the previous value, then add the new value
    _analogs[i].average.sum -= _analogs[i].average.values[index];
    _analogs[i].average.sum += raw;
    _analogs[i].average.values[index] = raw;
    // Advance the index and reset the flag
    _analogs[i].average.index++;
    _analogs[i].average.index &= ~0x80;
    // If anything falls out of the calibration range, don't make any updates
    _analogs[i].filtered = _analogs[i].average.sum >> ANALOG_AVERAGE_STRENGTH;

    //// Thresholds
    register uint8_t calibrated = Analog_GetCalibrated(i);
    if (calibrated > _analogs[i].threshold.enable)
      _analogs_digital |=  (1 << i);
    if (calibrated < _analogs[i].threshold.disable)
      _analogs_digital &= ~(1 << i);
  }
}

// Given a low and high value, set the enable and disable thresholds for the digital input version.
// Once an analog reading passes the "high" threshold, the input is considered active.
// Once an analog reading drops below the "low" threshold, the input is considered inactive.
static inline void Analog_ConfigureThresholds(const uint8_t i, const uint8_t low, const uint8_t high) {
  if (i >= ANALOG_CHANNELS_ACTIVE) return;
  _analogs[i].threshold.enable  = high,
  _analogs[i].threshold.disable = low;
}
