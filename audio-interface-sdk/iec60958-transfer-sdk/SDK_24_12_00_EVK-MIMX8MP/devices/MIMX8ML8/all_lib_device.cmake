# Copy variable into project config.cmake to use software component
#set.board.evkmimx8mp
#  # description: Board_project_template evkmimx8mp
#  set(CONFIG_USE_board_project_template true)

#set.device.MIMX8ML8
#  # description: Clock Driver
#  set(CONFIG_USE_driver_clock true)

#  # description: IOMUXC Driver
#  set(CONFIG_USE_driver_iomuxc true)

#  # description: MEMORY Driver
#  set(CONFIG_USE_driver_memory true)

#  # description: AUDIOMIX Driver
#  set(CONFIG_USE_driver_audiomix true)

#  # description: Utilities which is needed for particular toolchain like the SBRK function required to address limitation between HEAP and STACK in GCC toolchain library.
#  set(CONFIG_USE_utilities_misc_utilities true)

#  # description: Used to include slave core binary into master core binary.
#  set(CONFIG_USE_utility_incbin true)

#  # description: Utility debug_console Template Config
#  set(CONFIG_USE_utility_debug_console_template_config true)

#  # description: common Driver
#  set(CONFIG_USE_driver_common true)

#  # description: Driver srtm audio service
#  set(CONFIG_USE_component_srtm_audio_service true)

#  # description: Driver srtm i2c service
#  set(CONFIG_USE_component_srtm_i2c_service true)

#  # description: Driver srtm auto service
#  set(CONFIG_USE_component_srtm_auto_service true)

#  # description: Driver srtm io service
#  set(CONFIG_USE_component_srtm_io_service true)

#  # description: Driver srtm keypad service
#  set(CONFIG_USE_component_srtm_keypad_service true)

#  # description: Driver srtm lfcl service
#  set(CONFIG_USE_component_srtm_lfcl_service true)

#  # description: Driver srtm netc service
#  set(CONFIG_USE_component_srtm_netc_service true)

#  # description: Driver srtm pmic service
#  set(CONFIG_USE_component_srtm_pmic_service true)

#  # description: Driver srtm rtc service
#  set(CONFIG_USE_component_srtm_rtc_service true)

#  # description: Driver srtm sensor service
#  set(CONFIG_USE_component_srtm_sensor_service true)

#  # description: Driver srtm snvs lp rtc adapter
#  set(CONFIG_USE_component_srtm_snvs_lp_rtc_adapter true)

#  # description: Driver srtm freertos
#  set(CONFIG_USE_driver_srtm_freertos true)

#  # description: Driver silicon_id imx8
#  set(CONFIG_USE_component_silicon_id_imx8 true)

#  # description: Driver silicon_id imx93
#  set(CONFIG_USE_component_silicon_id_imx93 true)

#  # description: Driver silicon_id rt10xx
#  set(CONFIG_USE_component_silicon_id_imxrt10xx true)

#  # description: Driver silicon_id imxrt1170
#  set(CONFIG_USE_component_silicon_id_imxrt1170 true)

#  # description: Driver silicon_id imxrt1180
#  set(CONFIG_USE_component_silicon_id_imxrt1180 true)

#  # description: Driver silicon_id rw610
#  set(CONFIG_USE_component_silicon_id_rw610 true)

#  # description: Driver silicon_id scfw
#  set(CONFIG_USE_component_silicon_id_scfw true)

#  # description: Component serial_manager_swo
#  set(CONFIG_USE_component_serial_manager_swo true)

#  # description: Component serial_manager_virtual
#  set(CONFIG_USE_component_serial_manager_virtual true)

#  # description: Component ak4497 adapter for single codec
#  set(CONFIG_USE_component_ak4497_adapter true)

#  # description: Component codec adapters for multi codec
#  set(CONFIG_USE_component_codec_adapters true)

#  # description: Component cs42448 adapter for single codec
#  set(CONFIG_USE_component_cs42448_adapter true)

#  # description: Component cs42888 adapter for single codec
#  set(CONFIG_USE_component_cs42888_adapter true)

#  # description: Component da7212 adapter for single codec
#  set(CONFIG_USE_component_da7212_adapter true)

#  # description: Component pcm186x adapter for single codec
#  set(CONFIG_USE_component_pcm186x_adapter true)

#  # description: Component pcm512x adapter for single codec
#  set(CONFIG_USE_component_pcm512x_adapter true)

#  # description: Component sgtl5000 adapter for single codec
#  set(CONFIG_USE_component_sgtl_adapter true)

#  # description: Component tfa9896 adapter for single codec
#  set(CONFIG_USE_component_tfa9896_adapter true)

#  # description: Component tfa9xxx adapter for single codec
#  set(CONFIG_USE_component_tfa9xxx_adapter true)

#  # description: Component wm8524 adapter for single codec
#  set(CONFIG_USE_component_wm8524_adapter true)

#  # description: Component wm8904 adapter for single codec
#  set(CONFIG_USE_component_wm8904_adapter true)

