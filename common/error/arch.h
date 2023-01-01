#pragma once

#if defined(BOARD_DEVELOPMENT) && !defined(LAYOUT_DEVELOPMENT)
#error Development boards can only be used with layouts that have been marked for use on development boards. Review your layout to verify it is suitable for a development board and add LAYOUT_DEVELOPMENT to confirm.
#endif

#if defined(LAYOUT_DEVELOPMENT) && !defined(BOARD_DEVELOPMENT)
#error Layouts marked for use on development boards can only be used with development boards. Review your layout and, if not targeting a development board, remove LAYOUT_DEVELOPMENT and try again.
#endif
