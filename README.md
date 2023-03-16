pico-sdk linking bug demonstration repository
=============================================

This repository contains demonstration code, that shows how 
build gets broken for projects, which separate their code into
static libraries and then provide explicit data placing inside
the linker script.

This project contains minimal reproduction case.

main.c and library.c are two source files which both define one function.
CMakeLists.txt defines one executable and one library. Both link against
pico_stdlib because both are using pico-sdk functions (gpio).

Customized linker script is provided, which performs explicit placement of
librarie's .bss section. This may be necessary if MPU is being used as ARM
MPU requires data to be size-aligned.

~~~~~~~~~~~~
cmake -DPICO_SDK_PATH=<path_to_pic_sdk> -B build
cmake --build build
~~~~~~~~~~~~

Will yield a lot of linker errors due to duplicated symbols (because pico_stdlib
got compiled twice; once for main application and once for linked library).

If `-DNOBUG=1` argument is added to CMake during build system generation, then
customized linker script is not used and build passes.

