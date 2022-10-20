#include "encoder.h"

_encoder_t _encoder[ENCODERS_ACTIVE];

#if defined(ENCODER_DRIVER)
#include INCLUDE_IMPL(encoder, ENCODER_DRIVER, c)
#endif