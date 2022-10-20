#pragma once

#if ENCODERS_ACTIVE > ENCODERS_AVAILABLE
#error ENCODERS_ACTIVE cannot exceed the available number of encoders defined by the board.
#endif

#if ENCODERS_ACTIVE > 5
#error ENCODERS_ACTIVE cannot exceed the software limit of 5.
#endif

#if ENCODERS_ACTIVE < 0
#error ENCODERS_ACTIVE cannot be less than 0.
#endif

#if ENCODER_SAMPLES_UNTIL_VALID > 255
#error ENCODER_SAMPLES_UNTIL_VALID cannot exceed 255.
#endif

#if ENCODER_SAMPLES_UNTIL_VALID < 0
#error ENCODER_SAMPLES_UNTIL_VALID cannot be less than 0.
#endif
