# The following provides a sample user layout for building a IIDX "premium model" controller with a Raspberry Pi Pico.
# This example targets the following by default:
# * The dev/raspberrypi/pico board
# * The examples/iidx/premium-model controller
# Each of these can be overridden, so they must be defined using the "?=" assignment, setting the board/controller only if they haven't already been set.

TARGET_BOARD      ?= dev/raspberrypi/pico
TARGET_CONTROLLER ?= examples/iidx/premium-model