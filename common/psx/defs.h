#pragma once

typedef enum {
  PSX_Digital   = 0x41,
  PSX_AnalogRed = 0x73
} PSX_Identity_t;

typedef enum {
  PSX_Select      = 0x0001,
  PSX_R3          = 0x0002,
  PSX_L3          = 0x0004,
  PSX_Start       = 0x0008,
  PSX_DPad_Up     = 0x0010,
  PSX_DPad_Right  = 0x0020,
  PSX_DPad_Down   = 0x0040,
  PSX_DPad_Left   = 0x0080,
  PSX_L2          = 0x0100,
  PSX_R2          = 0x0200,
  PSX_L1          = 0x0400,
  PSX_R1          = 0x0800,
  PSX_Triangle    = 0x1000,
  PSX_Circle      = 0x2000,
  PSX_Cross       = 0x4000,
  PSX_Square      = 0x8000
} PSX_Button_t;

typedef struct {
  union {
    struct {
      uint16_t  buttons;
      union {
        struct {
          uint8_t rx, ry, lx, ly;
        };
        uint8_t axis[4];
      };
    };
    uint8_t raw[6];
  };
} PSX_Input_t;

// Packet describes both digital and red analog controllers
typedef struct {
  uint8_t index;      // The byte we're currently writing
  bool    shouldPoll; // Whether more data should be polled
  union {
    struct {
      PSX_Identity_t identity;   // Our controller type
      const uint8_t  padding_5a; // Should always be 0x5a
      PSX_Input_t    input;      // Our input
    };
    uint8_t raw[8]; // Identity + 5A + up to 3 words
  };
} PSX_Controller_t;
