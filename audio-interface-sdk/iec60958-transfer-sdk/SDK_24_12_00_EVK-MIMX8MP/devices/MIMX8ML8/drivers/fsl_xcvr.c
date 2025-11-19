#include "fsl_debug_console.h"
#include "fsl_audiomix.h"
#include "fsl_xcvr.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Structure definition for xcvr_private_handle_t. The structure is private. */
typedef struct _xcvr_private_handle
{
	EARC_Type *base;
	xcvr_callback_t xcvr_callback;
	xcvr_handle_t *handle;
} xcvr_private_handle_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*< Private handle only used for internally */
static xcvr_private_handle_t xcvr_private_handle;

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Configures the Audio XCVR PLLs.
 *
 * @param None
 */
static void XCVR_ConfigPlls(void);

/*!
 * @brief Configures the Audio XCVR clocks.
 *
 * @param None
 */
static void XCVR_ConfigClocks(void);

/*!
 * @brief Write to Audio Interface register through AI interface.
 *
 * @param base Audio XCVR base pointer
 * @param reg Register address
 * @param data Data to be written to register
 * @param phy true => phy, false => pll
 * @return 0 if success, -1 if error.
 */
static int xcvr_ai_write(EARC_Type * base, uint8_t reg, int data, bool phy);

/*!
 * @brief Set Audio PLL clock rate.
 *
 * @param base2 AUDIOMIX base pointer
 * @param freq Clock frequency in Hz
 */
static void set_clk_rate(AUDIOMIX_Type * base2, int freq);

/*!
 * @brief Enable Audio PLL with specific frequency.
 *
 * @param base Audio XCVR base pointer
 * @param base2 AUDIOMIX base pointer
 * @param freq Clock frequency in Hz
 * @return 0 if success, -1 if error.
 */
static int xcvr_en_aud_pll(EARC_Type * base, AUDIOMIX_Type * base2, int freq);

/*!
 * @brief SDMA callback function for XCVR Tx.
 *
 * This function is called when XCVR Tx transfer is finished.
 *
 * @param handle SDMA handle pointer.
 * @param userData Pointer to user data.
 * @param transferDone True if the transfer is done.
 * @param bdIndex The index of the finished BD.
 */
static void XCVR_TxSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void XCVR_ConfigPlls(void)
{
	/* Skip configuring AudioPLL when it's disabled by Acore. */
	if (0U != (AUDIOMIX->CLKEN1 & AUDIOMIX_CLKEN1_PLL_MASK))
	{
		AUDIOMIX_InitAudioPll(AUDIOMIX, &g_saiPLLConfig_EarcPhy); /* init SAI PLL run at 24000000Hz */
	}

	/* AUDIOMIX SAI PLL configuration */
	CLOCK_InitAudioPll1(&g_audioPllConfig);
	CLOCK_InitAudioPll2(&g_audioPllConfig);
}

static void XCVR_ConfigClocks(void)
{
	/* Configurating Root Audio Ahb for EARC and SPBA2 clock */
	CLOCK_SetRootDivider(kCLOCK_RootAudioAhb, 1U, 2U); //400MHz Clocks
	CLOCK_SetRootMux(kCLOCK_RootAudioAhb,kCLOCK_AudioAhbRootmuxSysPll1);

	/* Enable the Audio XCVR clock: EARC (CLKEN0[EARC]) */
    (void)CLOCK_EnableClock(kCLOCK_Earc);

    /* Enable the Audio XCVR clock: EARC PHY (CLKEN1[EARC_PHY]) */
    (void)CLOCK_EnableClock(kCLOCK_EarcPhy);

	/* Enable the Audio XCVR clock: SPBA2 (CLKEN0[SPBA2]) */
    (void)CLOCK_EnableClock(kCLOCK_Spba2);

	/* Enable the Audio XCVR clock: PLL (CLKEN1[PLL]) */
    (void)CLOCK_EnableClock(kCLOCK_Pll);

	/* Enable the Audio XCVR clock: SDMA3 (CLKEN0[SDMA3]) */
	(void)CLOCK_EnableClock(kCLOCK_Sdma3);
}