#  # description: Component wm8960 adapter for single codecs
#  set(CONFIG_USE_component_wm8960_adapter true)

#  # description: Component wm8962 adapter for single codecs
#  set(CONFIG_USE_component_wm8962_adapter true)

#  # description: Driver codec
#  set(CONFIG_USE_driver_codec true)

#  # description: Rte_device
#  set(CONFIG_USE_device_RTE true)

#  # description: ENET Driver
#  set(CONFIG_USE_driver_enet true)

#  # description: ENET QoS Driver
#  set(CONFIG_USE_driver_enet_qos true)

#  # description: SDMA Driver
#  set(CONFIG_USE_driver_sdma true)

#  # description: ECSPI SDMA Driver
#  set(CONFIG_USE_driver_ecspi_sdma true)

#  # description: IUART SDMA Driver
#  set(CONFIG_USE_driver_iuart_sdma true)

#  # description: SAI SDMA Driver
#  set(CONFIG_USE_driver_sai_sdma true)

#  # description: Component serial_manager_uart
#  set(CONFIG_USE_component_serial_manager_uart true)

#  # description: Utility debug_console_lite
#  set(CONFIG_USE_utility_debug_console_lite true)

#  # description: Device MIMX8ML8_cmsis
#  set(CONFIG_USE_device_CMSIS true)

#  # description: Device MIMX8ML8_system
#  set(CONFIG_USE_device_system true)

#  # description: Device MIMX8ML8_startup
#  set(CONFIG_USE_device_startup true)

#  # description: Utility str
#  set(CONFIG_USE_utility_str true)

#  # description: Utility debug_console
#  set(CONFIG_USE_utility_debug_console true)

#  # description: Utility assert
#  set(CONFIG_USE_utility_assert true)

#  # description: Utility assert_lite
#  set(CONFIG_USE_utility_assert_lite true)

#  # description: IUART Freertos Driver
#  set(CONFIG_USE_driver_iuart_freertos true)

#  # description: I2C Freertos Driver
#  set(CONFIG_USE_driver_ii2c_freertos true)

#  # description: ECSPI FreeRTOS Driver
#  set(CONFIG_USE_driver_ecspi_freertos true)

#  # description: wdog01 Driver
#  set(CONFIG_USE_driver_wdog01 true)

#  # description: TMU Driver
#  set(CONFIG_USE_driver_tmu_2 true)

#  # description: SEMA4 Driver
#  set(CONFIG_USE_driver_sema4 true)

#  # description: SAI Driver
#  set(CONFIG_USE_driver_sai true)

#  # description: Audio XCVR Driver
#  set(CONFIG_USE_driver_xcvr true)

#  # description: RDC SEMA42 Driver
#  set(CONFIG_USE_driver_rdc_sema42 true)

#  # description: RDC Driver
#  set(CONFIG_USE_driver_rdc true)

#  # description: PDM Driver
#  set(CONFIG_USE_driver_pdm true)

#  # description: PDM SDMA Driver
#  set(CONFIG_USE_driver_pdm_sdma true)

#  # description: MU Driver
#  set(CONFIG_USE_driver_mu true)

#  # description: IUART Driver
#  set(CONFIG_USE_driver_iuart true)

#  # description: UART CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_iuart true)

#  # description: PWM Driver
#  set(CONFIG_USE_driver_ipwm true)

#  # description: I2C Driver
#  set(CONFIG_USE_driver_ii2c true)

#  # description: I2C CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_ii2c true)

#  # description: GPIO Driver
#  set(CONFIG_USE_driver_igpio true)

#  # description: GPT Driver
#  set(CONFIG_USE_driver_gpt true)

#  # description: GPC Driver
#  set(CONFIG_USE_driver_gpc_2 true)

#  # description: FLEXCAN Driver
#  set(CONFIG_USE_driver_flexcan true)

#  # description: ENET CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_enet true)

#  # description: ECSPI Driver
#  set(CONFIG_USE_driver_ecspi true)

#  # description: ECSPI CMSIS Driver
#  set(CONFIG_USE_driver_cmsis_ecspi true)

#  # description: asrc Driver
#  set(CONFIG_USE_driver_easrc true)

#  # description: asrc_sdma Driver
#  set(CONFIG_USE_driver_easrc_sdma true)

#  # description: CACHE Driver
#  set(CONFIG_USE_driver_cache_armv7_m7 true)

#  # description: Component iuart_adapter
#  set(CONFIG_USE_component_iuart_adapter true)

#  # description: Driver srtm rpmsg endpoint
#  set(CONFIG_USE_component_rpmsg_endpoint true)

#  # description: Driver srtm i2c codec adapter
#  set(CONFIG_USE_component_srtm_i2c_codec_adapter true)

#  # description: Driver srtm pdm sdma adapter
#  set(CONFIG_USE_component_srtm_pdm_sdma_adapter true)

