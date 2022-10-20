BUILD_SYSTEM = CMake
ARCH         = pico
ARCH_PATH    = $(ROOT_DIR)/arch/pico

SRC += $(wildcard $(ARCH_PATH)/*.c)
SRC += $(wildcard $(ARCH_PATH)/impl/*.c)

INCLUDES += $(ARCH_PATH)/tinyusb/
INCLUDES += $(ARCH_PATH)/

.PHONY: all clean cmake_prep

cmake_prep:
	@mkdir -p $(OBJDIR)/.generated && cd $(OBJDIR) && cmake -DTARGET_NAME=${CLEAN_NAME} -DROOT_DIR=$(ROOT_DIR) $(ROOT_DIR)/arch/pico/ -DOBJ_DIR=$(OBJDIR) -DINCLUDES="$(INCLUDES)" -DSRC="$(SRC)"

all: cmake_prep
	@cd $(OBJDIR) && make

clean: cmake_prep
	@cd $(OBJDIR) && make clean
