#ifndef FSL_XCVR_H_
#define FSL_XCVR_H_
#include "fsl_common.h"
#include "fsl_sdma.h"
#include "fsl_iomuxc.h"
#include "pin_mux.h"
#include "app.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define FSL_XCVR_REG_OFFSET                 0x800 /* regs offset */
#define FSL_XCVR_PHY_CTRL                   0x00
#define FSL_XCVR_PHY_CTRL_SET               0x04
#define FSL_XCVR_PHY_CTRL_CLR               0x08
#define FSL_XCVR_PHY_CTRL_TX_CLK_AUD_SS     1<<26
#define FSL_XCVR_PHY_CTRL_SPDIF_EN          1<<8
#define start 1
#define resume 6
#define pause_release 4
#define stop 0
#define suspend 3
#define pause 5
#define SAMPLE_RATE_48KHz_BIG_ENDIAN            {0x20410040, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_48KHz_LITTLE_ENDIAN         {0x02008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_22_05KHz_BIG_ENDIAN         {0x20410020, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_22_05KHz_LITTLE_ENDIAN      {0x04008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_24KHz_BIG_ENDIAN            {0x20410060, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_24KHz_LITTLE_ENDIAN         {0x06008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_32KHz_BIG_ENDIAN            {0x204100c0, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_32KHz_LITTLE_ENDIAN         {0x03008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_44_1KHz_BIG_ENDIAN          {0x20410000, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_44_1KHz_LITTLE_ENDIAN       {0x00008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_88_2KHz_BIG_ENDIAN          {0x20410010, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_88_2KHz_LITTLE_ENDIAN       {0x08008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_96KHz_BIG_ENDIAN            {0x20410050, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_96KHz_LITTLE_ENDIAN         {0x0a008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_176_4KHz_BIG_ENDIAN         {0x20410030, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_176_4KHz_LITTLE_ENDIAN      {0x0c008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_192KHz_BIG_ENDIAN           {0x20410070, 0x40000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define SAMPLE_RATE_192KHz_LITTLE_ENDIAN        {0x0e008204, 0x00000002, 0x00000000, 0x00000000, 0x00000000, 0x00000000}
#define USER_DATA_DEFAULT_VALUE                 {0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000}