#  # description: Driver srtm sai sdma adapter
#  set(CONFIG_USE_component_srtm_sai_sdma_adapter true)

#  # description: Driver srtm wm8524 adapter
#  set(CONFIG_USE_component_srtm_wm8524_adapter true)

#  # description: Driver srtm
#  set(CONFIG_USE_driver_srtm true)

#  # description: Driver silicon_id
#  set(CONFIG_USE_component_silicon_id true)

#  # description: Component serial_manager
#  set(CONFIG_USE_component_serial_manager true)

#  # description: Driver phy-common
#  set(CONFIG_USE_component_eth_phy_common true)

#  # description: Driver phy-device-aqr113c
#  set(CONFIG_USE_component_phyaqr113c true)

#  # description: Driver phy-device-ar8031
#  set(CONFIG_USE_component_phyar8031 true)

#  # description: Driver phy-device-dp83848
#  set(CONFIG_USE_component_phydp83848 true)

#  # description: Driver phy-device-ksz8041
#  set(CONFIG_USE_component_phyksz8041 true)

#  # description: Driver phy-device-ksz8081
#  set(CONFIG_USE_component_phyksz8081 true)

#  # description: Driver phy-device-lan8720a
#  set(CONFIG_USE_component_phylan8720a true)

#  # description: Driver phy-device-lan8741
#  set(CONFIG_USE_component_phylan8741 true)

#  # description: Driver phy-device-rtl8201
#  set(CONFIG_USE_component_phyrtl8201 true)

#  # description: Driver phy-device-rtl8211f
#  set(CONFIG_USE_component_phyrtl8211f true)

#  # description: Driver phy-device-vsc8541
#  set(CONFIG_USE_component_phyvsc8541 true)

#  # description: Component lists
#  set(CONFIG_USE_component_lists true)

#  # description: Component ii2c_adapter
#  set(CONFIG_USE_component_ii2c_adapter true)

#  # description: Component i2c_adapter_interface
#  set(CONFIG_USE_component_i2c_adapter_interface true)

#  # description: Component codec_i2c
#  set(CONFIG_USE_component_codec_i2c true)

#  # description: Driver ak4497
#  set(CONFIG_USE_driver_ak4497 true)

#  # description: Driver cs42448
#  set(CONFIG_USE_driver_cs42448 true)

#  # description: Driver cs42888
#  set(CONFIG_USE_driver_cs42888 true)

#  # description: Driver dialog7212
#  set(CONFIG_USE_driver_dialog7212 true)

#  # description: Driver pcm186x
#  set(CONFIG_USE_driver_pcm186x true)

#  # description: Driver pcm512x
#  set(CONFIG_USE_driver_pcm512x true)

#  # description: Driver sgtl5000
#  set(CONFIG_USE_driver_sgtl5000 true)

#  # description: Driver tfa9896
#  set(CONFIG_USE_driver_tfa9896 true)

#  # description: Driver tfa9xxx
#  set(CONFIG_USE_driver_tfa9xxx true)

#  # description: Driver tfa9xxx_hal
#  set(CONFIG_USE_driver_tfa9xxx_hal true)

#  # description: Driver wm8524
#  set(CONFIG_USE_driver_wm8524 true)

#  # description: Driver wm8904
#  set(CONFIG_USE_driver_wm8904 true)

#  # description: Driver wm8960
#  set(CONFIG_USE_driver_wm8960 true)

#  # description: Driver wm8962
#  set(CONFIG_USE_driver_wm8962 true)

#set.CMSIS_DSP_Lib
#  # description: CMSIS-DSP Library Header
#  set(CONFIG_USE_CMSIS_DSP_Include true)

#  # description: CMSIS-DSP Library
#  set(CONFIG_USE_CMSIS_DSP_Source true)

#set.CMSIS
#  # description: Device interrupt controller interface
#  set(CONFIG_USE_CMSIS_Device_API_OSTick true)

#  # description: CMSIS-RTOS API for Cortex-M, SC000, and SC300
#  set(CONFIG_USE_CMSIS_Device_API_RTOS2 true)

#  # description: Access to #include Driver_CAN.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_CAN true)

#  # description: Access to #include Driver_ETH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet true)

#  # description: Access to #include Driver_ETH_MAC.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_MAC true)

#  # description: Access to #include Driver_ETH_PHY.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Ethernet_PHY true)

#  # description: Access to #include Driver_Flash.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_Flash true)

#  # description: Access to #include Driver_GPIO.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_GPIO true)

#  # description: Access to #include Driver_I2C.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_I2C true)

#  # description: Access to #include Driver_MCI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_MCI true)

#  # description: Access to #include Driver_NAND.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_NAND true)

#  # description: Access to #include Driver_SAI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SAI true)

#  # description: Access to #include Driver_SPI.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_SPI true)

#  # description: Access to #include Driver_USART.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USART true)

#  # description: Access to #include Driver_USBD.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Device true)

#  # description: Access to #include Driver_USBH.h file for custom implementation
#  set(CONFIG_USE_CMSIS_Driver_Include_USB_Host true)