void XCVR_Init( app_instance_t *app, xcvr_handle_t *xcvrHandle)
{
	EARC_Type *base = app->earc_base;
    /* Assert M0+ reset */
    base->EXT_CTRL.RW |= EARC_EXT_CTRL_CORE_RESET_MASK;
	base->EXT_CTRL.RW &= ~EARC_EXT_CTRL_CORE_SLEEP_HOLD_REQ_B_MASK;

    /* Assert EARC reset */
    AUDIOMIX_AttachClk(AUDIOMIX, AUDIOMIX_ATTACH_ID(0X200U, 0x3U, 0U));

#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)

	/* Configure PLLs */
	XCVR_ConfigPlls();

	/* Configure clocks */
	XCVR_ConfigClocks();

#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */

	/* De-assert EARC reset */
    AUDIOMIX_AttachClk(AUDIOMIX, AUDIOMIX_ATTACH_ID(0X200U, 0x3U, 3U));

	/* Preserving base and handle to private handle */
	xcvr_private_handle.base = base;
	xcvr_private_handle.handle = xcvrHandle;
}

void XCVR_load_firmware(unsigned char* xcvr_imx8mp_bin, unsigned int len)
{
	int rem = len;
	int page = 0, off, out, size = FSL_XCVR_REG_OFFSET;
	int mask, val, reg_val;
	int timer_cnt;
	EARC_Type *base = xcvr_private_handle.base;

	/* RAM is 20KiB = 16KiB code + 4KiB data => max 10 pages 2KiB each */
	if (rem > 16384) {
		PRINTF("FW size %d is bigger than 16KiB.\n", rem);
	}

    unsigned char *ram_add = (unsigned char *)AUDIO_XCVR_RAM;

	for (page = 0; page < 10; page++) {

		reg_val = base->EXT_CTRL.RW;
		reg_val &= ~ EARC_EXT_CTRL_PAGE_MASK;
		reg_val |= EARC_EXT_CTRL_PAGE(page);
		base->EXT_CTRL.RW = reg_val;

		off = page * size;
		out = (rem < size) ? rem : size;

		if (out > 0) {
			/* write firmware into code memory */
			memcpy(ram_add, xcvr_imx8mp_bin + off, out);
			rem -= out;
			if (rem == 0) {
				/* last part of firmware written */
				/* clean remaining part of code memory page */
				memset(ram_add + out, 0, size - out);
			}
		} else {
			/* clean current page, including data memory */
			memset(ram_add, 0, size);
		}
	}

	val = base->EXT_CTRL.RW;

	mask = EARC_EXT_CTRL_RX_FIFO_WMARK_MASK | EARC_EXT_CTRL_TX_FIFO_WMARK_MASK;
	val = EARC_EXT_CTRL_RX_FIFO_WMARK(64);
    val = EARC_EXT_CTRL_TX_FIFO_WMARK(64);

    mask |= EARC_EXT_CTRL_SDMA_WR_REQ_DIS_MASK | EARC_EXT_CTRL_SDMA_RD_REQ_DIS_MASK;
    val |= EARC_EXT_CTRL_SDMA_WR_REQ_DIS_MASK | EARC_EXT_CTRL_SDMA_RD_REQ_DIS_MASK;

    mask |= EARC_EXT_CTRL_PAGE_MASK;
    val |= EARC_EXT_CTRL_PAGE(8);

    reg_val = base->EXT_CTRL.RW;
    reg_val &= ~mask;
    reg_val |= val;
	base->EXT_CTRL.RW = reg_val;

	/* Store Capabilities Data Structure into Data RAM*/
	// TO DO if required, not required as of now

	/* Release M0+ reset */
	base->EXT_CTRL.RW &= ~EARC_EXT_CTRL_CORE_RESET_MASK;

	/* Let M0+ core complete firmware initialization */
	timer_cnt = 50000000;
	while (timer_cnt--);

	PRINTF("Audio XCVR: Firmware loaded successfully!\r\n");
}

/** phy: true => phy, false => pll */
static int xcvr_ai_write(EARC_Type * base, uint8_t reg, int data, bool phy)
{
	int mask_toggle = 0, mask_toggle_done = 0, shift = 0;
	int val;

	mask_toggle  = phy ? EARC_PHY_AI_CTRL_TOG_1_MASK : EARC_PHY_AI_CTRL_TOG_0_MASK;
	mask_toggle_done = phy ? EARC_PHY_AI_CTRL_TOG_DONE_1_MASK : EARC_PHY_AI_CTRL_TOG_DONE_0_MASK;
	shift = phy ? EARC_PHY_AI_CTRL_TOG_1_SHIFT : EARC_PHY_AI_CTRL_TOG_0_SHIFT;

	/* Clear/Reset AI Address */
	/* Set AI Address */
	val = base->PHY_AI_CTRL.RW;
	val &= ~EARC_PHY_AI_CTRL_AI_ADDR_MASK;
	val |= reg;
	base->PHY_AI_CTRL.RW = val;

	/* Set Write AI Data */
	base->PHY_AI_WDATA = data;

    /* Set Toggle Bit PHY_AI_CTRL.TOG_1 */
	val = base->PHY_AI_CTRL.RW;
	val = ((val & mask_toggle) >> shift);
	val = (val) ? 0 : mask_toggle;
	base->PHY_AI_CTRL.RW |= val;

	/* Wait for PHY_AI_CTRL.TOG_DONE_1 to match TOG_1 */
	while(1) {
		val = base->PHY_AI_CTRL.RW;
		if((val & mask_toggle) == ((val & mask_toggle_done) >> 1))
			break;
	}

	return 0;
}
static void set_clk_rate(AUDIOMIX_Type * base2, int freq)
{
	base2->SAI_PLL_GNRL_CTL = 0x0;

	AUDIOMIX_InitAudioPll(AUDIOMIX, &g_saiPLLConfig_EarcPhy_new_clkrate); /* init SAI PLL run at 61.44 Mhz */
}

