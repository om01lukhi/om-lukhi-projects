#include "app.h"
#include "board.h"
#include "fsl_debug_console.h"
#include "fsl_xcvr.h"
#include "stdio.h"
#include <PERI_EARC.h>

AT_NONCACHEABLE_SECTION_ALIGN(sdma_context_data_t sdmaContext, 4);
AT_NONCACHEABLE_SECTION_ALIGN(sdma_handle_t sdmaHandle, 4);
AT_NONCACHEABLE_SECTION_ALIGN(xcvr_handle_t xcvrHandle, 4);
app_instance_t g_app;

/* source initializing function */
int app_source_init(app_instance_t *app)
{
    /*1. First byte will be used for configuring :
         i. Transfer Method : DMA/IRQ
         ii. IEC60958 Frame Filling : Enabled/Disabled
         iii. Sample Rate : 48K/44.1K
         iv. Bits per sample : 16/24/32

       2. Next 4 bytes will be used for storing length of audio source data

       3. Next 4 bytes will be used for pre-audio data check value (0xFFFFFFFF)

       4. Audio source data will be placed after above 9 bytes

       5. Last 4 bytes will be used for post-audio data check value (0xEEEEEEEE)
    */

    /* For Tansfer Method:
        Bit [31] : 0 - Use IRQ method
                   1 - Use DMA method
        For IEC60958 Frame Filling:
        Bit [30] : 0 - Disabled
                   1 - Enabled
        For Bits per sample:
        Bit [29-27] : 000 - 32 bits
                      001 - 16 bits
                      010 - 24 bits
                      011 - 8 bits
                      100 - 20 bits

        For Sample Rate:
        Bit [26-23] : 0000 - 48K
                      0001 - 22.05K
                      0010 - 24K
                      0011 - 32K
                      0100 - 44.1K
                      0101 - 88.2K
                      0110 - 96K
                      0111 - 176.4K
                      1000 - 192K

        Bit [22-0] : Reserved

    */

    int user_info = Frames_Raw_PCM_DDR_ADDR;
    int temp = *(int *)user_info; /* First 4 bytes contain user configuration info */
    int dma_enable,xcvr_fill_frame,sample_rate, bps;


    dma_enable = temp>>31 & 0x1; /* First bit for DMA/IRQ transfer method */
    app->dma_enable = dma_enable == 1 ? true : false;

    xcvr_fill_frame = temp >> 30 & 0x1; /* Second bit for IEC60958 Frame Filling */
    app->xcvr_fill_frame = xcvr_fill_frame == 1 ? true : false;

    /* If IEC60958 frame format is enabled, extract sample rate and bits per sample */

    if(app->xcvr_fill_frame) {

        bps = temp >> 27 & 0x7; /* Third bit for Sample Rate */
        switch(bps) {
            case 0:
                app->bps = 32;
                break;
            case 1:
                app->bps = 16;
                break;
            case 2:
                app->bps = 24;
                break;
            case 3:
                app->bps = 8;
                break;
            case 4:
                app->bps = 20;
                break;
            default:
                app->bps = 32;
                break;
        }

        sample_rate = temp >> 23 & 0xff; /* Fourth bit for Bits per sample */

        switch(sample_rate) {
            case 0:
                app->sample_rate = 48000;
                break;
            case 1:
                app->sample_rate = 22050;
                break;
            case 2:
                app->sample_rate = 24000;
                break;
            case 3:
                app->sample_rate = 32000;
                break;
            case 4:
                app->sample_rate = 44100;
                break;
            case 5:
                app->sample_rate = 88200;
                break;
            case 6:
                app->sample_rate = 96000;
                break;
            case 7:
                app->sample_rate = 176400;
                break;
            case 8:
                app->sample_rate = 192000;
                break;
            default:
                app->sample_rate = 48000;
                break;
        }

    }

    app->audio_src_len = *(int *)(user_info + 4); /* Next 4 bytes contain length of audio data */
    int preAudioCheck = *(int *)(user_info + 8); /* Next 4 bytes contain preamble info */
    app->audio_src = (unsigned char *)(user_info + 12); /* After 12 bytes audio data starts */
    int postAudioCheck = *(int *)(user_info + app->audio_src_len + 12); /* Last 4 bytes contain end preamble info */

    PRINTF("Audio Source Initialization Info: DMA Enable = %d, IEC60958 Frame Fill = %d, Sample Rate = %d, Bits per sample = %d, Audio Source Length = %d\r\n",
           app->dma_enable, app->xcvr_fill_frame, app->sample_rate, app->bps, app->audio_src_len);

    if (!app->audio_src_len)
    {
        PRINTF("ERROR: Audio source length is zero\r\n");
        return -1;
    }

    /* User can add more checks here to validate audio source data */
    if ((preAudioCheck != 0xffffffff) || (postAudioCheck!= 0xeeeeeeee))
    {
        PRINTF("ERROR: AudioChecks Failed, Audio source data may be corrupted\r\n");
        return -1;
    }

    return 0;
}

