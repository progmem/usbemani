#pragma once

#define ANALOG_AVERAGE_STRENGTH 3

// Averaging information: 11
typedef struct {
  uint8_t  index;
  uint8_t  values[1 << ANALOG_AVERAGE_STRENGTH];
  uint16_t sum;
} _analog_average_t;

// Calibration information: 4
typedef struct {
  uint8_t min, max;
  uint16_t reciprocal;
} _analog_calibration_t;

// Schmitt-trigger thresholds for analog values: 2
typedef struct {
  uint8_t enable, disable;
} _analog_threshold_t;

typedef struct {
  uint8_t filtered; // Filtered value after calibration
  uint8_t raw;      // Raw ADC
  _analog_average_t     average;      // Averaging
  _analog_threshold_t   threshold;    // Thresholds
  _analog_calibration_t calibration;  // Calibration
} _analog_t;

typedef uint16_t _analog_digital_t;
