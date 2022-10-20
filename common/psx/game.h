#pragma once
#include "callbacks.h"

#define _PSX_QUOTE(x)          #x
#define _PSX(x)                _PSX_QUOTE(x)
#define _PSX_INCLUDE(x, y)     _PSX(psx/game/x.y)
