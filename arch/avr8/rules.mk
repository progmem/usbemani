BUILD_SYSTEM = DMBS
ARCH         = AVR8
ARCH_PATH    = $(ROOT_DIR)/arch/avr8
LUFA_PATH    = lib/lufa/LUFA

SRC += $(wildcard $(ARCH_PATH)/*.c)
SRC += $(wildcard $(ARCH_PATH)/impl/*.c)
SRC += $(LUFA_SRC_USB)

INCLUDES += $(ARCH_PATH)/lufa/
INCLUDES += $(ARCH_PATH)/
INCLUDE_DIRS = $(foreach include,$(INCLUDES),-I$(include))

F_USB         = $(F_CPU)
OPTIMIZATION  = 2
CC_FLAGS     += -Werror -DMCU=$(MCU) -DUSE_LUFA_CONFIG_HEADER $(INCLUDE_DIRS)
LD_FLAGS      =

# Include LUFA-specific DMBS extension modules
DMBS_LUFA_PATH ?= $(LUFA_PATH)/Build/LUFA
include $(DMBS_LUFA_PATH)/lufa-sources.mk
include $(DMBS_LUFA_PATH)/lufa-gcc.mk

# Include common DMBS build system modules
DMBS_PATH      ?= $(LUFA_PATH)/Build/DMBS/DMBS
include $(DMBS_PATH)/core.mk
include $(DMBS_PATH)/cppcheck.mk
include $(DMBS_PATH)/doxygen.mk
include $(DMBS_PATH)/dfu.mk
include $(DMBS_PATH)/gcc.mk
include $(DMBS_PATH)/hid.mk
include $(DMBS_PATH)/avrdude.mk
include $(DMBS_PATH)/atprogram.mk