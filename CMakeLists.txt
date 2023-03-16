cmake_minimum_required(VERSION 3.12)

if ("${PICO_SDK_PATH}" STREQUAL "")
    message(FATAL_ERROR "Please provide -DPICO_SDK_PATH=<path_to_sdk> to configure where the Raspberry Pi pico-SDK is deployed while running CMake.")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../pico-sdk/external")

# Pull in pico_sdk_import from SDK, don't maintain local copy
include(pico_sdk_import)

project(link-issue-demo LANGUAGES C CXX ASM)

add_definitions(-ffunction-sections -fdata-sections)

pico_sdk_init()

set(main_SRCS main.c)


set(library_SRCS library.c)
add_library(library STATIC ${library_SRCS})
target_link_libraries(library pico_stdlib)

add_executable(main ${main_SRCS})
target_link_libraries(main pico_stdlib library)

# Pass -DNOBUG=1 to link using standard linker script from pico-sdk
if (NOT "${NOBUG}" EQUAL 1)
    set_property(TARGET main PROPERTY PICO_TARGET_LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/memmap_default.ld)
endif()

pico_add_extra_outputs(main)