/* Initialize application instance.*/
void app_init(app_instance_t *app)
{
    /* Reset all structure members to zero */
    memset(app, 0, sizeof(app_instance_t));

    /* Initialize application instance structure */
    app->earc_base = AUDIO_XCVR;
    app->audiomix_base = AUDIOMIX;

    /* Default transfer configuration */

    app->dma_enable = true;
    app->xcvr_fill_frame = false;

    /* Default audio configuration */
    app->sample_rate = 48000;
    app->bps = 32; /* Bits per sample */
    app->channels = 2; /* Channel configuration */

    /* Audio source configuration */
    app->audio_src = NULL;
    app->audio_src_len = 0;

    /* Transfer status */
    app->TransferDone = false;
}

/* Function to print XCVR configuration registers for debugging */
void print_xcvr_config_register(EARC_Type *earc_base) {
    int ext_ctrl = (int)earc_base->EXT_CTRL.RW;
    int ext_ier0 = (int)earc_base->EXT_IER0.RW;
    int tx_dpath_ctrl = (int)earc_base->TX_DATAPATH_CTRL.RW;
    PRINTF("XCVR EXT_CTRL = 0x%x, EXT_IER0 = 0x%x, Tx_DATAPATH_CTRL = 0x%x\r\n",ext_ctrl, ext_ier0, tx_dpath_ctrl);
}

/* Function to print XCVR runtime status registers for debugging */
void print_xcvr_runtime_register(EARC_Type *earc_base) {
    int ext_status = earc_base->EXT_STATUS.RW;
    int dpath_status = earc_base->DPATH_STATUS;
    int isr = earc_base->EXT_ISR.RW;
    PRINTF("XCVR EXT_STAT = 0x%x, XCVR EXT_ISR = 0x%x, XCVR DATAPATH STATUS = 0x%x\r\n",ext_status, isr, dpath_status);
}

/* Callback function for Both SDMA and IRQ based transfer */
static void app_callback(EARC_Type *earc_base, xcvr_handle_t *handle, void *userData, int transferred_data) {

    PRINTF("%s: Entered callback function\r\n",__func__);
    uint8_t *temp;

    /* Check if DMA based transfer is enabled */
    if(handle->dma_enable) {
        xcvr_sdma_handle_t *sdma_handle = &handle->xcvr_sdma_handle;
        int remaining = (g_app.audio_src_len - sdma_handle->offset);

        if(remaining > 0) {
            xcvr_transfer_t xfer;
                temp = (unsigned char *)g_app.audio_src;
                xfer.data     = temp + sdma_handle->offset;
                xfer.dataSize = remaining > CHUNK_SIZE ? CHUNK_SIZE : remaining;

            PRINTF("%s, Updated BD[%d]: src=0x%08X, size=%d, remaining=%d\r\n",__func__, sdma_handle->queueUser, xfer.data, xfer.dataSize, remaining);
            XCVR_TransferSendSDMA(earc_base, handle, &xfer);

            /* Printed register values for debugging */
            print_xcvr_runtime_register(earc_base);
        } else {
            PRINTF("%s: Transfer is finished and TransferDone = True\r\n",__func__);
            g_app.TransferDone = true;
        }

    } else {
        int offset = transferred_data;
        int remaining = (g_app.audio_src_len - offset);
        if(remaining >= 0 ) { /* Data should be written manually, only when sdma is not configured, or it is irq based data transfer */
            xcvr_transfer_t xfer;

            temp = (unsigned char *)g_app.audio_src;

            xfer.data       = temp + offset;
            xfer.dataSize   = remaining > CHUNK_SIZE ? CHUNK_SIZE : remaining;
            XCVR_IRQ_TransferSetup(earc_base, &xfer);
        } else {
            g_app.TransferDone = true;
            PRINTF("%s: All data is transferred successfully\r\n",__func__);
        }
    }
}

