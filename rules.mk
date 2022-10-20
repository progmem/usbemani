ifeq ($(TARGET_CONTROLLER),)
ifeq ($(TARGET_CONFIG),)

.PHONY: clean

clean:
	$(info Performing cleanup...)
	@rm -rf ./build/* ./obj/*

endif
endif

ifneq ($(TARGET_CONTROLLER),)
ifneq ($(TARGET_CONFIG),)

BUILD_TAG = [${TARGET_CONTROLLER}:${TARGET_CONFIG}]
$(info ${BUILD_TAG} Initializing build system)

CLEAN_NAME  = $(subst /,_,$(TARGET_CONTROLLER))_$(subst /,_,$(TARGET_CONFIG))
ROOT_DIR    = $(CURDIR)
TARGET      = $(CURDIR)/build/$(CLEAN_NAME)
OBJDIR      = $(CURDIR)/obj/$(CLEAN_NAME)

SRC         = $(wildcard $(ROOT_DIR)/controllers/$(TARGET_CONTROLLER)/*.c)
SRC        += $(wildcard $(ROOT_DIR)/configs/$(TARGET_CONTROLLER)/$(TARGET_CONFIG)/*.c)

$(info ${BUILD_TAG} Establishing include hierarchy)
include common/rules.mk

include controllers/$(TARGET_CONTROLLER)/rules.mk
# User config rules are optional and should be given an opportunity to override
-include configs/$(TARGET_CONTROLLER)/$(TARGET_CONFIG)/rules.mk
include boards/$(TARGET_BOARD)/rules.mk

$(info ${BUILD_TAG} Targeting ${TARGET_ARCH})
include arch/$(TARGET_ARCH)/rules.mk

INCLUDES += $(ROOT_DIR)/controllers/$(TARGET_CONTROLLER)/
INCLUDES += $(ROOT_DIR)/boards/$(TARGET_BOARD)/
INCLUDES += $(ROOT_DIR)/configs/$(TARGET_CONTROLLER)/$(TARGET_CONFIG)/

# INCLUDE_DIRS = $(foreach include,$(INCLUDES),-I$(include))
# CC_FLAGS    += $(INCLUDE_DIRS)

PRINT_INCLUDES = $(filter -I%,$(CC_FLAGS))
$(info ${BUILD_TAG} Including $(words $(PRINT_INCLUDES)) directories:)
$(foreach include,$(subst -I,,$(PRINT_INCLUDES)),$(info -> $(include)))

$(info ${BUILD_TAG} Including $(words $(SRC)) source file(s):)
$(foreach source,$(SRC),$(info -> $(source)))

$(info ${BUILD_TAG} Build system ${TARGET_ARCH}:${BUILD_SYSTEM} ready)
$(info ${BUILD_TAG} Delegating ${CLEAN_NAME}...)
$(info -----)

endif
endif