static int xcvr_en_aud_pll(EARC_Type * base, AUDIOMIX_Type * base2, int freq)
{

    CLOCK_DisableClock(kCLOCK_EarcPhy);
	set_clk_rate(base2, freq);
	CLOCK_EnableClock(kCLOCK_EarcPhy);

	/* Release AI interface from reset */
	base->PHY_AI_CTRL.RW |= EARC_PHY_AI_CTRL_AI_RESETN_MASK;

	/* PHY: CTRL_SET: TX_CLK_AUD_SS | SPDIF_EN */
	xcvr_ai_write(base, FSL_XCVR_PHY_CTRL_SET, FSL_XCVR_PHY_CTRL_TX_CLK_AUD_SS | FSL_XCVR_PHY_CTRL_SPDIF_EN, 1);

	return 0;
}

int XCVR_Prepare(app_instance_t *app)
{
	EARC_Type *base = app->earc_base;
	AUDIOMIX_Type *base2 = app->audiomix_base;
	int channels = app->channels;
	int sample_rate = app->sample_rate;
	int val;
	int fout;

	/* Calculating Audio PLL output frequency */
	fout = 32 * sample_rate * channels * 10;

	xcvr_en_aud_pll(base,base2,fout);

	/*
	 * Set TX_DATAPATH_CTRL.FRM_FMT
	 * Output 60958 frame format data will be considered to be aligned to the LSB. i.e, 60958 frame bit
	 * 0 is at bit position 0 of the TX data FIFO
	 */
	base->TX_DATAPATH_CTRL.RW |= EARC_TX_DATAPATH_CTRL_FRM_FMT_MASK;

	/*
	 * set SPDIF MODE - this flag is used to gate
	 * SPDIF output, useless for SPDIF RX
	 */
	val = base->EXT_CTRL.RW;
	val &= ~EARC_EXT_CTRL_SPDIF_MODE_MASK;
	val |= EARC_EXT_CTRL_SPDIF_MODE_MASK;
	base->EXT_CTRL.RW = val;

	return 0;
}

int XCVR_Startup(EARC_Type * base)
{
	int ret = 0;
	// TODO if required , kind of constraint checking
	return ret;
}

