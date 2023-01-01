cmake_minimum_required(VERSION 3.13)

# Include pico-sdk functions
include(${ROOT_DIR}/lib/pico-sdk/pico_sdk_init.cmake)

# Build our list of include directories
set(INCLUDE_DIRS ${INCLUDES})
separate_arguments(INCLUDE_DIRS)

# Build our list of sources
set(SRC_FILES ${SRC})
separate_arguments(SRC)
separate_arguments(SRC_FILES)
# list(TRANSFORM SRC_FILES PREPEND ${ROOT_DIR}/)
# list(TRANSFORM SRC_FILES REPLACE ${ROOT_DIR}/ "")

# file(GLOB all_SRCS
#   ${ROOT_DIR}/usbemani/*.c
#   ${ROOT_DIR}/arch/pico/impl/*.c
# )

project(${TARGET_NAME})
pico_sdk_init()
add_executable(${TARGET_NAME})

target_compile_definitions(${TARGET_NAME} PUBLIC
  -DPICO_XOSC_STARTUP_DELAY_MULTIPLIER=64
)


add_definitions("-Wall -Werror")

# set_property(TARGET ${TARGET_NAME} PROPERTY C_STANDARD 17)
target_sources(${TARGET_NAME} PUBLIC
  ${SRC}
)

target_include_directories(${TARGET_NAME} PUBLIC
  ${OBJ_DIR}/generated/pio/
  ${INCLUDE_DIRS}
  ${ROOT_DIR}/.
)

# Build any found PIO files
file(GLOB_RECURSE all_PIOS
  LIST_DIRECTORIES false
  RELATIVE ${ROOT_DIR}/arch/pico/impl/
  *.pio
)
foreach(pio IN ITEMS ${all_PIOS})
  get_filename_component(relative_dir
    ${pio}
    DIRECTORY
  )
  file(MAKE_DIRECTORY
    ${OBJ_DIR}/generated/pio/${relative_dir}/
  )
  pico_generate_pio_header(
    ${TARGET_NAME}
    ${ROOT_DIR}/arch/pico/impl/${pio}
    OUTPUT_DIR ${OBJ_DIR}/generated/pio/${relative_dir}/
  )
endforeach()

target_link_libraries(${TARGET_NAME}
  pico_bootrom
  pico_stdlib
  pico_multicore
  hardware_adc
  hardware_clocks
  hardware_dma
  hardware_pio
  hardware_spi
  tinyusb_device
  tinyusb_board
)

# Build additional outputs, including .uf2
pico_add_extra_outputs(${TARGET_NAME})

# Relocate built files to the /build folder
add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
  COMMAND mv ${TARGET_NAME}.* ${ROOT_DIR}/build/
)