#  # description: Access to #include Driver_WiFi.h file
#  set(CONFIG_USE_CMSIS_Driver_Include_WiFi true)

#  # description: CMSIS-NN Library
#  set(CONFIG_USE_CMSIS_NN_Source true)

#  # description: CMSIS-CORE for Cortex-M, ARMv8-M, ARMv8.1-M
#  set(CONFIG_USE_CMSIS_Include_core_cm true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_RTX true)

#  # description: CMSIS-RTOS2 RTX5 for Cortex-M, SC000, C300 and Armv8-M (Library)
#  set(CONFIG_USE_CMSIS_RTOS2_RTX_LIB true)

#set.middleware.tinycbor
#  # description: Concise Binary Object Representation (CBOR) Library
#  set(CONFIG_USE_middleware_tinycbor true)

#set.middleware.pkcs11
#  # description: Public Key Cryptography Standard #11 defines generic cryptographic token interface.
#  set(CONFIG_USE_middleware_pkcs11 true)

#set.middleware.multicore
#  # description: Remote Processor component
#  set(CONFIG_USE_middleware_multicore_remoteproc true)

#  # description: remoteproc-load script
#  set(CONFIG_USE_middleware_multicore_remoteproc_loadscript true)

#  # description: MCMgr
#  set(CONFIG_USE_middleware_multicore_mcmgr true)

#  # description: eRPC
#  set(CONFIG_USE_middleware_multicore_erpc true)

#  # description: eRPC
#  set(CONFIG_USE_middleware_multicore_erpc_doc true)

#  # description: RPMsg-Lite BM environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_bm true)

#  # description: RPMsg-Lite FreeRTOS environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_freertos true)

#  # description: RPMsg-Lite XOS environment layer sources
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_xos true)

#  # description: RPMsg-Lite QNX environment layer sources
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_qnx true)

#  # description: RPMsg-Lite ThreadX environment layer sources
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_threadx true)

#  # description: RPMsg-Lite Zephyr environment sources
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_zephyr true)

#  # description: RPMsg-Lite
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite true)

#  # description: RPMsg-Lite NS
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_ns true)

#  # description: RPMsg-Lite Queue
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_queue true)

#  # description: RPMsg-Lite for evkmimx8mp application
#  set(CONFIG_USE_middleware_multicore_rpmsg-lite_imx8mp_m7 true)

#  # description: eRPC_client
#  set(CONFIG_USE_middleware_multicore_erpc_client true)

#  # description: eRPC_server
#  set(CONFIG_USE_middleware_multicore_erpc_server true)

#  # description: eRPC_arbitrator
#  set(CONFIG_USE_middleware_multicore_erpc_arbitrator true)

#  # description: eRPC_port_stdlib
#  set(CONFIG_USE_middleware_multicore_erpc_port_stdlib true)

#  # description: eRPC_port_freertos
#  set(CONFIG_USE_middleware_multicore_erpc_port_freertos true)

#  # description: eRPC_mu_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_mu_transport true)

#  # description: eRPC_rpmsg_lite_transport_master
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_transport_master true)

#  # description: eRPC_rpmsg_lite_transport_remote
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_transport_remote true)

#  # description: eRPC_rpmsg_lite_rtos_transport_master
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport_master true)

#  # description: eRPC_rpmsg_lite_rtos_transport_remote
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport_remote true)

#  # description: eRPC_rpmsg_tty_rtos_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_rpmsg_tty_rtos_transport true)

#  # description: eRPC_uart_cmsis_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_uart_cmsis_transport true)

#  # description: eRPC_dspi_master_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_dspi_master_transport true)

#  # description: eRPC_dspi_slave_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_dspi_slave_transport true)

#  # description: eRPC_spi_master_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_spi_master_transport true)

#  # description: eRPC_spi_slave_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_spi_slave_transport true)

#  # description: eRPC_lpspi_slave_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_lpspi_slave_transport true)

#  # description: eRPC_i2c_slave_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_i2c_slave_transport true)

#  # description: eRPC_lpi2c_slave_transport
#  set(CONFIG_USE_middleware_multicore_erpc_eRPC_lpi2c_slave_transport true)

#  # description: eRPC
#  set(CONFIG_USE_middleware_multicore_erpc_examples_erpc_common_multicore true)

#  # description: erpc_examples Matrix Multiply Client
#  set(CONFIG_USE_middleware_multicore_erpc_examples_erpc_matrix_multiply_client true)

#  # description: erpc_examples Matrix Multiply Server
#  set(CONFIG_USE_middleware_multicore_erpc_examples_erpc_matrix_multiply_server true)

#  # description: erpc_examples Two Way RPC core0
#  set(CONFIG_USE_middleware_multicore_erpc_examples_erpc_two_way_rpc_core0 true)

#  # description: erpc_examples Two Way RPC core1
#  set(CONFIG_USE_middleware_multicore_erpc_examples_erpc_two_way_rpc_core1 true)