int XCVR_Trigger(EARC_Type * base, int cmd, xcvr_handle_t *xcvrHandle, xcvr_callback_t xcvr_callback)
{
	int val;

	/* application callback preserved, which will be used in handling IRQ and SDMA interrupts */
	xcvr_private_handle.xcvr_callback = xcvr_callback;

	switch(cmd){
		case start:
		case resume:
		case pause_release:

			/* set DPATH RESET */
			val = base->EXT_CTRL.RW;
			val &= ~EARC_EXT_CTRL_TX_DPATH_RESET_MASK;
			val |= EARC_EXT_CTRL_TX_DPATH_RESET_MASK;
			base->EXT_CTRL.RW = val;

			/* Set TX_DATAPATH_CTRL.STRT_DATA_TX : As soon as TX_FIFO has data, enable DMAC TX datapath */
			val = base->TX_DATAPATH_CTRL.RW;
			val &= ~EARC_TX_DATAPATH_CTRL_STRT_DATA_TX_MASK;
			val |= EARC_TX_DATAPATH_CTRL_STRT_DATA_TX_MASK;
			base->TX_DATAPATH_CTRL.RW = val;

			/* Enabling DMA */
			XCVR_TxEnableDMA(base, xcvrHandle->dma_enable);

			/* Enabling all required interrupts */
			val = base->EXT_IER0.RW;
			val |= (XCVR_NewCSRecInterruptEnable | XCVR_NewUDReceivedInterruptEnable | XCVR_MuteDetectedInterruptEnable |
				XCVR_FIFOOverFlowUnderFlowInterruptEnable | XCVR_HostWakeupCECMatchInterruptEnable | XCVR_CMDCStatusRegUpdateInterruptEnable |
				XCVR_B_SubframePreambleMismatch | XCVR_M_W_SubframePreambleMismatch | XCVR_PreambleMismatchInterruptEnable |
				XCVR_UnexpectedPreambltInterruptEnable | XCVR_ARCModeSetupInterruptEnable | XCVR_RqWriteDataFromFifo);
			base->EXT_IER0.RW = val;

			/* Clean datapath reset */
			val = base->EXT_CTRL.RW;
			val &= ~EARC_EXT_CTRL_TX_DPATH_RESET_MASK;
			base->EXT_CTRL.RW = val;
			EnableIRQ(AUDIO_XCVR0_IRQn);
			break;

		case pause:
		case stop:
		case suspend:
			/* disable DMA RD/WR */
				XCVR_TxEnableDMA(base, xcvrHandle->dma_enable);

			/* Disabling all required interrupts */
			val = base->EXT_IER0.RW;
			val &= ~(XCVR_NewCSRecInterruptEnable | XCVR_NewUDReceivedInterruptEnable | XCVR_MuteDetectedInterruptEnable |
				XCVR_FIFOOverFlowUnderFlowInterruptEnable | XCVR_HostWakeupCECMatchInterruptEnable | XCVR_CMDCStatusRegUpdateInterruptEnable |
				XCVR_B_SubframePreambleMismatch | XCVR_M_W_SubframePreambleMismatch | XCVR_PreambleMismatchInterruptEnable |
				XCVR_UnexpectedPreambltInterruptEnable | XCVR_ARCModeSetupInterruptEnable | XCVR_RqWriteDataFromFifo);
			base->EXT_IER0.RW = val;

			/* Stop data transmission, make start bit 0 */
			val = base->TX_DATAPATH_CTRL.RW;
			val &= ~EARC_TX_DATAPATH_CTRL_STRT_DATA_TX_MASK;
			base->TX_DATAPATH_CTRL.RW = val;
			break;

	}

	return 0;
}

/*!
 * @brief Enables the Audio XCVR interrupt requests.
 *
 * @param base Audio XCVR base pointer
 * @param mask interrupt source mask
 *     The parameter can be a combination of the interrupt flags defined by xcvr_interrupt_t.
 */
void XCVR_Enable_Interrupt(EARC_Type * base, uint32_t mask)
{
    base->EXT_IER0.SET = mask;
}
/*!
 * @brief Enables/disables the XCVR Tx DMA requests.
 * @param base XCVR base pointer
 * @param enable True means enable DMA, false means disable DMA.
 */

void XCVR_TxEnableDMA(EARC_Type *base, bool enable)
{
	int val;
    if (enable)
    {
		/* Enabling DMA */
		val = base->EXT_CTRL.RW;
		val &= ~EARC_EXT_CTRL_SDMA_WR_REQ_DIS_MASK;
		base->EXT_CTRL.RW = val;
    }
    else
    {
		val = base->EXT_CTRL.RW;
		val |= EARC_EXT_CTRL_SDMA_WR_REQ_DIS_MASK;
		base->EXT_CTRL.RW = val;
	}
}

static void XCVR_TxSDMACallback(sdma_handle_t *handle, void *userData, bool transferDone, uint32_t bdIndex)
{
	xcvr_private_handle_t *xcvr_priv_handle = (xcvr_private_handle_t *)userData;
	xcvr_sdma_handle_t *xcvrHandle = &xcvr_priv_handle->handle->xcvr_sdma_handle;

	if(!xcvr_priv_handle->handle->dma_enable)
	{
		PRINTF("DMA is not enabled, returned from callback\r\n");
		return;
	}

	/* If finished a block, call the callback function */
    (void)memset(&xcvrHandle->xcvrQueue[xcvrHandle->queueDriver], 0, sizeof(xcvr_transfer_t));
    xcvrHandle->queueDriver = (xcvrHandle->queueDriver + 1U) % XCVR_XFER_QUEUE_SIZE;
    /* Stop SDMA transfer */
    SDMA_StopChannel(handle->base, handle->channel);
    if (xcvr_priv_handle->xcvr_callback != NULL)
    {
		(xcvr_priv_handle->xcvr_callback)(xcvr_priv_handle->base, xcvr_priv_handle->handle, xcvrHandle->userData, 0);
    }
	PRINTF("xcvrHandle->xcvrQueue[%d].data = %p and dataSize = %d\r\n",xcvrHandle->queueDriver, xcvrHandle->xcvrQueue[xcvrHandle->queueDriver].data,
		xcvrHandle->xcvrQueue[xcvrHandle->queueDriver].dataSize);
    /* If all data finished, just stop the transfer */
    if (xcvrHandle->xcvrQueue[xcvrHandle->queueDriver].data == NULL)
    {
		PRINTF("XCVR_TxSDMACallback: All data is finished, stop the transfer\r\n");
        /* Disable dma */
        SDMA_AbortTransfer(handle);
        /* Disable DMA enable bit */
        XCVR_TxEnableDMA(xcvr_priv_handle->base, false);
        /* Set the handle state */
        xcvrHandle->state = (uint32_t)XCVR_Idle;
    }
}

