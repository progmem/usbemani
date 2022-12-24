ifeq ($(TARGET_LAYOUT),)

.PHONY: clean

clean:
	$(info Performing cleanup...)
	@rm -rf ./build/* ./obj/*

endif



ifneq ($(TARGET_LAYOUT),)

SPACE :=
SPACE +=

ifeq '$(findstring ;,$(PATH))' ';'
    BUILD_OS := Windows
else
    BUILD_OS := $(shell uname 2>/dev/null || echo Unknown)
    BUILD_OS := $(patsubst CYGWIN%,Cygwin,$(BUILD_OS))
    BUILD_OS := $(patsubst MSYS%,MSYS,$(BUILD_OS))
    BUILD_OS := $(patsubst MINGW%,MSYS,$(BUILD_OS))
endif


_TARGET_1 := ${TARGET_BOARD}:${TARGET_CONTROLLER}:${TARGET_LAYOUT}
_TARGET_2 := $(_TARGET_1::%=%)
BUILD_TAG := $(_TARGET_2::%=%)
$(info [${BUILD_TAG}] Initializing build system)
$(info [${BUILD_TAG}] Building on ${BUILD_OS})

CLEAN_NAME  := $(subst :,_,$(subst /,_,$(BUILD_TAG)))
$(info [${BUILD_TAG}] Outputting: ${CLEAN_NAME})
ROOT_DIR    := $(CURDIR)
TARGET      := $(CURDIR)/build/$(CLEAN_NAME)
OBJDIR      := $(CURDIR)/obj/$(CLEAN_NAME)

# User layouts will determine which target controller and board to use unless overridden. Inherit in reverse order.
include common/rules.mk
include layouts/$(TARGET_LAYOUT)/rules.mk
ifeq ($(TARGET_CONTROLLER),)
  $(error No target controller specified!)
endif
-include controllers/$(TARGET_CONTROLLER)/rules.mk
ifeq ($(TARGET_BOARD),)
  $(error No target board specified!)
endif
-include boards/$(TARGET_BOARD)/rules.mk

$(info [${BUILD_TAG}] Targeting ${TARGET_ARCH})
include arch/$(TARGET_ARCH)/rules.mk

$(info [${BUILD_TAG}] Establishing include hierarchy)
INCLUDES += $(ROOT_DIR)/boards/$(TARGET_BOARD)/
INCLUDES += $(ROOT_DIR)/controllers/$(TARGET_CONTROLLER)/
INCLUDES += $(ROOT_DIR)/layouts/$(TARGET_LAYOUT)/

$(info [${BUILD_TAG}] Establishing source file list)
SRC      += $(wildcard $(ROOT_DIR)/boards/$(TARGET_BOARD)/*.c)
SRC      += $(wildcard $(ROOT_DIR)/controllers/$(TARGET_CONTROLLER)/*.c)
SRC      += $(wildcard $(ROOT_DIR)/layouts/$(TARGET_LAYOUT)/*.c)

PRINT_INCLUDES = $(filter -I%,$(CC_FLAGS))
$(info [${BUILD_TAG}] Including $(words $(INCLUDES)) directories:)
$(foreach include,$(subst -I,,$(INCLUDES)),$(info -> $(include)))

$(info [${BUILD_TAG}] Including $(words $(SRC)) source file(s):)
$(foreach source,$(SRC),$(info -> $(source)))

$(info [${BUILD_TAG}] Build system ${TARGET_ARCH}:${BUILD_SYSTEM} ready)
$(info [${BUILD_TAG}] Delegating ${CLEAN_NAME}...)
$(info -----)

endif
