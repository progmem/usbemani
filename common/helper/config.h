#pragma once
#define  CONFIG_PRINT(x) _CONFIG_PRINT(x)
#define _CONFIG_PRINT(x) #x

#define _CONFIG_MIN(x, y)         ((x < y) ? x : y)
#define _CONFIG_MAX(x, y)         ((x > y) ? x : y)
#define _CONFIG_CONCAT(x, y)      x ## y

#define _CONFIG_QUOTE(x)          #x
#define _CONFIG(x)                _CONFIG_QUOTE(x)
#define _CONFIG_INCLUDE(x, y)     _CONFIG(config/x.y)


/* Encoder */
#define  CONCAT_ENCODER_MAX(x)    _CONFIG_CONCAT(x, _Max)
#define  CONCAT_ENCODER_SHIFT(x)  _CONFIG_CONCAT(x, _Shift)
#define  CONCAT_ENCODER_DELTA(x)  _CONFIG_CONCAT(x, _Delta)

#define ENCODER_AXIS_RESOLUTION_IIDX 8
#define ENCODER_AXIS_RESOLUTION_SDVX 10

#define ENCODER_SCALE_IIDX 144
#define ENCODER_SCALE_SDVX 1024
