#pragma once

typedef enum {
  Quirk_IIDX_LR2,
  Quirk_IIDX_FiveKeys
} Quirks_Type_t;

typedef struct {
  bool Quirk_IIDX_LR2       : 1;
  bool Quirk_IIDX_FiveKeys  : 1;
} Quirks_t;