/* SDMA configuration for data transfer */
void app_dma_config(app_instance_t *app)
{
    uint8_t *temp;
    xcvr_transfer_t xfer;
    sdma_config_t sdmaConfig = {0};

    /*Default configuration of SDMA*/
    SDMA_GetDefaultConfig(&sdmaConfig);
    #if defined DEMO_SDMA_CLOCK_RATIO
    sdmaConfig.ratio = kSDMA_ARMClockFreq; /* SDMA core clock frequency equals to ARM platform */
    #endif
    /*Initialize SDMA Module*/
    SDMA_Init(DEMO_SDMA, &sdmaConfig);
    PRINTF("Audio XCVR : SDMA_Init executed successfully\r\n");

    /*Create SDMA Handle*/
    SDMA_CreateHandle(&sdmaHandle, DEMO_SDMA, DEMO_CHANNEL, &sdmaContext);
    PRINTF("Audio XCVR : SDMA_CreateHandle executed successfully\r\n");

    /*Set the SDMA channel priority*/
    SDMA_SetChannelPriority(DEMO_SDMA, DEMO_CHANNEL, 2);
    PRINTF("Audio XCVR : SDMA_SetChannelPriority executed successfully\r\n");

    /*Create XCVR SDMA Transfer Handle*/
    XCVR_TransferTxCreateHandleSDMA(app->earc_base, &xcvrHandle, NULL, &sdmaHandle,XCVR_TX_SOURCE);
    PRINTF("Audio XCVR : XCVR_TransferTxCreateHandleSDMA executed successfully\r\n");

    /* Default bytes per frame 4 bytes for iec60958 frame and 64 is taken as count for each request */
    int bps = 4;

     /* If IEC60958 frame format is enabled, set bytes per sample accordingly */
    if(app->xcvr_fill_frame) {
        bps = app->bps / 8;
    }

    /*Set the transfer configuration*/
    XCVR_TransferTxSetConfigSDMA(app->earc_base, &xcvrHandle, bps, 64);

        /*  xfer structure */
    temp = &app->audio_src[0];

    xfer.data     = temp;
    xfer.dataSize = CHUNK_SIZE;
    XCVR_TransferSendSDMA(app->earc_base, &xcvrHandle, &xfer);

    xfer.data     = temp + CHUNK_SIZE;
    xfer.dataSize = CHUNK_SIZE;
    XCVR_TransferSendSDMA(app->earc_base, &xcvrHandle, &xfer);

    xfer.data     = temp + 2*CHUNK_SIZE;
    xfer.dataSize = CHUNK_SIZE;
    XCVR_TransferSendSDMA(app->earc_base, &xcvrHandle, &xfer);

    xfer.data     = temp + 3*CHUNK_SIZE;
    xfer.dataSize = CHUNK_SIZE;
    XCVR_TransferSendSDMA(app->earc_base, &xcvrHandle, &xfer);
}

/* Initial configuration setup for XCVR handle */
int app_config(app_instance_t *app, xcvr_handle_t *xcvr_handle) {

    xcvr_handle->dma_enable = app->dma_enable;
    xcvr_handle->xcvr_fill_iec60958_frame = app->xcvr_fill_frame;

    if(!app->dma_enable) {
        xcvr_handle->xcvr_irq_handle.src_add = app->audio_src;
        xcvr_handle->xcvr_irq_handle.dest_add = AUDIO_XCVR_TX_FIFO;
        xcvr_handle->xcvr_irq_handle.rem_data = app->audio_src_len;
        xcvr_handle->xcvr_irq_handle.chunk_size = CHUNK_SIZE;
    } else {
        app_dma_config(app);
    }
    return 0;
}