#set.middleware.freertos-kernel
#  # description: FreeRTOS kernel
#  set(CONFIG_USE_middleware_freertos-kernel true)

#  # description: FreeRTOS NXP extension
#  set(CONFIG_USE_middleware_freertos-kernel_extension true)

#  # description: FreeRTOS heap 1
#  set(CONFIG_USE_middleware_freertos-kernel_heap_1 true)

#  # description: FreeRTOS heap 2
#  set(CONFIG_USE_middleware_freertos-kernel_heap_2 true)

#  # description: FreeRTOS heap 3
#  set(CONFIG_USE_middleware_freertos-kernel_heap_3 true)

#  # description: FreeRTOS heap 4
#  set(CONFIG_USE_middleware_freertos-kernel_heap_4 true)

#  # description: FreeRTOS heap 5
#  set(CONFIG_USE_middleware_freertos-kernel_heap_5 true)

#  # description: old FreeRTOS MPU wrappers used before V10.6.0
#  set(CONFIG_USE_middleware_freertos-kernel_mpu_wrappers true)

#  # description: new V2 FreeRTOS MPU wrappers introduced in V10.6.0
#  set(CONFIG_USE_middleware_freertos-kernel_mpu_wrappers_v2 true)

#  # description: Template configuration file to be edited by user. Provides also memory allocator (heap_x), change variant if needed.
#  set(CONFIG_USE_middleware_freertos-kernel_config true)

#set.middleware.voice_spot
#  # description: Voice Spot Hey NXP model
#  set(CONFIG_USE_middleware_voice_spot_model true)

#  # description: Voice Spot library for Cortex M7
#  set(CONFIG_USE_middleware_voice_spot_cm7_iMX8MP true)

#set.middleware.audio_voice.components.voice_seeker
#  # description: Voice seeker library for Cortex M7
#  set(CONFIG_USE_middleware_audio_voice_components_voice_seeker_cm7 true)

#  # description: Voice seeker memory utilities for Cortex M7
#  set(CONFIG_USE_middleware_audio_voice_components_voice_seeker_rdsp_utilities_public_cm7 true)

#set.middleware.llhttp
#  # description: HTTP parser in LLVM IR
#  set(CONFIG_USE_middleware_llhttp true)

#set.middleware.fmstr
#  # description: Common FreeMASTER driver code.
#  set(CONFIG_USE_middleware_fmstr true)

#  # description: FreeMASTER driver code for 32bit platforms, enabling communication between FreeMASTER or FreeMASTER Lite tools and MCU application. Supports Serial, CAN, USB and BDM/JTAG physical interface.
#  set(CONFIG_USE_middleware_fmstr_platform_gen32le true)

#  # description: FreeMASTER driver code for DSC platforms, enabling communication between FreeMASTER or FreeMASTER Lite tools and MCU application. Supports Serial, CAN, USB and BDM/JTAG physical interface.
#  set(CONFIG_USE_middleware_fmstr_platform_56f800e true)

#  # description: FreeMASTER driver code for S32 platform.
#  set(CONFIG_USE_middleware_fmstr_platform_s32 true)

#  # description: FreeMASTER driver code for Power Architecture 32bit platform.
#  set(CONFIG_USE_middleware_fmstr_platform_pa32 true)

#  # description: FreeMASTER driver code for S12Z platform.
#  set(CONFIG_USE_middleware_fmstr_platform_s12z true)

list(APPEND CMAKE_MODULE_PATH
  ${CMAKE_CURRENT_LIST_DIR}/.
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Core/Include
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/DSP
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/Driver
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/NN
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2
  ${CMAKE_CURRENT_LIST_DIR}/../../CMSIS/RTOS2/Include
  ${CMAKE_CURRENT_LIST_DIR}/../../boards/evkmimx8mp/project_template
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/ak4497
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/cs42448
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/cs42888
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/da7212
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/i2c
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/pcm186x
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/pcm512x
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/sgtl5000
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/tfa9896
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/tfa9xxx
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8524
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8904
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8960
  ${CMAKE_CURRENT_LIST_DIR}/../../components/codec/wm8962
  ${CMAKE_CURRENT_LIST_DIR}/../../components/i2c
  ${CMAKE_CURRENT_LIST_DIR}/../../components/lists
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyaqr113c
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyar8031
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phydp83848
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8041
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyksz8081
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phylan8720a
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phylan8741
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyrtl8201
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyrtl8211f
  ${CMAKE_CURRENT_LIST_DIR}/../../components/phy/device/phyvsc8541
  ${CMAKE_CURRENT_LIST_DIR}/../../components/serial_manager
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/imx8
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/imx93
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/imxrt1170
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/imxrt1180
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/rt10xx
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/rw610
  ${CMAKE_CURRENT_LIST_DIR}/../../components/silicon_id/socs/scfw
  ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm
  ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/port
  ${CMAKE_CURRENT_LIST_DIR}/../../components/srtm/services
  ${CMAKE_CURRENT_LIST_DIR}/../../components/uart
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/audio_voice/components/voice_seeker/ARM_CortexM7
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/audio_voice/components/voice_seeker/ARM_CortexM7/rdsp_utilities_public
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/audio_voice/components/voice_spot
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/freemaster
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/llhttp
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/multicore
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/pkcs11
  ${CMAKE_CURRENT_LIST_DIR}/../../middleware/tinycbor
  ${CMAKE_CURRENT_LIST_DIR}/../../rtos/freertos/freertos-kernel
  ${CMAKE_CURRENT_LIST_DIR}/cmsis_drivers
  ${CMAKE_CURRENT_LIST_DIR}/drivers
  ${CMAKE_CURRENT_LIST_DIR}/template
  ${CMAKE_CURRENT_LIST_DIR}/utilities
  ${CMAKE_CURRENT_LIST_DIR}/utilities/debug_console_lite
  ${CMAKE_CURRENT_LIST_DIR}/utilities/incbin
)

