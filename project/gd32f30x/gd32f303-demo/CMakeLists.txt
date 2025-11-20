cmake_minimum_required(VERSION 3.10)


project(gd32f303-demo LANGUAGES C CXX ASM)

set(TARGET_FLAGS 
    "-Wall"
    "-Wextra"
    "-Wconversion"
    "-Wno-sign-conversion"
    "-Wno-unused-parameter"
    "-Wno-psabi"
    "$<$<CONFIG:Debug>:-g;-O0>"
    "$<$<CONFIG:Release>:-g;-O3>"
    "$<$<CONFIG:MinSizeRel>:-g;-Os>"
)

target_compile_definitions(arch-gd32f30x PUBLIC
    -DGD32F30X_HD
    -DHXTAL_VALUE=8000000U
    -DGD_ECLIPSE_GCC
)

target_compile_options(segger-rtt PRIVATE 
    "-DBUFFER_SIZE_UP=4096"
)

# app程序生成
add_executable(gd32f303-demo )
target_link_libraries(gd32f303-demo segger-rtt arch-gd32f30x c m gcc  )

file(GLOB_RECURSE USER_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)
target_sources(gd32f303-demo PRIVATE 
    ${USER_SRCS}
)

target_include_directories(gd32f303-demo PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/inc/
)

target_compile_options(gd32f303-demo PRIVATE "${TARGET_FLAGS}")

# 设置默认的flash和RAM参数
set(FLASH_ORIGIN "0x08000000" CACHE STRING "Flash start address")
set(FLASH_LENGTH "256K" CACHE STRING "Flash size")
set(RAM_ORIGIN "0x20000000" CACHE STRING "RAM start address")
set(RAM_LENGTH "48K" CACHE STRING "RAM size")
set(STACK_SIZE "2K" CACHE STRING "Stack size")
set(HEAP_SIZE "1K" CACHE STRING "Heap size")

# 配置链接脚本
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/gd32f30x_flash.ld"
    "${CMAKE_CURRENT_BINARY_DIR}/gd32f30x_flash.ld"
)

target_link_options(gd32f303-demo  PRIVATE
    "-T${CMAKE_CURRENT_BINARY_DIR}/gd32f30x_flash.ld"
)

# 自动生成map
add_target_make_map(gd32f303-demo)
# 自动生成bin
add_target_make_bin(gd32f303-demo)
# 自动打印内存/存储占用
add_target_print_memory_usage(gd32f303-demo)

add_jlink_image( default
    IMAGE_NAME "GD32F303_DEMO"
    CHIP_NAME "GD32F303RCT6"
    FIRMWARE_LIST "APP:V0.0.1:0x08000000:gd32f303-demo.bin"
    DEPENDS gd32f303-demo
)

add_vscode_cortex_debug_gdb( default
    CHIP_NAME "GD32F303RCT6"
    ELF_NAME_LIST "gd32f303-demo"
    SERVER_TYPE "openocd"
    INTERFACE "swd"
    OTHER_EXT_CONFIG "${CMAKE_CURRENT_SOURCE_DIR}/debugconfig/ext-cortex-debug-config.json"
    RTT_DEBUG  ON
    DEPENDS gd32f303-demo
)