/* Application setup for transferring data */
int app_setup(app_instance_t *app)
{
    /*Setting up one of Raw PCM or IEC60958 frames as source */
    if (app_source_init(app)) {
        PRINTF("audio source not initialized\r\n");
        return -1;
    }

    /* Initial configuration setup for XCVR handle */
    app_config(app,&xcvrHandle);

    return 0;
}

int main(void){

    app_instance_t *app;
    app = &g_app;

    app_init(app); /* Initialize application instance structure */

    /* Init board hardware. */
    BOARD_InitHardware();

    IOMUXC_SetPinMux(IOMUXC_SPDIF_TX_AUDIOMIX_SPDIF1_OUT, 0U);
    IOMUXC_SetPinConfig(IOMUXC_SPDIF_TX_AUDIOMIX_SPDIF1_OUT,0xd6);

    IOMUXC_SetPinMux(IOMUXC_SPDIF_RX_AUDIOMIX_SPDIF1_IN, 0U);
    IOMUXC_SetPinConfig(IOMUXC_SPDIF_RX_AUDIOMIX_SPDIF1_IN,0xd6);

    IOMUXC_SetPinMux(IOMUXC_SPDIF_EXT_CLK_AUDIOMIX_SPDIF1_EXT_CLK, 0U);
    IOMUXC_SetPinConfig(IOMUXC_SPDIF_EXT_CLK_AUDIOMIX_SPDIF1_EXT_CLK,0xd6);
    PRINTF("Audio XCVR Demo Application.\r\n");

    /* Initialize Audio XCVR */
    XCVR_Init(app, &xcvrHandle);

    /* Audio XCVR: Load firmware */
    XCVR_load_firmware(xcvr_imx8mp_fw_bin, xcvr_imx8mp_fw_bin_len);

    /* Audio XCVR: Configure for S/PDIF Tx transmission */
    XCVR_Prepare(app);
    PRINTF("Audio XCVR: Prepare executed successfully\r\n");

    /* Application setup for transferring data */
    if (app_setup(app))
        return -1;

    print_xcvr_config_register(app->earc_base);

    if(app->xcvr_fill_frame) {

        /* Set CS and UD Values based on sample rate */
        Set_CS_UD_Values(app,CS_value, UD_value);

        /* Write CS Values to Register */
        XCVR_write_CS_to_Reg(app->earc_base, CS_value);

        /* Write UD Values to Register */
        XCVR_write_UD_to_Reg(app->earc_base, UD_value);

        /* XCVR register Tx Data Path further configured for enable CS , UD, Valid, Preamble, Parity bits from xcvr register */
        XCVR_AdvanceConfiguration(app->earc_base); // CS, UD, Valid, Parity, Preamble bits enabled
    }

    XCVR_Trigger(app->earc_base, start, &xcvrHandle, app_callback); // SDMA Write Enabled in start case of xcvr_trigger

    PRINTF("Audio XCVR : XCVR_Trigger executed successfully\r\n");

    /* To ensure that accessed data are correct */
    for(int i=0;i<192;i++) {
        if(i%16 == 0)
            PRINTF("\r\n");
        int temp = xcvrHandle.xcvr_irq_handle.src_add[i];
        PRINTF("0x%02x ",temp);
    }
    print_xcvr_config_register(app->earc_base);

    while (app->TransferDone != true)
    {
        /* code */
    }
    XCVR_Trigger(app->earc_base, stop, &xcvrHandle, app_callback); // SDMA Write Disabled in stop case of xcvr_trigger
    PRINTF("Audio XCVR : Transfer completed\r\n");
    // while(1);
    PRINTF("Audio XCVR Demo Application Exit.\r\n");

    return 0;
}