/*! @brief _xcvr_interrupt_t, The Audio XCVR interrupt */
typedef enum
{
    XCVR_NewCSRecInterruptEnable  = EARC_EXT_IER0_NEW_CS_IE_0_MASK, /*! NEW_CS_IE_0 - Enable for New channel status block received interrupt */
    XCVR_NewUDReceivedInterruptEnable = EARC_EXT_IER0_NEW_UD_IE_0_MASK, /*! NEW_UD_IE_0 - Enable for new user data received interrupt */
    XCVR_MuteDetectedInterruptEnable   = EARC_EXT_IER0_MUTE_IE_0_MASK, /*! MUTE_IE_0 - Enable for Mute detected interrupt */
    XCVR_CMDCDataResponseTimeOutInterruptEnable  = EARC_EXT_IER0_CMDC_RESP_TO_IE_0_MASK, /*! CMDC_RESP_TO_IE_0 - Receiver CMDC data response timeout interrupt enable */
    XCVR_IECDataUncorrectableErrorInterruptEnable = EARC_EXT_IER0_ECC_ERR_IE_0_MASK, /*! ECC_ERR_IE_0 - 60958 Compressed data uncorrectable error interrupt enable */ 
    XCVR_PreambleMismatchInterruptEnable   = EARC_EXT_IER0_PREAMBLE_MISMATCH_IE_0_MASK, /*! PREAMBLE_MISMATCH_IE_0 - Preamble mismatch interrupt enable. */
    XCVR_FIFOOverFlowUnderFlowInterruptEnable  = EARC_EXT_IER0_FIFO_OFLOW_UFLOW_ERR_IE_0_MASK, /*! FIFO_OFLOW_UFLOW_ERR_IE_0 - FIFO overflow (in Rx mode) / FIFO underflow (in Tx mode) error interrupt enable. */
    XCVR_HostWakeupCECMatchInterruptEnable = EARC_EXT_IER0_HOST_WAKEUP_IE_0_MASK,/*! HOST_WAKEUP_IE_0 - Host wakeup on CEC match interrupt enable. */
    XCVR_OutputHPDInterruptEnable   = EARC_EXT_IER0_OHPD_IE_0_MASK, /*! OHPD_IE_0 - Output HPD interrupt enable. */
    XCVR_NoDMACDataReceivedInterruptEnable  = EARC_EXT_IER0_DMAC_NO_DATA_REC_IE_0_MASK, /*! DMAC_NO_DATA_REC_IE_0 - Indicates no DMAC data is received. */
    XCVR_DMACDataChangedInterruptEnable = EARC_EXT_IER0_DMAC_FMT_CHG_DET_IE_0_MASK, /*! DMAC_FMT_CHG_DET_IE_0 - Indicates DMAC format change was detected */
    XCVR_HeartbeatStatusChangeInterruptEnable   = EARC_EXT_IER0_HB_STATE_CHG_IE_0_MASK, /*! HB_STATE_CHG_IE_0 - Interrupt enable for Heartbeat status change */
    XCVR_CMDCStatusRegUpdateInterruptEnable  = EARC_EXT_IER0_CMDC_STATUS_UPDATE_IE_0_MASK, /*! CMDC_STATUS_UPDATE_IE_0 - Interrupt enable for CMDC status register update. */
    XCVR_ChipTempUpdateRequest = EARC_EXT_IER0_TEMP_UPDATE_IE_0_MASK, /*! TEMP_UPDATE_IE_0 - Update request for chip temperature value. */
    XCVR_RqReadDataFromFifo   = EARC_EXT_IER0_DMA_RD_REQ_IE_0_MASK, /*! DMA_RD_REQ_IE_0 - Request to read data from FIFO. */
    XCVR_RqWriteDataFromFifo  = EARC_EXT_IER0_DMA_WR_REQ_IE_0_MASK, /*! DMA_WR_REQ_IE_0 - Request to write data to FIFO. */
    XCVR_BiphaseEncodingErrorInterrupt = EARC_EXT_IER0_DMAC_RX_BME_ERR_IE_0_MASK, /*! DMAC_RX_BME_ERR_IE_0 - Bi-phase mark encoding error */
    XCVR_PreambleMatchInterrupt   = EARC_EXT_IER0_PREAMBLE_MATCH_IE_0_MASK, /*! PREAMBLE_MATCH_IE_0 - Interrupt enable for preamble match received. */
    XCVR_M_W_SubframePreambleMismatch  = EARC_EXT_IER0_M_W_PRE_MISMATCH_IE_0_MASK, /*! M_W_PRE_MISMATCH_IE_0 - Interrupt enable for sub-frame M/W preamble mismatch received. */
    XCVR_B_SubframePreambleMismatch = EARC_EXT_IER0_B_PRE_MISMATCH_IE_0_MASK, /*! B_PRE_MISMATCH_IE_0 - Interrupt enable for sub-frame B preamble mismatch received. */
    XCVR_UnexpectedPreambltInterruptEnable   = EARC_EXT_IER0_UNEXP_PRE_REC_IE_0_MASK, /*! UNEXP_PRE_REC_IE_0 - Interrupt enable for Unexpected preamble received. */
    XCVR_ARCModeSetupInterruptEnable  = EARC_EXT_IER0_ARC_MODE_IE_0_MASK, /*! ARC_MODE_IE_0 - Interrupt to indicate ARC mode setup. */
    XCVR_CS_UD_NotSavedInterruptEnable = EARC_EXT_IER0_CH_UD_OFLOW_IE_0_MASK, /*! CH_UD_OFLOW_IE_0 - Channel status or used data could not be stored. */
    XCVR_SpareInterruptEnable   = EARC_EXT_IER0_SPARE_IE_0_MASK, /*! SPARE_IE_0 - Spare interrupts */
    XCVR_AllInterruptEnable = ( EARC_EXT_IER0_NEW_CS_IE_0_MASK | EARC_EXT_IER0_NEW_UD_IE_0_MASK | EARC_EXT_IER0_MUTE_IE_0_MASK | EARC_EXT_IER0_CMDC_RESP_TO_IE_0_MASK | 
        EARC_EXT_IER0_ECC_ERR_IE_0_MASK | EARC_EXT_IER0_PREAMBLE_MISMATCH_IE_0_MASK | EARC_EXT_IER0_FIFO_OFLOW_UFLOW_ERR_IE_0_MASK | EARC_EXT_IER0_HOST_WAKEUP_IE_0_MASK | 
        EARC_EXT_IER0_OHPD_IE_0_MASK | EARC_EXT_IER0_DMAC_NO_DATA_REC_IE_0_MASK | EARC_EXT_IER0_DMAC_FMT_CHG_DET_IE_0_MASK | EARC_EXT_IER0_HB_STATE_CHG_IE_0_MASK | EARC_EXT_IER0_CMDC_STATUS_UPDATE_IE_0_MASK |
        EARC_EXT_IER0_TEMP_UPDATE_IE_0_MASK | EARC_EXT_IER0_DMA_RD_REQ_IE_0_MASK | EARC_EXT_IER0_DMA_WR_REQ_IE_0_MASK | EARC_EXT_IER0_DMAC_RX_BME_ERR_IE_0_MASK | EARC_EXT_IER0_PREAMBLE_MATCH_IE_0_MASK |
        EARC_EXT_IER0_M_W_PRE_MISMATCH_IE_0_MASK | EARC_EXT_IER0_B_PRE_MISMATCH_IE_0_MASK | EARC_EXT_IER0_UNEXP_PRE_REC_IE_0_MASK | EARC_EXT_IER0_ARC_MODE_IE_0_MASK |
        EARC_EXT_IER0_CH_UD_OFLOW_IE_0_MASK | EARC_EXT_IER0_SPARE_IE_0_MASK )
} xcvr_interrupt_t;