void XCVR_TransferTxCreateHandleSDMA(EARC_Type *base,
									xcvr_handle_t *xcvr_handle,
                                    void *userData,
                                    sdma_handle_t *dmaHandle,
									uint32_t eventSource)
{
	xcvr_sdma_handle_t *handle = &xcvr_handle->xcvr_sdma_handle;
    assert((handle != NULL) && (dmaHandle != NULL));

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set xcvr base to handle */
    handle->dmaHandle     = dmaHandle;
    handle->userData      = userData;
	handle->eventSource   = eventSource;
    /* Set XCVR state to idle */
    handle->state = (uint32_t)XCVR_Idle;

    SDMA_InstallBDMemory(dmaHandle, handle->bdPool, XCVR_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    SDMA_SetCallback(dmaHandle, XCVR_TxSDMACallback, &xcvr_private_handle);
}

void XCVR_TransferTxSetConfigSDMA(EARC_Type *base, xcvr_handle_t *xcvrHandle, int bytesPerFrame, int count)
{
	xcvr_sdma_handle_t *handle = &xcvrHandle->xcvr_sdma_handle;
	handle->offset 		= 0;
	handle->queueUser   = 0;
	handle->queueDriver = 0;
	handle->count		  = count;
	handle->bytesPerFrame = bytesPerFrame;
}

status_t XCVR_TransferSendSDMA(EARC_Type *base, xcvr_handle_t *xcvrHandle, xcvr_transfer_t *xfer)
{
	xcvr_sdma_handle_t *handle = &xcvrHandle->xcvr_sdma_handle;
    assert((handle != NULL) && (xfer != NULL));
    assert((xfer->dataSize % (handle->bytesPerFrame)) == 0U);

    sdma_transfer_config_t config = {0};
    uint32_t destAddr             = AUDIO_XCVR_TX_FIFO;
    sdma_handle_t *dmaHandle      = handle->dmaHandle;
    sdma_peripheral_t perType     = kSDMA_PeripheralTypeSPDIF;

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U) || ((xfer->dataSize % (handle->bytesPerFrame)) != 0U))
    {
		PRINTF("%s, IN : SDMA: input parameter is not valid\r\n",__func__);
        return kStatus_InvalidArgument;
    }

    if (handle->xcvrQueue[handle->queueUser].data != NULL)
    {
		PRINTF("%s, IN : SDMA: xcvr data is not null\r\n",__func__);
        return kStatus_XCVR_QueueFull;
    }

    /* Change the state of handle */
    handle->transferSize[handle->queueUser]       = xfer->dataSize;
    handle->xcvrQueue[handle->queueUser].data     = xfer->data;
    handle->xcvrQueue[handle->queueUser].dataSize = xfer->dataSize;

#if defined(FSL_FEATURE_SOC_SPBA_COUNT) && (FSL_FEATURE_SOC_SPBA_COUNT > 0)
    bool isSpba = SDMA_IsPeripheralInSPBA((uint32_t)base);
    /* Judge if the instance is located in SPBA */
    if (isSpba)
    {
        perType = kSDMA_PeripheralNormal_SP;
    }
