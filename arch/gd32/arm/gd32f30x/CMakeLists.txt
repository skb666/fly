add_library(arch-gd32f30x OBJECT EXCLUDE_FROM_ALL)

target_compile_definitions(arch-gd32f30x PUBLIC -DUSE_STDPERIPH_DRIVER)
target_include_directories(arch-gd32f30x PUBLIC "${CMAKE_CURRENT_LIST_DIR}/CMSIS/GD/GD32F30x/Include")
target_include_directories(arch-gd32f30x PUBLIC "${CMAKE_CURRENT_LIST_DIR}/CMSIS/")
target_include_directories(arch-gd32f30x PUBLIC "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Include")
target_sources(arch-gd32f30x PRIVATE  "${CMAKE_CURRENT_LIST_DIR}/CMSIS/GD/GD32F30x/Source/system_gd32f30x.c")
target_sources(arch-gd32f30x PRIVATE  "${CMAKE_CURRENT_LIST_DIR}/CMSIS/GD/GD32F30x/Source/GCC/startup_gd32f30x_hd.S")
target_sources(arch-gd32f30x PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_adc.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_bkp.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_can.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_crc.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_ctc.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_dac.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_dbg.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_dma.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_enet.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_exmc.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_exti.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_fmc.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_fwdgt.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_gpio.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_i2c.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_misc.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_pmu.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_rcu.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_rtc.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_sdio.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_spi.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_timer.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_usart.c"
    "${CMAKE_CURRENT_LIST_DIR}/GD32F30x_standard_peripheral/Source/gd32f30x_wwdgt.c"
)
    