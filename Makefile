SHELL = /bin/bash

ALL_BOARDS = $(shell find boards -type f -iname 'config.h' -exec dirname {} \; | cut -d'/' -f2- | paste -s -d' ' -)
ALL_CONTROLLERS = $(shell find controllers -type f -iname 'config.h' -exec dirname {} \; | cut -d'/' -f2- | paste -s -d' ' -)
ALL_LAYOUTS = $(shell find layouts -type f -iname 'config.h' -exec dirname {} \; | cut -d'/' -f2- | paste -s -d' ' -)

.DEFAULT_GOAL := help
.PHONY: help list-boards list-controllers list-configs %

%:
	@mkdir -p ./build ./obj
	$(eval TARGET_PARAM_COUNT     := $(shell tr -cd ':' <<< "$@" | wc -c))
	$(eval TARGET_LAYOUT_POS      := $(shell echo $$(( $(TARGET_PARAM_COUNT) + 1 ))))
	$(eval TARGET_CONTROLLER_POS  := $(shell echo $$(( $(TARGET_PARAM_COUNT) ))))
	$(eval TARGET_BOARD_POS       := $(shell echo $$(( $(TARGET_PARAM_COUNT) - 1 ))))
	$(eval TARGET_LAYOUT          := $(shell [ $(TARGET_LAYOUT_POS)      -gt 0 ] && cut -d ':' -f $(TARGET_LAYOUT_POS)     <<< "$@" ))
	$(eval TARGET_CONTROLLER      := $(shell [ $(TARGET_CONTROLLER_POS)  -gt 0 ] && cut -d ':' -f $(TARGET_CONTROLLER_POS) <<< "$@" ))
	$(eval TARGET_BOARD           := $(shell [ $(TARGET_BOARD_POS)       -gt 0 ] && cut -d ':' -f $(TARGET_BOARD_POS)      <<< "$@" ))
	$(eval FOUND_LAYOUT           := $(or $(filter $(TARGET_LAYOUT),    $(ALL_LAYOUTS))))
	$(eval FOUND_CONTROLLER       := $(or $(filter $(TARGET_CONTROLLER),$(ALL_CONTROLLERS))))
	$(eval FOUND_BOARD            := $(or $(filter $(TARGET_BOARD),     $(ALL_BOARDS))))
	$(eval BUILD_LAYOUT           := $(or $(BUILD_LAYOUT),     $(shell if [ ! -z "$(TARGET_LAYOUT)" ] && [ "$(FOUND_LAYOUT)"      == "$(TARGET_LAYOUT)"     ] ; then echo TARGET_LAYOUT=$(TARGET_LAYOUT); fi )))
	$(eval BUILD_CONTROLLER       := $(or $(BUILD_CONTROLLER), $(shell if [ ! -z "$(BUILD_LAYOUT)" ] && [ ! -z "$(TARGET_CONTROLLER)" ] ; then if [ "$(FOUND_CONTROLLER)" == "$(TARGET_CONTROLLER)" ] ; then echo TARGET_CONTROLLER=$(TARGET_CONTROLLER); else echo !INVALID; fi; fi)))
	$(eval BUILD_BOARD            := $(or $(BUILD_BOARD),      $(shell if [ ! -z "$(BUILD_LAYOUT)" ] && [ ! -z "$(TARGET_BOARD)"      ] ; then if [ "$(FOUND_BOARD)"      == "$(TARGET_BOARD)"      ] ; then echo TARGET_BOARD=$(TARGET_BOARD); else echo !INVALID; fi; fi)))
	$(eval TARGETS += $@)
	$(eval REAL_TARGETS += $(shell if [ -z "$(FOUND_LAYOUT)" ]; then echo $@; fi))
	@if [ "$(TARGETS)" == "$(MAKECMDGOALS)" ] ; then if [ "$(BUILD_LAYOUT)" != "!INVALID" ] && [ "$(BUILD_CONTROLLER)" != "!INVALID" ] && [ "$(BUILD_BOARD)" != "!INVALID" ] ; then export FINAL_TARGETS="$(REAL_TARGETS)" ; make $(BUILD_LAYOUT) $(BUILD_CONTROLLER) $(BUILD_BOARD) -f rules.mk $${FINAL_TARGETS:-all}; exit $? ; else echo "One or more components of the make target do not exist!" ; echo "Please review your target and correct any errors." ; echo "Run 'make help' for more information on build targets."; exit 1 ; fi ; fi


help:
	$(info -= USBemani Build System Runner =-)
	$(info )
	$(info -= Basic targets =-)
	$(info -> list-boards      : List all available boards)
	$(info -> list-controllers : List all available controllers)
	$(info -> list-layouts     : List all available user layouts/configs)
	$(info -> clean            : Perform a cleanup of all build artifacts)
	$(info -> help             : Print this help text)
	$(info )
	$(info To build a specific firmware, run one of the following:)
	$(info -> make <layout>)
	$(info -> make <controller>:<layout>)
	$(info -> make <board>::<layout>)
	$(info -> make <board>:<controller>:<layout>)
	@exit 0

list-boards:
	@for board in $(ALL_BOARDS); do \
	  echo "$$board";\
  done

list-controllers:
	@for controller in $(ALL_CONTROLLERS); do \
	  echo "$$controller";\
	done

list-layouts:
	@for layout in $(ALL_LAYOUTS); do \
	  echo "$$layout";\
	done