#endif /* FSL_FEATURE_SOC_SPBA_COUNT */

    /* Prepare sdma configure */
    SDMA_PrepareTransfer(&config, (uint32_t)xfer->data, destAddr, handle->bytesPerFrame, handle->bytesPerFrame,
                         handle->bytesPerFrame * handle->count, xfer->dataSize, handle->eventSource, perType,
                         kSDMA_MemoryToPeripheral);

	/* Configure the BD */
	if (handle->queueUser == XCVR_XFER_QUEUE_SIZE - 1U)
    {
        SDMA_ConfigBufferDescriptor(&dmaHandle->BDPool[handle->queueUser], (uint32_t)(xfer->data), destAddr,
                                    config.destTransferSize, xfer->dataSize, true, true, true,
                                    kSDMA_MemoryToPeripheral);
    }
    else
    {
        SDMA_ConfigBufferDescriptor(&dmaHandle->BDPool[handle->queueUser], (uint32_t)(xfer->data), destAddr,
                                    config.destTransferSize, xfer->dataSize, true, true, false,
                                    kSDMA_MemoryToPeripheral);
    }
    PRINTF("%s : Buffer Address = 0x%p for queue user %d\r\n",__func__,dmaHandle->BDPool[handle->queueUser].bufferAddr, handle->queueUser);

    handle->queueUser = (handle->queueUser + 1U) % XCVR_XFER_QUEUE_SIZE;

    if (handle->state != (uint32_t)XCVR_Busy)
    {
        SDMA_SubmitTransfer(handle->dmaHandle, &config);
        /* Start DMA transfer */
        SDMA_StartTransfer(handle->dmaHandle);
        /* Enable DMA enable bit */
		/* As per Linux XCVR, DMA is not being enabled till trigger, while from SAI Demo reference this is enabled here*/
        // XCVR_TxEnableDMA(base, true);

        /* Enable XCVR Tx clock */
        // Here if clock is synchronous with receiver, transmitter and receiver gets enabled, not sure if this should be done here

    }
	handle->offset += xfer->dataSize;
	handle->state = (uint32_t)XCVR_Busy;
    return kStatus_Success;
}

	/*!
 * brief Aborts a XCVR transfer using SDMA.
 *
 * param base XCVR base pointer.
 * param handle XCVR SDMA handle pointer.
 */
void XCVR_TransferAbortSendSDMA(EARC_Type *base, xcvr_sdma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    SDMA_AbortTransfer(handle->dmaHandle);

    /* Disable DMA enable bit */
    XCVR_TxEnableDMA(base,false);

    /* Handle the queue index */
    (void)memset(&handle->xcvrQueue[handle->queueDriver], 0, sizeof(xcvr_transfer_t));
    handle->queueDriver = (handle->queueDriver + 1U) % (uint8_t)XCVR_XFER_QUEUE_SIZE;

    /* Set the handle state */
    handle->state = (uint32_t)XCVR_Idle;
}

