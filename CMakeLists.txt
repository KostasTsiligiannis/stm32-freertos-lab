cmake_minimum_required(VERSION 3.22)

# Ορισμός Toolchain πριν το project()
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/cubeide-gcc.cmake")

project(stm32f303-freertos-lab C ASM)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Flags για STM32F303K8 (ARM Cortex-M4F)
set(MCU_FLAGS
    -mcpu=cortex-m4
    -mthumb
    -mfpu=fpv4-sp-d16
    -mfloat-abi=hard
)

add_compile_options(
    ${MCU_FLAGS}
    -Wall
    -Wextra
    -ffunction-sections
    -fdata-sections
)

add_compile_definitions(
    USE_HAL_DRIVER
    STM32F303x8
)

# Συλλογή Source Files
file(GLOB APP_SOURCES "app/*.c")
file(GLOB STARTUP_SOURCES "drivers/Startup/*.s")
file(GLOB HAL_SOURCES "drivers/STM32F3_Drivers/STM32F3xx_HAL_Driver/Src/*.c")
list(FILTER HAL_SOURCES EXCLUDE REGEX ".*_template\\.c$")

set(FREERTOS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/third_party/FreeRTOS-Kernel")
set(FREERTOS_SOURCES
    "${FREERTOS_DIR}/tasks.c"
    "${FREERTOS_DIR}/queue.c"
    "${FREERTOS_DIR}/list.c"
    "${FREERTOS_DIR}/timers.c"
    "${FREERTOS_DIR}/event_groups.c"
    "${FREERTOS_DIR}/stream_buffer.c"
    "${FREERTOS_DIR}/portable/GCC/ARM_CM4F/port.c"
    "${FREERTOS_DIR}/portable/MemMang/heap_4.c"
)

add_executable(${PROJECT_NAME}.elf
    ${APP_SOURCES}
    ${STARTUP_SOURCES}
    ${HAL_SOURCES}
    ${FREERTOS_SOURCES}
)

target_include_directories(${PROJECT_NAME}.elf PRIVATE
    app
    drivers/STM32F3_Drivers/CMSIS_Core/CMSIS/Core/Include
    drivers/STM32F3_Drivers/CMSIS_Device_F3/Include
    drivers/STM32F3_Drivers/STM32F3xx_HAL_Driver/Inc
    ${FREERTOS_DIR}/include
    ${FREERTOS_DIR}/portable/GCC/ARM_CM4F
)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    ${MCU_FLAGS}
    -T${CMAKE_CURRENT_SOURCE_DIR}/drivers/STM32F303K8TX_FLASH.ld
    -specs=nano.specs
    -Wl,-Map=${PROJECT_BINARY_DIR}/${PROJECT_NAME}.map,--cref
    -Wl,--gc-sections
    -static
    -Wl,--start-group -lc -lm -Wl,--end-group
)

add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.bin
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${PROJECT_NAME}.elf>
)
