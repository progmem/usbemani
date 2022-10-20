#pragma once
#include <stdlib.h>
#include <stdint.h>

#include "impl/color.h"

void HSV_Brighten(HSV_Color_t *color, uint8_t value);
void HSV_Dim(HSV_Color_t *color, uint8_t value);

RGB_Color_t HSV_ToRGB(HSV_Color_t hsv);