/*! @brief _xcvr_status_t, XCVR return status.*/
enum
{
    kStatus_XCVR_TxBusy    = MAKE_STATUS(kStatusGroup_SPDIF, 0), /*!< XCVR Tx is busy. */
    kStatus_XCVR_RxBusy    = MAKE_STATUS(kStatusGroup_SPDIF, 1), /*!< XCVR Rx is busy. */
    kStatus_XCVR_TxError   = MAKE_STATUS(kStatusGroup_SPDIF, 2), /*!< XCVR Tx FIFO error. */
    kStatus_XCVR_RxError   = MAKE_STATUS(kStatusGroup_SPDIF, 3), /*!< XCVR Rx FIFO error. */
    kStatus_XCVR_QueueFull = MAKE_STATUS(kStatusGroup_SPDIF, 4), /*!< XCVR transfer queue is full. */
    kStatus_XCVR_TxIdle    = MAKE_STATUS(kStatusGroup_SPDIF, 5), /*!< XCVR Tx is idle */
    kStatus_XCVR_RxIdle    = MAKE_STATUS(kStatusGroup_SPDIF, 6)  /*!< XCVR Rx is idle */
};

/*!
 * @brief XCVR State.
 */
 enum
{
    XCVR_Busy = 0x0U, /*!< XCVR is busy */
    XCVR_Idle,        /*!< Transfer is done. */
};

/*! @brief XCVR transfer structure */
typedef struct _xcvr_transfer
{
    uint8_t *data;   /*!< Data start address to transfer. */
    size_t dataSize; /*!< Transfer size. */
} xcvr_transfer_t;

/*! @brief xcvr sdma handle typedef */
typedef struct xcvr_sdma_handle xcvr_sdma_handle_t;

/*! @brief XCVR IRQ handle typedef */
typedef struct xcvr_irq_handle xcvr_irq_handle_t;

/*! @brief XCVR handle typedef */
typedef struct xcvr_handle xcvr_handle_t;

/*! @brief XCVR callback definition */
typedef void (*xcvr_callback_t)(EARC_Type *base, xcvr_handle_t *xcvr_handle, void *userData, int transferred_data);

/*! @brief XCVR DMA transfer handle, users should not touch the content of the handle. */
struct xcvr_sdma_handle
{
    sdma_handle_t *dmaHandle;     /*!< DMA handler for XCVR send */
    uint8_t bytesPerFrame;        /*!< Bytes in a frame */
    uint32_t count;               /*!< The transfer data count in a DMA request */
    uint32_t state;               /*!< Internal state for XCVR SDMA transfer */
    uint32_t eventSource;         /*!< XCVR event source number */
    void *userData;               /*!< User callback parameter */
    sdma_buffer_descriptor_t bdPool[XCVR_XFER_QUEUE_SIZE]; /*!< BD pool for SDMA transfer. */
    xcvr_transfer_t xcvrQueue[XCVR_XFER_QUEUE_SIZE];         /*!< Transfer queue storing queued transfer. */
    size_t transferSize[XCVR_XFER_QUEUE_SIZE];             /*!< Data bytes need to transfer */
    volatile uint8_t queueUser;                           /*!< Index for user to queue transfer. */
    volatile uint8_t queueDriver;                         /*!< Index for driver to get the transfer data and size */
    size_t offset;
};

