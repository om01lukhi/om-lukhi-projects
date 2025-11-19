# CROSS COMPILER SETTING
set(CMAKE_SYSTEM_NAME Generic)
cmake_minimum_required(VERSION 3.10.0)

# THE VERSION NUMBER
SET (MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION 2)
SET (MCUXPRESSO_CMAKE_FORMAT_MINOR_VERSION 0)

include(ide_overrides.cmake OPTIONAL)

if(CMAKE_SCRIPT_MODE_FILE)
  message("${MCUXPRESSO_CMAKE_FORMAT_MAJOR_VERSION}")
  return()
endif()


set(CMAKE_STATIC_LIBRARY_PREFIX)
set(CMAKE_STATIC_LIBRARY_SUFFIX)

set(CMAKE_EXECUTABLE_LIBRARY_PREFIX)
set(CMAKE_EXECUTABLE_LIBRARY_SUFFIX)

# CURRENT DIRECTORY
set(ProjDirPath ${CMAKE_CURRENT_SOURCE_DIR})

set(EXECUTABLE_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})
set(LIBRARY_OUTPUT_PATH ${ProjDirPath}/${CMAKE_BUILD_TYPE})

project(xcvr_iec958)

enable_language(ASM)

set(MCUX_BUILD_TYPES debug flash_debug ddr_debug release flash_release ddr_release)

set(MCUX_SDK_PROJECT_NAME xcvr_iec958.elf)

if (NOT DEFINED SdkRootDirPath)
    SET(SdkRootDirPath ${ProjDirPath}/../../../../..)
endif()

include(${ProjDirPath}/flags.cmake)

include(${ProjDirPath}/config.cmake)

add_executable(${MCUX_SDK_PROJECT_NAME}
"${ProjDirPath}/../my_app.c"
"${ProjDirPath}/../board.h"
"${ProjDirPath}/../board.c"
"${ProjDirPath}/../clock_config.h"
"${ProjDirPath}/../clock_config.c"
"${ProjDirPath}/../pin_mux.c"
"${ProjDirPath}/../pin_mux.h"
"${ProjDirPath}/../hardware_init.c"
"${ProjDirPath}/../app.h"
"${ProjDirPath}/../mcux_config.h"
"${ProjDirPath}/../../../../../devices/MIMX8ML8/drivers/fsl_sdma.c"
"${ProjDirPath}/../../../../../devices/MIMX8ML8/drivers/fsl_sdma.h"
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PRIVATE
    ${ProjDirPath}/..
)


include(${SdkRootDirPath}/devices/MIMX8ML8/all_lib_device.cmake)

IF(NOT DEFINED TARGET_LINK_SYSTEM_LIBRARIES)
    SET(TARGET_LINK_SYSTEM_LIBRARIES "-lm -lc -lgcc -lnosys")
ENDIF()

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--start-group)

target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE ${TARGET_LINK_SYSTEM_LIBRARIES})

TARGET_LINK_LIBRARIES(${MCUX_SDK_PROJECT_NAME} PRIVATE -Wl,--end-group)

ADD_CUSTOM_COMMAND(TARGET ${MCUX_SDK_PROJECT_NAME} POST_BUILD COMMAND ${CMAKE_OBJCOPY}
-Obinary ${EXECUTABLE_OUTPUT_PATH}/${MCUX_SDK_PROJECT_NAME} ${EXECUTABLE_OUTPUT_PATH}/xcvr_iec958.bin)

set_target_properties(${MCUX_SDK_PROJECT_NAME} PROPERTIES ADDITIONAL_CLEAN_FILES "output.map;${EXECUTABLE_OUTPUT_PATH}/xcvr_iec958.bin")

# wrap all libraries with -Wl,--start-group -Wl,--end-group to prevent link order issue
group_link_libraries()

if(DEFINED ENV{BUILD_OPTIONS})
    set(OPTIONS_STRING "$ENV{BUILD_OPTIONS}")
    message(STATUS "Build options: ${OPTIONS_STRING}")

    # Check for IRQ option (override default DMA)
    string(FIND "${OPTIONS_STRING}" "IRQ" IRQ_POS)
    if(NOT IRQ_POS EQUAL -1)
        add_compile_definitions(USE_IRQ_METHOD)
        message(STATUS "Using IRQ transfer method")
    endif()

    # Check for XCVR_FILL_IEC60958_FRAME option (override default NO_FRAME_FILL_BY_XCVR)
    string(FIND "${OPTIONS_STRING}" "XCVR_FILL_IEC60958_FRAME" XCVR_POS)
    if(NOT XCVR_POS EQUAL -1)
        add_compile_definitions(XCVR_FILL_IEC60958_FRAME)
        message(STATUS "Using XCVR to fill IEC60958 frame")

        # Only check for sampling frequency options if XCVR_FILL_IEC60958_FRAME is enabled
        string(FIND "${OPTIONS_STRING}" "SAMPLING_FREQUENCY_48K" FREQ48_POS)
        string(FIND "${OPTIONS_STRING}" "SAMPLING_FREQUENCY_44K" FREQ44_POS)

        if(NOT FREQ48_POS EQUAL -1)
            add_compile_definitions(SAMPLING_FREQUENCY_48K)
            message(STATUS "Sampling frequency set to 48 kHz")
        elseif(NOT FREQ44_POS EQUAL -1)
            add_compile_definitions(SAMPLING_FREQUENCY_44K)
            message(STATUS "Sampling frequency set to 44.1 kHz")
        else()
            add_compile_definitions(SAMPLING_FREQUENCY_48K)
            message(WARNING "No sampling frequency defined (44.1kHz or 48kHz). Default 48k is applied.")
        endif()

        #Check for bits per sample options
        string(FIND "${OPTIONS_STRING}" "BITS_PER_SAMPLE_8" BPS8_POS)
        string(FIND "${OPTIONS_STRING}" "BITS_PER_SAMPLE_16" BPS16_POS)
        string(FIND "${OPTIONS_STRING}" "BITS_PER_SAMPLE_24" BPS24_POS)
        string(FIND "${OPTIONS_STRING}" "BITS_PER_SAMPLE_32" BPS32_POS)

        set(bits_defined 0)

        if(NOT BPS8_POS EQUAL -1)
            add_compile_definitions(BITS_PER_SAMPLE_8)
            message(STATUS "Bits per sample: 8")
        elseif(NOT BPS16_POS EQUAL -1)
            add_compile_definitions(BITS_PER_SAMPLE_16)
            message(STATUS "Bits per sample: 16")
        elseif(NOT BPS24_POS EQUAL -1)
            add_compile_definitions(BITS_PER_SAMPLE_24)
            message(STATUS "Bits per sample: 24")
        elseif(NOT BPS32_POS EQUAL -1)
            add_compile_definitions(BITS_PER_SAMPLE_32)
            message(STATUS "Bits per sample: 32")
        elseif(bits_defined GREATER 1)
            message(FATAL_ERROR "Multiple bits-per-sample options defined! Choose only one of: 8, 16, 24, 32, Format: BITS_PER_SAMPLE_x")
        elseif(bits_defined EQUAL 0)
            add_compile_definitions(BITS_PER_SAMPLE_16)
            message(WARNING "No bits-per-sample defined. Default configuration is taken 16 bits per sample.")
        endif()

    endif()
else()
    message(STATUS "Using application defaults: DMA + NO_FRAME_FILL_BY_XCVR")
endif()