include_if_use(CMSIS_DSP_Include)
include_if_use(CMSIS_DSP_Source)
include_if_use(CMSIS_Device_API_OSTick)
include_if_use(CMSIS_Device_API_RTOS2)
include_if_use(CMSIS_Driver_Include_CAN)
include_if_use(CMSIS_Driver_Include_Ethernet)
include_if_use(CMSIS_Driver_Include_Ethernet_MAC)
include_if_use(CMSIS_Driver_Include_Ethernet_PHY)
include_if_use(CMSIS_Driver_Include_Flash)
include_if_use(CMSIS_Driver_Include_GPIO)
include_if_use(CMSIS_Driver_Include_I2C)
include_if_use(CMSIS_Driver_Include_MCI)
include_if_use(CMSIS_Driver_Include_NAND)
include_if_use(CMSIS_Driver_Include_SAI)
include_if_use(CMSIS_Driver_Include_SPI)
include_if_use(CMSIS_Driver_Include_USART)
include_if_use(CMSIS_Driver_Include_USB_Device)
include_if_use(CMSIS_Driver_Include_USB_Host)
include_if_use(CMSIS_Driver_Include_WiFi)
include_if_use(CMSIS_Include_core_cm)
include_if_use(CMSIS_NN_Source)
include_if_use(CMSIS_RTOS2_RTX)
include_if_use(CMSIS_RTOS2_RTX_LIB)
include_if_use(board_project_template)
include_if_use(component_ak4497_adapter.MIMX8ML8)
include_if_use(component_codec_adapters.MIMX8ML8)
include_if_use(component_codec_i2c.MIMX8ML8)
include_if_use(component_cs42448_adapter.MIMX8ML8)
include_if_use(component_cs42888_adapter.MIMX8ML8)
include_if_use(component_da7212_adapter.MIMX8ML8)
include_if_use(component_eth_phy_common.MIMX8ML8)
include_if_use(component_i2c_adapter_interface.MIMX8ML8)
include_if_use(component_ii2c_adapter.MIMX8ML8)
include_if_use(component_iuart_adapter.MIMX8ML8)
include_if_use(component_lists.MIMX8ML8)
include_if_use(component_pcm186x_adapter.MIMX8ML8)
include_if_use(component_pcm512x_adapter.MIMX8ML8)
include_if_use(component_phyaqr113c.MIMX8ML8)
include_if_use(component_phyar8031.MIMX8ML8)
include_if_use(component_phydp83848.MIMX8ML8)
include_if_use(component_phyksz8041.MIMX8ML8)
include_if_use(component_phyksz8081.MIMX8ML8)
include_if_use(component_phylan8720a.MIMX8ML8)
include_if_use(component_phylan8741.MIMX8ML8)
include_if_use(component_phyrtl8201.MIMX8ML8)
include_if_use(component_phyrtl8211f.MIMX8ML8)
include_if_use(component_phyvsc8541.MIMX8ML8)
include_if_use(component_rpmsg_endpoint.MIMX8ML8)
include_if_use(component_serial_manager.MIMX8ML8)
include_if_use(component_serial_manager_swo.MIMX8ML8)
include_if_use(component_serial_manager_uart.MIMX8ML8)
include_if_use(component_serial_manager_virtual.MIMX8ML8)
include_if_use(component_sgtl_adapter.MIMX8ML8)
include_if_use(component_silicon_id.MIMX8ML8)
include_if_use(component_silicon_id_imx8.MIMX8ML8)
include_if_use(component_silicon_id_imx93.MIMX8ML8)
include_if_use(component_silicon_id_imxrt10xx.MIMX8ML8)
include_if_use(component_silicon_id_imxrt1170.MIMX8ML8)
include_if_use(component_silicon_id_imxrt1180.MIMX8ML8)
include_if_use(component_silicon_id_rw610.MIMX8ML8)
include_if_use(component_silicon_id_scfw.MIMX8ML8)
include_if_use(component_srtm_audio_service.MIMX8ML8)
include_if_use(component_srtm_auto_service.MIMX8ML8)
include_if_use(component_srtm_i2c_codec_adapter.MIMX8ML8)
include_if_use(component_srtm_i2c_service.MIMX8ML8)
include_if_use(component_srtm_io_service.MIMX8ML8)
include_if_use(component_srtm_keypad_service.MIMX8ML8)
include_if_use(component_srtm_lfcl_service.MIMX8ML8)
include_if_use(component_srtm_netc_service.MIMX8ML8)
include_if_use(component_srtm_pdm_sdma_adapter.MIMX8ML8)
include_if_use(component_srtm_pmic_service.MIMX8ML8)
include_if_use(component_srtm_rtc_service.MIMX8ML8)
include_if_use(component_srtm_sai_sdma_adapter.MIMX8ML8)
include_if_use(component_srtm_sensor_service.MIMX8ML8)
include_if_use(component_srtm_snvs_lp_rtc_adapter.MIMX8ML8)
include_if_use(component_srtm_wm8524_adapter.MIMX8ML8)
include_if_use(component_tfa9896_adapter.MIMX8ML8)
include_if_use(component_tfa9xxx_adapter.MIMX8ML8)
include_if_use(component_wm8524_adapter.MIMX8ML8)
include_if_use(component_wm8904_adapter.MIMX8ML8)
include_if_use(component_wm8960_adapter.MIMX8ML8)
include_if_use(component_wm8962_adapter.MIMX8ML8)
include_if_use(device_CMSIS.MIMX8ML8)
include_if_use(device_RTE.MIMX8ML8)
include_if_use(device_startup.MIMX8ML8)
include_if_use(device_system.MIMX8ML8)
include_if_use(driver_ak4497.MIMX8ML8)
include_if_use(driver_audiomix.MIMX8ML8)
include_if_use(driver_cache_armv7_m7.MIMX8ML8)
include_if_use(driver_clock.MIMX8ML8)
include_if_use(driver_cmsis_ecspi.MIMX8ML8)
include_if_use(driver_cmsis_enet.MIMX8ML8)
include_if_use(driver_cmsis_ii2c.MIMX8ML8)
include_if_use(driver_cmsis_iuart.MIMX8ML8)
include_if_use(driver_codec.MIMX8ML8)
include_if_use(driver_common.MIMX8ML8)
include_if_use(driver_cs42448.MIMX8ML8)
include_if_use(driver_cs42888.MIMX8ML8)
include_if_use(driver_dialog7212.MIMX8ML8)
include_if_use(driver_easrc.MIMX8ML8)
include_if_use(driver_easrc_sdma.MIMX8ML8)
include_if_use(driver_ecspi.MIMX8ML8)
include_if_use(driver_ecspi_freertos.MIMX8ML8)
include_if_use(driver_ecspi_sdma.MIMX8ML8)
include_if_use(driver_enet.MIMX8ML8)
include_if_use(driver_enet_qos.MIMX8ML8)
include_if_use(driver_flexcan.MIMX8ML8)
include_if_use(driver_gpc_2.MIMX8ML8)
include_if_use(driver_gpt.MIMX8ML8)
include_if_use(driver_igpio.MIMX8ML8)
include_if_use(driver_ii2c.MIMX8ML8)
include_if_use(driver_ii2c_freertos.MIMX8ML8)
include_if_use(driver_iomuxc.MIMX8ML8)
include_if_use(driver_ipwm.MIMX8ML8)
include_if_use(driver_iuart.MIMX8ML8)
include_if_use(driver_iuart_freertos.MIMX8ML8)
include_if_use(driver_iuart_sdma.MIMX8ML8)
include_if_use(driver_memory.MIMX8ML8)
include_if_use(driver_mu.MIMX8ML8)
include_if_use(driver_pcm186x.MIMX8ML8)
include_if_use(driver_pcm512x.MIMX8ML8)
include_if_use(driver_pdm.MIMX8ML8)
include_if_use(driver_pdm_sdma.MIMX8ML8)
include_if_use(driver_rdc.MIMX8ML8)
include_if_use(driver_rdc_sema42.MIMX8ML8)
include_if_use(driver_sai.MIMX8ML8)
include_if_use(driver_xcvr.MIMX8ML8)
include_if_use(driver_sai_sdma.MIMX8ML8)
include_if_use(driver_sdma.MIMX8ML8)
include_if_use(driver_sema4.MIMX8ML8)
include_if_use(driver_sgtl5000.MIMX8ML8)
include_if_use(driver_srtm.MIMX8ML8)
include_if_use(driver_srtm_freertos.MIMX8ML8)
include_if_use(driver_tfa9896.MIMX8ML8)
include_if_use(driver_tfa9xxx.MIMX8ML8)
include_if_use(driver_tfa9xxx_hal.MIMX8ML8)
include_if_use(driver_tmu_2.MIMX8ML8)
include_if_use(driver_wdog01.MIMX8ML8)
include_if_use(driver_wm8524.MIMX8ML8)
include_if_use(driver_wm8904.MIMX8ML8)
include_if_use(driver_wm8960.MIMX8ML8)
include_if_use(driver_wm8962.MIMX8ML8)
include_if_use(middleware_audio_voice_components_voice_seeker_cm7)
include_if_use(middleware_audio_voice_components_voice_seeker_rdsp_utilities_public_cm7)
include_if_use(middleware_fmstr)
include_if_use(middleware_fmstr_platform_56f800e)
include_if_use(middleware_fmstr_platform_gen32le)
include_if_use(middleware_fmstr_platform_pa32)
include_if_use(middleware_fmstr_platform_s12z)
include_if_use(middleware_fmstr_platform_s32)
include_if_use(middleware_freertos-kernel)
include_if_use(middleware_freertos-kernel_config)
include_if_use(middleware_freertos-kernel_extension)
include_if_use(middleware_freertos-kernel_heap_1)
include_if_use(middleware_freertos-kernel_heap_2)
include_if_use(middleware_freertos-kernel_heap_3)
include_if_use(middleware_freertos-kernel_heap_4)
include_if_use(middleware_freertos-kernel_heap_5)
include_if_use(middleware_freertos-kernel_mpu_wrappers)
include_if_use(middleware_freertos-kernel_mpu_wrappers_v2)
include_if_use(middleware_llhttp)
include_if_use(middleware_multicore_erpc)
include_if_use(middleware_multicore_erpc_arbitrator)
include_if_use(middleware_multicore_erpc_client)
include_if_use(middleware_multicore_erpc_doc)
include_if_use(middleware_multicore_erpc_eRPC_dspi_master_transport)
include_if_use(middleware_multicore_erpc_eRPC_dspi_slave_transport)
include_if_use(middleware_multicore_erpc_eRPC_i2c_slave_transport)
include_if_use(middleware_multicore_erpc_eRPC_lpi2c_slave_transport)
include_if_use(middleware_multicore_erpc_eRPC_lpspi_slave_transport)
include_if_use(middleware_multicore_erpc_eRPC_mu_transport)
include_if_use(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport_master)
include_if_use(middleware_multicore_erpc_eRPC_rpmsg_lite_rtos_transport_remote)
include_if_use(middleware_multicore_erpc_eRPC_rpmsg_lite_transport_master)
include_if_use(middleware_multicore_erpc_eRPC_rpmsg_lite_transport_remote)
include_if_use(middleware_multicore_erpc_eRPC_rpmsg_tty_rtos_transport)
include_if_use(middleware_multicore_erpc_eRPC_spi_master_transport)
include_if_use(middleware_multicore_erpc_eRPC_spi_slave_transport)
include_if_use(middleware_multicore_erpc_eRPC_uart_cmsis_transport)
include_if_use(middleware_multicore_erpc_examples_erpc_common_multicore)
include_if_use(middleware_multicore_erpc_examples_erpc_matrix_multiply_client)
include_if_use(middleware_multicore_erpc_examples_erpc_matrix_multiply_server)
include_if_use(middleware_multicore_erpc_examples_erpc_two_way_rpc_core0)
include_if_use(middleware_multicore_erpc_examples_erpc_two_way_rpc_core1)
include_if_use(middleware_multicore_erpc_port_freertos)
include_if_use(middleware_multicore_erpc_port_stdlib)
include_if_use(middleware_multicore_erpc_server)
include_if_use(middleware_multicore_mcmgr)
include_if_use(middleware_multicore_remoteproc)
include_if_use(middleware_multicore_remoteproc_loadscript)
include_if_use(middleware_multicore_rpmsg-lite)
include_if_use(middleware_multicore_rpmsg-lite_bm)
include_if_use(middleware_multicore_rpmsg-lite_freertos)
include_if_use(middleware_multicore_rpmsg-lite_imx8mp_m7)
include_if_use(middleware_multicore_rpmsg-lite_ns)
include_if_use(middleware_multicore_rpmsg-lite_qnx)
include_if_use(middleware_multicore_rpmsg-lite_queue)
include_if_use(middleware_multicore_rpmsg-lite_threadx)
include_if_use(middleware_multicore_rpmsg-lite_xos)
include_if_use(middleware_multicore_rpmsg-lite_zephyr)
include_if_use(middleware_pkcs11)
include_if_use(middleware_tinycbor)
include_if_use(middleware_voice_spot_cm7_iMX8MP)
include_if_use(middleware_voice_spot_model)
include_if_use(utilities_misc_utilities.MIMX8ML8)
include_if_use(utility_assert.MIMX8ML8)
include_if_use(utility_assert_lite.MIMX8ML8)
include_if_use(utility_debug_console.MIMX8ML8)
include_if_use(utility_debug_console_lite.MIMX8ML8)
include_if_use(utility_debug_console_template_config.MIMX8ML8)
include_if_use(utility_incbin.MIMX8ML8)
include_if_use(utility_str.MIMX8ML8)
