cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pull in Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(rp2040-logic-analyzer C CXX)

# Initialise the Pico SDK
pico_sdk_init()

# Add FatFS SPI library
add_subdirectory(FatFs_SPI)

# Add executable. Default name is the project name, version 0.2

add_executable(rp2040-logic-analyzer rp2040-logic-analyzer.c )

pico_set_program_name(rp2040-logic-analyzer "rp2040-logic-analyzer")
pico_set_program_version(rp2040-logic-analyzer "0.2")

pico_enable_stdio_uart(rp2040-logic-analyzer 0)
pico_enable_stdio_usb(rp2040-logic-analyzer 1)

# Add the standard library to the build
target_link_libraries(rp2040-logic-analyzer FatFs_SPI pico_stdlib hardware_pio hardware_dma)

target_compile_definitions(rp2040-logic-analyzer PUBLIC N_SD_CARDS=1)

pico_add_extra_outputs(rp2040-logic-analyzer)