typedef struct xcvr_irq_handle
{
    unsigned char *src_add;
    int dest_add;
    int chunk_size;
    int rem_data;
    int chunk_index;
} xcvr_irq_handle_t;

typedef struct xcvr_handle
{
    bool dma_enable;
    bool xcvr_fill_iec60958_frame;
    xcvr_callback_t callback; /*!< Callback for users while transfer finish or error occurs */

    /* Based on transfer method, only one of DMA and IRQ handle is used to save memory */
    union {
        xcvr_sdma_handle_t xcvr_sdma_handle; /* DMA-based transfer handle */
        xcvr_irq_handle_t xcvr_irq_handle;  /* IRQ-based transfer handle */
    };
} xcvr_handle_t;

/*******************************************************************************
 * APIs
 ******************************************************************************/

/*!
 * @name Initialization and Configuration
 * @{
 */

/*!
 * @brief Initializes the XCVR peripheral.
 * This API gates the XCVR clock. The XCVR module can't operate unless XCVR_Init is called to enable the clock.
 *
 * @param app Pointer to the application instance structure.
 * @param handle Pointer to xcvr_handle_t structure.
 */
void XCVR_Init(app_instance_t *app, xcvr_handle_t *handle);

/*!
 * @brief Load firmware to XCVR.
 * This function loads the XCVR firmware to the XCVR internal memory.
 *
 * @param xcvr_imx8mp_bin Pointer to the XCVR firmware image.
 * @param len Length of the XCVR firmware image.
 */

void XCVR_load_firmware(unsigned char* xcvr_imx8mp_bin, unsigned int len);

/*!
 * @brief Prepare XCVR for operation.
 * This function prepares the XCVR for operation after the firmware is loaded.
 *
 * @param app Pointer to the application instance structure.
 * @return 0 if success or -1 if error.
 */

int XCVR_Prepare(app_instance_t *app);

/*!
 * @brief Start XCVR Operation.
 * This function starts the XCVR operation after it is prepared.
 *
 * @param base XCVR base pointer.
 * @return 0 if success or -1 if error.
 */

int XCVR_Startup(EARC_Type * base);

/*!
 * @brief Trigger XCVR operations

 * @param base XCVR base pointer.
 * @param cmd Trigger command, start/resume/pause_release/stop/suspend/pause
 * @param handle Pointer to xcvr_handle_t structure.
 * @param xcvr_callback XCVR callback function for handling irqs with required arguements for further operations
 * @return 0 if success or -1 if error.
 */

int XCVR_Trigger(EARC_Type * base, int cmd, xcvr_handle_t *handle, xcvr_callback_t xcvr_callback);

/*! @} */

/*!
 * @name Interrupts
 * @{
 */

 /*!
 * @brief Enable XCVR interrupts.
 * This function enables the XCVR interrupts.
 *
 * @param base XCVR base pointer.
 * @param mask The interrupts to enable. This is a logical OR of members of the enumeration ::xcvr_interrupt_t
 */

void XCVR_Enable_Interrupt(EARC_Type * base, uint32_t mask);

/*!
 * @name Transactional
 * @ {
 */

 /*!
 * @brief Create XCVR handle for sending data using SDMA
 * This function initializes the XCVR SDMA handle which can be used for other XCVR SDMA transactional APIs. Usually, for a specified XCVR instance,
 * call this API once to get the initialized handle.
 *
 * @param base XCVR base pointer.
 * @param handle Pointer to xcvr_sdma_handle_t structure.
 * @param callback XCVR SDMA callback function.
 * @param userData User data for XCVR SDMA callback.
 * @param dmaHandle Pointer to SDMA handle, this handle shall be initialized before calling this API.
 * @param eventSource SDMA event source number for XCVR, please refer to the reference manual to get the event source number.
 * @return kStatus_Success if success or kStatus_InvalidArgument if error.
 */