void AUDIO_XCVR0_IRQHandler(void)
{
    unsigned int xcvr_isr_reg = 0;
    unsigned int xcvr_isr_clr = 0;
	xcvr_isr_reg = xcvr_private_handle.base->EXT_ISR.RW;
	xcvr_irq_handle_t xcvr_irq_handle = xcvr_private_handle.handle->xcvr_irq_handle;
	bool dma_enable = xcvr_private_handle.handle->dma_enable;

    PRINTF("OM Log: %s: In (0x%x)\r\n",__func__, xcvr_isr_reg);

    if (xcvr_isr_reg & XCVR_RqWriteDataFromFifo) {
        PRINTF("%s: Data Write IRQ\r\n",__func__);
        xcvr_isr_clr |= XCVR_RqWriteDataFromFifo;
		/* If FIFO is below watermark level, handler will callback a function that refill fifo by Watermark amount of data */
		if(!dma_enable) {
			int ret = write_to_fifo(xcvr_irq_handle.src_add, xcvr_irq_handle.rem_data, xcvr_irq_handle.chunk_index);
			if(ret < 0)
				PRINTF("Data is not written to FIFO\r\n");
		}
	}

    if (xcvr_isr_reg & XCVR_FIFOOverFlowUnderFlowInterruptEnable) {
		PRINTF("%s: FIFO OverFlow/UnderFlow IRQ\r\n",__func__);
        xcvr_isr_clr |= XCVR_FIFOOverFlowUnderFlowInterruptEnable;
    }

	if(xcvr_isr_reg & XCVR_NewCSRecInterruptEnable) {
		PRINTF("%s: New CS Received IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_NewCSRecInterruptEnable;
	}

	if (xcvr_isr_reg & XCVR_NewUDReceivedInterruptEnable) {
		PRINTF("%s: New User Data Received IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_NewUDReceivedInterruptEnable;
	}

	if (xcvr_isr_reg & XCVR_MuteDetectedInterruptEnable) {
		PRINTF("%s: Mute Detected IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_MuteDetectedInterruptEnable;
	}

	if (xcvr_isr_reg & XCVR_ARCModeSetupInterruptEnable) {
		PRINTF("%s: ARC Mode Setup IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_ARCModeSetupInterruptEnable;
	}

	if(xcvr_isr_reg & XCVR_RqReadDataFromFifo) {
		PRINTF("%s: Data Read IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_RqReadDataFromFifo;
	}

	if(xcvr_isr_reg & XCVR_CMDCStatusRegUpdateInterruptEnable) {
		PRINTF("%s: CMDC Status Reg Update IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_CMDCStatusRegUpdateInterruptEnable;
	}

	if(xcvr_isr_reg & XCVR_PreambleMismatchInterruptEnable) {
		PRINTF("%s: Preamble Mismatch IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_PreambleMismatchInterruptEnable;
	}

	if(xcvr_isr_reg & XCVR_UnexpectedPreambltInterruptEnable) {
		PRINTF("%s: Unexpected Preamble IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_UnexpectedPreambltInterruptEnable;
	}

	if(xcvr_isr_reg & XCVR_B_SubframePreambleMismatch) {
		PRINTF("%s: B Subframe Preamble Mismatch IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_B_SubframePreambleMismatch;
	}

	if(xcvr_isr_reg & XCVR_M_W_SubframePreambleMismatch) {
		PRINTF("%s: M/W Subframe Preamble Mismatch IRQ\r\n",__func__);
		xcvr_isr_clr |= XCVR_M_W_SubframePreambleMismatch;
	}

	if(xcvr_isr_clr) {
	    xcvr_private_handle.base->EXT_ISR.CLR = xcvr_isr_clr;
    }
}

/* Transfer Setup on IRQ based transfer */

int XCVR_IRQ_TransferSetup(EARC_Type *base,xcvr_transfer_t *xfer) {

	xcvr_irq_handle_t *xcvr_irq_handle = &xcvr_private_handle.handle->xcvr_irq_handle;

	if((xfer->data == NULL) || (xfer->dataSize == 0)) {
		PRINTF("Insufficient Data or Data size, Transfer setup failed...\r\n");
		return 0;
	}
	xcvr_irq_handle->src_add = xfer->data;
	xcvr_irq_handle->chunk_size = xfer->dataSize;
	xcvr_irq_handle->chunk_index = 0;
	return 0;
}

/* API used to write data into Tx FIFO and return size of data copied */

int write_to_fifo(unsigned char * src_add, int rem_data, int chunk_index) {

	EARC_Type *base = xcvr_private_handle.base;
	xcvr_handle_t *handle = xcvr_private_handle.handle;
	xcvr_callback_t xcvr_callback = xcvr_private_handle.xcvr_callback;

	int write_fifo_wm = 256; // 64 integer or 256 bytes
	static int transferred_data = 0;
	int chunk_size = xcvr_private_handle.handle->xcvr_irq_handle.chunk_size;
	int priv_chunk_index = xcvr_private_handle.handle->xcvr_irq_handle.chunk_index;

	int remained_in_chunk = chunk_size - chunk_index;
	size_t size =  write_fifo_wm < remained_in_chunk ? write_fifo_wm : remained_in_chunk;
	unsigned char *tx_fifo = (unsigned char *)AUDIO_XCVR_TX_FIFO;

	/* Writing data to fifo */
	memcpy(tx_fifo, src_add, size);

	/* Increased transferred data */
	transferred_data += size; // Counter for complete 4.8MB data
	priv_chunk_index += size; // index or counting for chunk

	PRINTF("Transfer index = %d and size = %d\r\n", transferred_data,size);
	/* If chunk amount of data transferred, callback will setup new transfer */
	if (xcvr_callback != NULL && (priv_chunk_index >= chunk_size)) {
			(xcvr_callback)(base, handle, NULL,transferred_data);
	}

	return size;
}

int Set_CS_UD_Values(app_instance_t *app,int *CS_value, int *UD_value) {
	if (app->sample_rate == 48000) {
        #if defined(CS_IN_BIG_ENDIAN)
            int tmp[6] = SAMPLE_RATE_48KHz_BIG_ENDIAN;
        #else
            int tmp[6] = SAMPLE_RATE_48KHz_LITTLE_ENDIAN;
        #endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else if (app->sample_rate == 22050) {

		#if defined(CS_IN_BIG_ENDIAN)
			int tmp[6] = SAMPLE_RATE_22_05KHz_BIG_ENDIAN;
		#else
			int tmp[6] = SAMPLE_RATE_22_05KHz_LITTLE_ENDIAN;
		#endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else if (app->sample_rate == 24000) {
		#if defined(CS_IN_BIG_ENDIAN)
			int tmp[6] = SAMPLE_RATE_24KHz_BIG_ENDIAN;
		#else
			int tmp[6] = SAMPLE_RATE_24KHz_LITTLE_ENDIAN;
		#endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else if (app->sample_rate == 32000) {
		#if defined(CS_IN_BIG_ENDIAN)
			int tmp[6] = SAMPLE_RATE_32KHz_BIG_ENDIAN;
		#else
			int tmp[6] = SAMPLE_RATE_32KHz_LITTLE_ENDIAN;
		#endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else if (app->sample_rate == 44100) {
		#if defined(CS_IN_BIG_ENDIAN)
			int tmp[6] = SAMPLE_RATE_44_1KHz_BIG_ENDIAN;
		#else
			int tmp[6] = SAMPLE_RATE_44_1KHz_LITTLE_ENDIAN;
		#endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else if (app->sample_rate == 88200) {
		#if defined(CS_IN_BIG_ENDIAN)
			int tmp[6] = SAMPLE_RATE_88_2KHz_BIG_ENDIAN;
		#else
			int tmp[6] = SAMPLE_RATE_88_2KHz_LITTLE_ENDIAN;
		#endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else if (app->sample_rate == 96000) {
		#if defined(CS_IN_BIG_ENDIAN)
			int tmp[6] = SAMPLE_RATE_96KHz_BIG_ENDIAN;
		#else
			int tmp[6] = SAMPLE_RATE_96KHz_LITTLE_ENDIAN;
		#endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else if (app->sample_rate == 176400) {
		#if defined(CS_IN_BIG_ENDIAN)
			int tmp[6] = SAMPLE_RATE_176_4KHz_BIG_ENDIAN;
		#else
			int tmp[6] = SAMPLE_RATE_176_4KHz_LITTLE_ENDIAN;
		#endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else if (app->sample_rate == 192000) {
		#if defined(CS_IN_BIG_ENDIAN)
			int tmp[6] = SAMPLE_RATE_192KHz_BIG_ENDIAN;
		#else
			int tmp[6] = SAMPLE_RATE_192KHz_LITTLE_ENDIAN;
		#endif
		memcpy(CS_value, tmp, sizeof(tmp));

	} else {
		PRINTF("Unsupported Sample Rate, setting default 48KHz CS values\r\n");
	}

		/* User Data value setting */
		memcpy(UD_value, 0, 6 * sizeof(int));
		return 0;
}

/* Function that writes CS values to required register */

int XCVR_write_CS_to_Reg(EARC_Type *base, int *CS_val) {

	/* Write CS value to CS register */
	base->TX_CS_DATA_BITS[0] = CS_val[0];
	base->TX_CS_DATA_BITS[1] = CS_val[1];
	base->TX_CS_DATA_BITS[2] = CS_val[2];
	base->TX_CS_DATA_BITS[3] = CS_val[3];
	base->TX_CS_DATA_BITS[4] = CS_val[4];
	base->TX_CS_DATA_BITS[5] = CS_val[5];

	return 0;
}

/* Function that writes UD values to required register */
int XCVR_write_UD_to_Reg(EARC_Type *base, int *UD_value) {

	/* Write UD value to UD register */
	base->TX_USER_DATA_BITS[0] = UD_value[0];
	base->TX_USER_DATA_BITS[1] = UD_value[1];
	base->TX_USER_DATA_BITS[2] = UD_value[2];
	base->TX_USER_DATA_BITS[3] = UD_value[3];
	base->TX_USER_DATA_BITS[4] = UD_value[4];
	base->TX_USER_DATA_BITS[5] = UD_value[5];

	return 0;
}
int XCVR_AdvanceConfiguration(EARC_Type *base) {

	int temp = base->TX_DATAPATH_CTRL.RW;
	bool xcvr_fill_iec60958_frame = xcvr_private_handle.handle->xcvr_fill_iec60958_frame;
	/* CS Mode - Enable Channel Status Insertion from CS Register
	 * UD Mode - Enable User Data Insertion from UD Register
	 * Valid Bit - Enable Valid Bit Insertion
	 * Parity Bit - Enable Parity Bit Insertion
	 * Preamble - Enable Preamble Insertion
	 */
	if(xcvr_fill_iec60958_frame) {
		temp = EARC_TX_DATAPATH_CTRL_CS_MOD_MASK | EARC_TX_DATAPATH_CTRL_UD_MOD_MASK | EARC_TX_DATAPATH_CTRL_VLD_MOD_MASK |
				EARC_TX_DATAPATH_CTRL_EN_PARITY_MASK | EARC_TX_DATAPATH_CTRL_EN_PREAMBLE_MASK | EARC_TX_DATAPATH_CTRL_FRM_VLD_MASK;

		base->TX_DATAPATH_CTRL.RW = temp;
	}
	return 0;
}
