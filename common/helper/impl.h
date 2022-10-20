#pragma once

/* Generic Include */
#define _INCLUDE_QUOTE(x)   #x
#define _INCLUDE(x)         _INCLUDE_QUOTE(x)

/* Implementations */
#define INCLUDE(x, y, z)          _INCLUDE(x/y.z)
#define INCLUDE_IMPL(x, y, z)     _INCLUDE(impl/x/y.z)
#define INCLUDE_IMPL_RGB(x, y, z) _INCLUDE(impl/rgb/x.y.z)

/* Standard implementation */
/*
#define _IMPL_QUOTE(x)         #x
#define _IMPL(x)               _IMPL_QUOTE(x)
#define _IMPL_INCLUDE(x, y, z) _IMPL(impl/x/y.z)
*/

/* RGB implementation, to include both the driver and LED */
// #define _IMPL_RGB_INCLUDE(x, y, z) _IMPL(impl/rgb/x.y.z)