void XCVR_TransferTxCreateHandleSDMA(EARC_Type *base,
                                    xcvr_handle_t *xcvr_handle,
                                    void *userData,
                                    sdma_handle_t *dmaHandle,
									uint32_t eventSource);

/*!
 * @brief Transfer data using SDMA
 * This function sends data using SDMA. When all data is sent, the callback function is called.
 *
 * @param base XCVR base pointer.
 * @param handle Pointer to xcvr_handle_t structure.
 * @param xfer Pointer to xcvr_transfer_t structure.
 * @return kStatus_Success if success, kStatus_XCVR_TxBusy if a previous send is not finished, or kStatus_InvalidArgument if error.
 */

status_t XCVR_TransferSendSDMA(EARC_Type *base, xcvr_handle_t *handle, xcvr_transfer_t *xfer);

/*!
 * @brief Set the XCVR SDMA transfer configuration
 * This function sets the XCVR SDMA transfer configuration.
 *
 * @param base XCVR base pointer.
 * @param handle Pointer to xcvr_handle_t structure.
 * @param bytesPerFrame Bytes in a frame, usually 4 bytes for sending iec60958 frame.
 * @param wmarklevel FIFO watermark level, when the FIFO data count is below this value, a DMA request is generated.
 */

void XCVR_TransferTxSetConfigSDMA(EARC_Type *base, xcvr_handle_t *handle, int bytesPerFrame, int count);

/*!
 * @brief Abort a XCVR SDMA send
 * This function aborts a XCVR SDMA send. DMA will be disabled and other configurations will be reset.
 *
 * @param base XCVR base pointer.
 * @param handle Pointer to xcvr_sdma_handle_t structure.
 */
void XCVR_TransferAbortSendSDMA(EARC_Type *base, xcvr_sdma_handle_t *handle);


/*!
 * @name DMA Control
 * @{
 */

/*!
 * @brief Enable or disable XCVR Tx DMA
 * This function enables or disables the XCVR Tx DMA.
 *
 * @param base XCVR base pointer.
 * @param enable True to enable, false to disable.
 */

void XCVR_TxEnableDMA(EARC_Type *base, bool enable);


/*! @name IRQ Control
 * @{
 */

/*!
 * @brief Setup XCVR IRQ transfer
 * This function sets up the XCVR IRQ transfer.
 *
 * @param base XCVR base pointer.
 * @param xfer Pointer to xcvr_transfer_t structure.
 * @return 0 if success or -1 if error.
 */

int XCVR_IRQ_TransferSetup(EARC_Type *base, xcvr_transfer_t *xfer);

/*!
 * @name Bus Operations
 * @{
 */

/*!
 * @brief Write data to XCVR FIFO
 * This function writes data to XCVR FIFO in IRQ handler.
 *
 * @param src_data Pointer to source data.
 * @param rem_data Remaining data to be sent.
 * @param chunk_index Chunk index for current transfer.
 * @return Number of bytes written to FIFO.
 */

int write_to_fifo(unsigned char * src_data, int rem_data, int chunk_index);

/*!
 * @brief Function that sets CS and UD values based on sample rate
 * This function sets CS and UD values based on sample rate in app_instance_t structure
 *
 * @param app Pointer to the application instance structure.
 * @return 0 if success or -1 if error.
 */
int Set_CS_UD_Values(app_instance_t *app,int CS_value[], int UD_value[]);

/*!
 * @brief Function that writes CS values to required register
 * This function writes CS values to required register from the buffer passed as argument
 *
 * @param base XCVR base pointer.
 * @param CS_value Pointer to the buffer containing CS values.
 * @return 0 if success or -1 if error.
 */

int XCVR_write_CS_to_Reg(EARC_Type *base, int *CS_value);

/*!
 * @brief Function that writes UD values to required register
 * This function writes UD values to required register from the buffer passed as argument
 *
 * @param base XCVR base pointer.
 * @param UD_value Pointer to the buffer containing UD values.
 * @return 0 if success or -1 if error.
 */

int XCVR_write_UD_to_Reg(EARC_Type *base, int *UD_value);

/*!
 * @brief Function that does the advanced configuration
 * This function does the advanced configuration like filling CS/UD into frames
 *
 * @param base XCVR base pointer.
 * @return 0 if success or -1 if error.
 */

int XCVR_AdvanceConfiguration(EARC_Type *base);

#endif /* FSL_XCVR_H_ */

