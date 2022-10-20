SHELL = /bin/bash

ALL_BOARDS = $(shell find -s boards -type f -iname 'config.h' -exec dirname {} \; | cut -d'/' -f2- | paste -s -d' ' -)
ALL_CONTROLLERS = $(shell find -s controllers -type f -iname 'config.h' -exec dirname {} \; | cut -d'/' -f2- | paste -s -d' ' -)
ALL_CONFIGS = $(shell find -s configs -type f -iname 'config.h' -exec dirname {} \; | cut -d'/' -f2- | paste -s -d' ' -)

.DEFAULT_GOAL := help
.PHONY: help list-boards list-controllers list-configs %

%:
	$(eval TEST_TARGET_CONTROLLER = $(shell cut -d: -f1 <<< "$@::"))
	$(eval TEST_TARGET_CONFIG     = $(shell cut -d: -f2 <<< "$@::"))
	$(eval BUILD_TARGET_VARS      := $(or $(BUILD_TARGET_VARS),$(shell if [ ! -z "$(TEST_TARGET_CONTROLLER)" ]	&& [ ! -z "$(TEST_TARGET_CONFIG)" ]; then echo TARGET_CONTROLLER=$(TEST_TARGET_CONTROLLER) TARGET_CONFIG=$(TEST_TARGET_CONFIG); fi)))
	$(eval TARGETS  += $@)
	$(eval REAL_TARGETS += $(shell if [ -z "$(TEST_TARGET_CONTROLLER)" ] || [ -z "$(TEST_TARGET_CONFIG)" ]; then echo $@; fi))
	@if [ "$(TARGETS)" == "$(MAKECMDGOALS)" ]; then export FINAL_TARGETS="$(REAL_TARGETS)"; make $(BUILD_TARGET_VARS) -f rules.mk $${FINAL_TARGETS:-all}; fi

help:
	$(info -= USBemani Build System Runner =-)
	$(info )
	$(info -= Basic targets =-)
	$(info -> list-boards      : List all available boards)
	$(info -> list-controllers : List all available controllers)
	$(info -> list-configs     : List all available user configurations)
	$(info -> clean            : Perform a cleanup of all build artifacts)
	$(info -> help             : Print this help text)
	$(info )
	$(info To build a specific firmware, run 'make <board>:<config>')
	$(info Firmware builds will be available in the 'build' folder)
	$(info -> e.g. make examples/arduino/pro-micro/iidx:default)
	@exit 0

list-boards:
	@for board in $(ALL_BOARDS); do \
	  echo "$$board";\
  done

list-controllers:
	@for controller in $(ALL_CONTROLLERS); do \
	  echo "$$controller";\
	done

list-configs:
	@for config in $(ALL_CONFIGS); do \
	  echo "$$config";\
	done
