IF(NOT DEFINED FPU)  
    SET(FPU "-mfloat-abi=hard -mfpu=fpv5-d16")  
ENDIF()  

IF(NOT DEFINED SPECS)  
    SET(SPECS "--specs=nano.specs --specs=nosys.specs")  
ENDIF()  

IF(NOT DEFINED DEBUG_CONSOLE_CONFIG)  
    SET(DEBUG_CONSOLE_CONFIG "-DSDK_DEBUGCONSOLE=1")  
ENDIF()  

SET(CMAKE_ASM_FLAGS_RELEASE " \
    ${CMAKE_ASM_FLAGS_RELEASE} \
    -D__STARTUP_INITIALIZE_NONCACHEDATA \
    -D__STARTUP_CLEAR_BSS \
    -DNO_CRP \
    -D__PERFORMANCE_IMPLEMENTATION \
    -DMCUXPRESSO_SDK \
    -DCPU_MIMX8ML8DVNLZ_cm7 \
    -mthumb \
    -mcpu=cortex-m7 \
    ${FPU} \
")
SET(CMAKE_C_FLAGS_RELEASE " \
    ${CMAKE_C_FLAGS_RELEASE} \
    -include ${ProjDirPath}/../mcux_config.h \
    -DNDEBUG \
    -DSRTM_DEBUG_MESSAGE_FUNC=DbgConsole_Printf \
    -DSRTM_DEBUG_VERBOSE_LEVEL=SRTM_DEBUG_VERBOSE_WARN \
    -DNOT_CONFIG_CLK_ROOT=1 \
    -DSRTM_PDM_SDMA_ADAPTER_USE_HWVAD=0 \
    -DSRTM_PDM_SDMA_ADAPTER_FORCE_LOCAL_AND_EXTRA_BUFFERS=1 \
    -DDEMO_SAI_TX_CONFIG_StopOnSuspend=1 \
    -DDEMO_SAI_TX_CONFIG_UseLocalBuf=0 \
    -DSRTM_SAI_CONFIG_Rx_Enabled=0 \
    -DSRTM_SAI_CONFIG_SupportLocalBuf=0 \
    -DMCUX_META_BUILD \
    -DMCUXPRESSO_SDK \
    -DCPU_MIMX8ML8DVNLZ_cm7 \
    -DDISABLEFLOAT16 \
    -DSDK_I2C_BASED_COMPONENT_USED=1 \
    -DCODEC_MULTI_ADAPTERS=1 \
    -DCODEC_WM8962_ENABLE \
    -DSDK_OS_FREE_RTOS \
    -Os \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -std=gnu99 \
    -mcpu=cortex-m7 \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_CXX_FLAGS_RELEASE " \
    ${CMAKE_CXX_FLAGS_RELEASE} \
    -DNDEBUG \
    -DMCUX_META_BUILD \
    -DMCUXPRESSO_SDK \
    -DCPU_MIMX8ML8DVNLZ_cm7 \
    -DSDK_OS_FREE_RTOS \
    -Os \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -fno-rtti \
    -fno-exceptions \
    -mcpu=cortex-m7 \
    ${FPU} \
    ${DEBUG_CONSOLE_CONFIG} \
")
SET(CMAKE_EXE_LINKER_FLAGS_RELEASE " \
    ${CMAKE_EXE_LINKER_FLAGS_RELEASE} \
    -Xlinker \
    --defsym=__stack_size__=0x0080 \
    -Xlinker \
    --defsym=__heap_size__=0x12C00 \
    -Xlinker \
    -Map=output.map \
    -Wall \
    -fno-common \
    -ffunction-sections \
    -fdata-sections \
    -fno-builtin \
    -mthumb \
    -mapcs \
    -Wl,--gc-sections \
    -Wl,-static \
    -Wl,-z \
    -Wl,muldefs \
    -Wl,-Map=output.map \
    -Wl,--print-memory-usage \
    -mcpu=cortex-m7 \
    ${FPU} \
    ${SPECS} \
    -T\"${ProjDirPath}/MIMX8ML8xxxxx_cm7_lpv_ram.ld\" -static \
")
