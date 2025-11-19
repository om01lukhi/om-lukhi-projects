#include "iec958_custom.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define PREAMBLE_B 0x0 // starting of block
#define PREAMBLE_W 0x1 // odd block
#define PREAMBLE_M 0x3 // even block

#define CS_consumer_use 0x00
#define CS_professional_use 0x01
#define CS_OtherThanLinearPCM 0x02
#define CS_NoCpRightAsserted 0x04 // bit2 modify if no copy right asserted
// bit 3-4-5 all 0 means 2 audio channel without pre-emphasis
#define CS_2AudioCh_50by15 PreEmphesis 0x08
#define CS_ReservedFor2AudioCh_PreEmphasis 0x10

// byte1
// #define CS_CatCode_Musical 0x7D
#define CS_CatCode_Optical 0x82


// byte[2]
#define CS_SourceNo1 0x01
#define CS_SourceNo2 0x02
#define CS_SourceNo3 0x03
//...continue
#define CS_leftChannel 0x10
#define CS_rightChannel 0x20

// byte[3]
#define CS_samplingFreq_22050 0x04 // bit 24-27
#define CS_samplingFreq_44100 0x00
#define CS_samplingFreq_88200 0x08
#define CS_samplingFreq_176400 0x0C
#define CS_samplingFreq_24000 0x06
#define CS_samplingFreq_48000 0x02
#define CS_samplingFreq_96000 0x0A
#define CS_samplingFreq_192000 0x0E
#define CS_samplingFreq_32000 0x03
#define CS_samplingFreq_768000 0x0D

#define CS_clockAccuracy_L2 0x00 // bit 28-29
#define CS_clockAccuracy_L1 0x10
#define CS_clockAccuracy_L3 0x20
// bit 30-31 are sampling freq extension, putting it 0 for now

// byte[4]
#define CS_20bit_data 0x00 // bit 32
#define CS_24bit_data 0x01

#define CS_20or16bits 0x02 // bit 33-35
#define CS_22or18bits 0x04
#define CS_23or19bits 0x08
#define CS_24or20bits 0x0A
#define CS_21or17bits 0x0C

#define CS_OgSamplingFreq_22050 0xb0 // bit 36-39
#define CS_OgSamplingFreq_44100 0xf0
#define CS_OgSamplingFreq_88200 0x70
#define CS_OgSamplingFreq_176400 0x30
#define CS_OgSamplingFreq_24000 0x90
#define CS_OgSamplingFreq_48000 0xd0
#define CS_OgSamplingFreq_96000 0x50
#define CS_OgSamplingFreq_192000 0x10
#define CS_OgSamplingFreq_32000 0xc0
#define CS_OgSamplingFreq_128000 0xe0
#define CS_OgSamplingFreq_8000 0x60
#define CS_OgSamplingFreq_11025 0xa0
#define CS_OgSamplingFreq_12000 0x20
#define CS_OgSamplingFreq_64000 0x40
#define CS_OgSamplingFreq_16000 0x80

// byte 5

#define CS_CopyingPermitted 0x00
#define CS_oneGenCopy 0x01
#define CS_NoCopyPermitted 0x03

// static WavHeader header;

typedef struct {

    uint8_t byte[24];

} ChannelStatus;

typedef struct {
    uint32_t sample_rate;
    uint16_t no_of_channel;
    uint16_t bps;
    uint32_t size;
} IEC60958_Context;


int iec60958_init(void **pHandle, uint32_t sample_rate, uint16_t num_chans, uint16_t bps, uint32_t size) {
    IEC60958_Context *iec958_ctx = (IEC60958_Context *)malloc(sizeof(IEC60958_Context));
    if (iec958_ctx == NULL) {
        exit(EXIT_FAILURE);
    }
    iec958_ctx->sample_rate = sample_rate;
    iec958_ctx->no_of_channel = num_chans;
    iec958_ctx->bps = bps;
    iec958_ctx->size = size;
    *pHandle = iec958_ctx;
    return 0;
}

// void iec958_CS_value_set(ChannelStatus *cs)
static void iec958_CS_value_set(ChannelStatus *cs, IEC60958_Context *iec958_ctx) {
    memset(cs, 0, sizeof(ChannelStatus));

    cs->byte[0] = 0x04;
    cs->byte[1] = CS_CatCode_Optical;
    cs->byte[2] = 0;

    switch (iec958_ctx->sample_rate) {
    case 44100:
        cs->byte[3] = 0x00;
        break;
    case 88200:
        cs->byte[3] = 0x08;
        break;
    case 176400:
        cs->byte[3] = 0x0c;
        break;
    case 24000:
        cs->byte[3] = 0x06;
        break;
    case 48000:
        cs->byte[3] = 0x02;
        break;
    case 96000:
        cs->byte[3] = 0x0a;
        break;
    case 192000:
        cs->byte[3] = 0x0e;
        break;
    case 32000:
        cs->byte[3] = 0x03;
        break;
    case 768000:
        cs->byte[3] = 0x09;
        break;
    default:
        break;
    }

    cs->byte[4] = CS_20bit_data | CS_20or16bits;

    /* here & 0 is done to take default value , if conversion of sampling frequency happens this can be used */
    switch (iec958_ctx->sample_rate & 0) {
    case 44100:
        cs->byte[4] |= CS_OgSamplingFreq_44100;
        break;
    case 88200:
        cs->byte[4] |= CS_OgSamplingFreq_88200;
        break;
    case 176400:
        cs->byte[4] |= CS_OgSamplingFreq_176400;
        break;
    case 24000:
        cs->byte[4] |= CS_OgSamplingFreq_24000;
        break;
    case 48000:
        cs->byte[4] |= CS_OgSamplingFreq_48000;
        break;
    case 96000:
        cs->byte[4] |= CS_OgSamplingFreq_96000;
        break;
    case 192000:
        cs->byte[4] |= CS_OgSamplingFreq_192000;
        break;
    case 32000:
        cs->byte[4] |= CS_OgSamplingFreq_32000;
        break;
    case 128000:
        cs->byte[4] |= CS_OgSamplingFreq_128000;
        break;
    case 8000:
        cs->byte[4] |= CS_OgSamplingFreq_8000;
        break;
    case 11025:
        cs->byte[4] |= CS_OgSamplingFreq_11025;
        break;
    case 12000:
        cs->byte[4] |= CS_OgSamplingFreq_12000;
        break;
    case 64000:
        cs->byte[4] |= CS_OgSamplingFreq_64000;
        break;
    case 16000:
        cs->byte[4] |= CS_OgSamplingFreq_16000;
        break;
    default:
        cs->byte[4] &= ~0xf0;
    }
    cs->byte[5] = CS_CopyingPermitted;
}

static uint8_t get_channel_status(ChannelStatus *cs, int count) {

    unsigned int byte = count >> 3;
    unsigned int mask = 1 << (count - (byte << 3));
    unsigned int bit_pos = count & 7;
    return (cs->byte[byte] & mask) >> (bit_pos);
}

static int calculate_parity(int data) {
    int p = 0;
    while (data) {
        p ^= (data & 1);
        data >>= 1;
    }
    return p;
}

static iec958Frame prepare_subframe(uint32_t data, uint8_t cs, uint8_t preamble, uint8_t valid) {
    iec958Frame frame = {0};
    uint32_t frame_data = (data << 8) | (valid << 28) | (cs << 30);
    frame.parity = calculate_parity(frame_data);
    frame.cs = cs;
    frame.user = 0;
    frame.valid = valid;
    frame.data = (data & 0xFFFF) << 4;
    frame.aux = 0;
    frame.preamble = preamble;

    return frame;
}

int count = 0;
int block_frame = 0;
int iec60958_encode(void *ptr, uint16_t *iec_in, size_t in_size, iec958Frame *iec_out, size_t *num_out_frames_to_write) {
    IEC60958_Context *iec958_ctx = (IEC60958_Context *)ptr;
    ChannelStatus cs;
    if (iec958_ctx == NULL || iec_in == NULL || iec_out == NULL) {
        printf("Give arguements in encode are invalid\n");
        return EXIT_FAILURE;
    }

    iec958_CS_value_set(&cs, iec958_ctx);

    for (size_t i = 0; i < in_size; i++) {
        uint8_t status, preamble;

        if (block_frame == 0 && (count % 2 == 0)) {
            preamble = PREAMBLE_B;
            status = get_channel_status(&cs, block_frame);
        } else if (count % 2 == 0) {
            preamble = PREAMBLE_W;
            status = get_channel_status(&cs, block_frame);
        } else {
            preamble = PREAMBLE_M;
            status = get_channel_status(&cs, block_frame);
        }

        uint8_t valid = (iec_in[i] <= 0xFFFF) ? 0 : 1;

        iec_out[i] = prepare_subframe(iec_in[i], status, preamble, valid);

        count++;
        if (count % 2 == 0) {
            block_frame = (block_frame + 1) % 192;
        }
    }

    *num_out_frames_to_write = in_size;

    return EXIT_SUCCESS;
}

uint16_t iec60958_decode(uint32_t *iec_in, size_t in_size, uint16_t *iec_out, size_t *num_out_frames_to_write) {
    if (iec_in == NULL || iec_out == NULL) {
        printf("Give arguements in decode are invalid\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < in_size; i++) {
        int temp = 0;
        temp = (iec_in[i] & 0x0ffff000);
        iec_out[i] = temp >> 12;
    }
    *num_out_frames_to_write = in_size;
    return EXIT_SUCCESS;
}

int extract_cs(uint32_t *iec_in, size_t in_size, FILE *srcfile, uint8_t *cs_data_left_ch, uint8_t *cs_data_right_ch, int offset) {

    for (size_t i = 0; i < in_size; i++) {
        int frame_idx = i / 2;
        int byte_idx  = frame_idx / 8;
        int bit_idx   = frame_idx % 8;
        int cs_bit = (iec_in[i] >> 30) & 0x1;  // extract bit 30
        if(i%2 == 0) { // to extract channel status only once for two channels
            if (cs_bit)
                cs_data_left_ch[offset + byte_idx] |= (1 << bit_idx);
            else
                cs_data_right_ch[offset + byte_idx] &= ~(1 << bit_idx);
        } else {
            if (cs_bit)
                cs_data_right_ch[offset + byte_idx] |= (1 << bit_idx);
            else
                cs_data_right_ch[offset + byte_idx] &= ~(1 << bit_idx);
        }
    }
    return 0;
}
int cs_logging(uint8_t *cs_data) {

    printf("\nChannel Status Details:\n");

    for(int i = 0; i < 24; i++) {

        if(i==0) {
            printf("\nByte [%d] = 0x%02x : General control and mode information\n",i, cs_data[i]);
            switch(cs_data[i] & 0x01) {
                case 0:
                    printf("bit 0 = 0: Consumer use\n");
                    break;
                default:
                    printf("Reserved\n");
            }

            switch((cs_data[i] >> 1) & 0x1) {
                case 0:
                    printf("bit 1 = 0: Audio sample word represents linear PCM samples\n");
                    break;
                case 1:
                    printf("bit 1 = 1: Audio sample word used for other purposes\n");
                    break;
                default:
                    printf("Reserved\n");
            }

            switch((cs_data[i] >> 2) & 0x1) {
                case 0:
                    printf("bit 2 = 0: Software for which Copyright asserted\n");
                    break;
                case 1:
                    printf("bit 2 = 1: Software for which No copyright asserted\n");
                    break;
                default:
                    printf("Reserved\n");
            }
            switch (cs_data[i] >> 3 & 0x07) {
                case 0:
                    printf("bit 3-5 = 000: Two audio channels, no pre-emphasis\n");
                    break;
                case 1:
                    printf("bit 3-5 = 100: Two audio channels, 50/15 microsecond pre-emphasis\n");
                    break;
                case 2:
                    printf("bit 3-5 = 101: Reserved for two audio channels, with pre-emphasis\n");
                    break;
                case 3:
                    printf("bit 3-5 = 110: Reserved for two audio channels, with pre-emphasis\n");
                    break;

                default:
                    printf("All other states of bits 3 to 5 are reserved and shall not be used until further defined.\n");
            }
            switch(cs_data[i] >> 6 & 0x03) {
                case 00:
                    printf("bit 6-7 = 00: Mode 0\n");
                    break;
                default:
                    printf("bit 6-7: All other states of bits 6 and 7 are reserved and shall not be used until further defined\n");
            }
        }
        else if(i == 1) {
            printf("Byte 1 = 0x%02x \n", cs_data[i]);
            switch(cs_data[i] & 0xf) {
                case 0:
                    printf("Bit 8-15 = 0000 Category code: General. Used temporarily\n");
                    break;
                case 1:
                    printf("Bit 8-15 = 100XXXXL Category code: Laser optical products\n");
                    break;
                case 2:
                    printf("Bit 8-15 = 010XXXXL Category code: Digital converters and signal processing products\n");
                    break;
                case 3:
                    printf("Bit 8-15 = 110XXXXL Category code: Magnetic tape or disc based products\n");
                    break;
                case 4:
                case 14:
                    printf("Bit 8-15 = 001XXXXL or 011 1XXXL Category code: Broadcast reception of digitally encoded audio signals with or without video signals\n");
                    break;
                case 5:
                    printf("Bit 8-15 = 101XXXXL Category code: Musical instruments, microphones and other sources without copyright information\n");
                    break;
                case 6:
                    printf("Bit 8-15 = 111XXXXL Category code: Analogue/digital converters for analogue signals with or without copyright information\n");
                    break;
                case 7:
                    printf("Bit 8-15 = 0001XXXXL Category code: Not defined reserved\n");
                    break;
                case 8:
                    printf("Bit 8-15 = 0001XXXXL Category code: Solid-state memory-based products\n");
                    break;
                default:
                    printf("All other states of bits 8 to 15 are reserved and shall not be used until further defined\n");
            }
        }
        else if(i == 2) {
            printf("\nByte [%d] = 0x%02x : Source number and channel number\n", i, cs_data[i]);
            int temp = cs_data[i] & 0xf;
            if(temp == 0)
                printf("Bit 16-19 = 0000: Source number: Do not take into account\n");
            else
                printf("Bit 16 - 19: %x: source number: %d\n", temp, temp);

            switch((cs_data[i] >> 4) & 0xf) {
                case 0:
                    printf("Bit 20-23 = 0000: No channel mode specified\n");
                    break;
                case 1:
                    printf("Bit 20-23 = 0001: Left channel for stereo channel format\n");
                    break;
                case 2:
                    printf("Bit 20-23 = 0010: Right channel for stereo channel format\n");
                    break;
                default:
                    printf("All other states of bits 20 to 21 are reserved and shall not be used until further defined\n");
            }
        }
        else if(i == 3) {
            printf("\nByte [%d] = 0x%02x : sampling frequency and clock accuracy\n", i, cs_data[i]);
            switch(cs_data[i] & 0xf)
            {
                case 0x0:
                    printf("Bit 24-27 = 0000: Sampling frequency: 44.1 kHz\n");
                    break;
                case 0x2:
                    printf("Bit 24-27 = 0100: Sampling frequency: 48 kHz\n");
                    break;
                case 0x3:
                    printf("Bit 24-27 = 1100: Sampling frequency: 32 kHz\n");
                    break;
                case 0x4:
                    printf("Bit 24-27 = 0010: Sampling frequency: 22.05 kHz\n");
                    break;
                case 0x6:
                    printf("Bit 24-27 = 0110: Sampling frequency: 24 kHz\n");
                    break;
                case 0x8:
                    printf("Bit 24-27 = 0001: Sampling frequency: 88.2 kHz\n");
                    break;
                case 0xa:
                    printf("Bit 24-27 = 0101: Sampling frequency: 96 kHz\n");
                    break;
                case 0xc:
                    printf("Bit 24-27 = 0011: Sampling frequency: 176.4 kHz\n");
                    break;
                case 0xe:
                    printf("Bit 24-27 = 0111: Sampling frequency: 192 kHz\n");
                    break;
                case 0x9:
                    printf("Bit 24-27 = 1001: Sampling frequency: 768 kHz\n");
                    break;
                default:
                    printf("All other states of bits 24 to 27 are reserved and shall not be used until further defined\n");
            }
            switch((cs_data[i] >> 4) & 0x3) {
                case 0:
                    printf("Bit 28-29 = 00: Level II clock accuracy\n");
                    break;
                case 1:
                    printf("Bit 28-29 = 10: Level I clock accuracy\n");
                    break;
                case 2:
                    printf("Bit 28-29 = 01: Level III clock accuracy\n");
                    break;
                default:
                    printf("Bit 28-29 = 11: Interface frame rate not matched to sampling frequency.\n");
            }
            switch((cs_data[i] >> 6) & 0x3) {
                case 0:
                    switch(cs_data[i] & 0xf) {
                        case 0x5:
                            printf("Bit 24-27 + 30-31 = 101000: Sampling frequency extension: 384 kHz\n");
                            break;
                        case 0xb:
                            printf("Bit 24-27 + 30-31 = 110100: Sampling frequency extension: 64 kHz\n");
                            break;
                        case 0xd:
                            printf("Bit 24-27 + 30-31 = 101100: Sampling frequency extension: 352.8 kHz\n");
                            break;
                        default:
                            break;
                    }
                case 1:
                    switch (cs_data[i] & 0xf) {
                        case 0x5:
                            printf("Bit 24-27 + 30-31 = 101010: Sampling frequency extension: 1536 kHz\n");
                            break;
                        case 0xb:
                            printf("Bit 24-27 + 30-31 = 110110: Sampling frequency extension: 256 kHz\n");
                            break;
                        case 0xd:
                            printf("Bit 24-27 + 30-31 = 101110: Sampling frequency extension: 1411.2 kHz\n");
                            break;
                        default:
                            break;
                    }
                case 2:
                     switch (cs_data[i] & 0xf) {
                        case 0xb:
                            printf("Bit 24-27 + 30-31 = 110101: Sampling frequency extension: 128 kHz\n");
                            break;
                        case 0xd:
                            printf("Bit 24-27 + 30-31 = 101101: Sampling frequency extension: 705.6 kHz\n");
                            break;
                        default:
                            break;
                    }
                case 3:
                    switch (cs_data[i] & 0xf) {
                        case 0x5:
                            printf("Bit 24-27 + 30-31 = 101011: Sampling frequency extension: 1024 kHz\n");
                            break;
                        case 0xb:
                            printf("Bit 24-27 + 30-31 = 110111: Sampling frequency extension: 512 kHz\n");
                            break;
                        default:
                            break;
                    }
                default:
                    printf("Bit 30-31 = 00: No sampling frequency extension\n");
                    break;
            }
        }
        else if(i == 4) {
            printf("\nByte [%d] = 0x%02x : word length and original sampling frequency\n", i, cs_data[i]);
            switch(cs_data[i] & 0x1) {
                case 0:
                    printf("Bit 32 = 0: Maximum audio sample word length is 20 bits\n");
                    break;
                case 1:
                    printf("Bit 32 = 1: Maximum audio sample word length is 24 bits\n");
                    break;
                default:
                    printf("All other states of bit 32 are reserved and shall not be used until further defined\n");
            }
            switch((cs_data[i] >> 1) & 0x07) {
                case 0x0:
                    printf("Bit 33-35 = 000: Word length not indicated (default)\n");
                    break;
                case 0x1:
                    printf("Bit 33-35 = 001: Audio sample word length: 20 if max len=24 or 16 bits if max len=20\n");
                    break;
                case 0x2:
                    printf("Bit 33-35 = 010: Audio sample word length: 22 if max len=24 or 18 bits if max len=20\n");
                    break;
                case 0x4:
                    printf("Bit 33-35 = 001: Audio sample word length: 23 if max len=24 or 19 bits if max len=20\n");
                    break;
                case 0x5:
                    printf("Bit 33-35 = 101: Audio sample word length: 24 if max len=24 or 20 bits if max len=20\n");
                    break;
                case 0x6:
                    printf("Bit 33-35 = 011: Audio sample word length: 21 if max len=24 or 17 bits if max len=20\n");
                    break;
                default:
                    printf("All other states of bits 33 to 35 are reserved and shall not be used until further defined\n");
            }
            switch((cs_data[i] >> 4) & 0xf) {
                case 0xf:
                    printf("Bit 36-39 = 1111: Original sampling frequency:44.1 kHz\n");
                    break;
                case 0x7:
                    printf("Bit 36-39 = 1110: Original sampling frequency:88.2 kHz\n");
                    break;
                case 0xb:
                    printf("Bit 36-39 = 1101: Original sampling frequency:22.05 kHz\n");
                    break;
                case 0x3:
                    printf("Bit 36-39 = 1100: Original sampling frequency:176.4 kHz\n");
                    break;
                case 0xd:
                    printf("Bit 36-39 = 1011: Original sampling frequency:48 kHz\n");
                    break;
                case 0x5:
                    printf("Bit 36-39 = 1010: Original sampling frequency:96 kHz\n");
                    break;
                case 0x9:
                    printf("Bit 36-39 = 1001: Original sampling frequency:24 kHz\n");
                    break;
                case 0x1:
                    printf("Bit 36-39 = 1000: Original sampling frequency:192 kHz\n");
                    break;
                case 0xe:
                    printf("Bit 36-39 = 0111: Original sampling frequency:128 kHz\n");
                    break;
                case 0x6:
                    printf("Bit 36-39 = 0110: Original sampling frequency:8 kHz\n");
                    break;
                case 0xa:
                    printf("Bit 36-39 = 0101: Original sampling frequency:11025 kHz\n");
                    break;
                case 0x2:
                    printf("Bit 36-39 = 0100: Original sampling frequency:12 kHz\n");
                    break;
                case 0xc:
                    printf("Bit 36-39 = 0011: Original sampling frequency:32 kHz\n");
                    break;
                case 0x4:
                    printf("Bit 36-39 = 0010: Original sampling frequency:64 kHz\n");
                    break;
                case 0x8:
                    printf("Bit 36-39 = 0001: Original sampling frequency:16 kHz\n");
                    break;
                case 0x0:
                    printf("Bit 36-39 = 0000: Original sampling frequency not indicated\n");
                    break;
                default:
                    printf("All other states of bits 36 to 39 are reserved and shall not be used until further defined\n");
            }
        }
        else if(i == 5) {
            printf("\nByte [%d] = 0x%02x : Copying and emphasis\n", i, cs_data[i]);
            switch(cs_data[i] & 0x3) {
                case 0:
                    printf("Bit 40-41 = 00: Copying permitted\n");
                    break;
                case 1:
                    printf("Bit 40-41 = 10: One generation of copies permitted\n");
                    break;
                case 3:
                    printf("Bit 40-41 = 11: No copying permitted\n");
                    break;
                default:
                    printf("Bit 40-41 = 01: Condition not used\n");
            }
            switch((cs_data[i] >> 1) & 0x1) {
                case 0:
                    printf("Bit 42 = 0: No indication\n");
                    break;
                case 1:
                    printf("Bit 42 = 1: GGMS-A valid\n");
                    break;
                default:
                    printf("Bit 42 = 11: Reserved\n");
            }
            switch((cs_data[i] >> 4) & 0xf) {
                case 0:
                    printf("Bit 44-47 = 0000: Not indicated\n");
                    break;
                case 8:
                    printf("Bit 44-47 = 0001: Audio sampling freq coefficient: Equal to transmission sampling frequency\n");
                    break;
                case 4:
                    printf("Bit 44-47 = 0010: Audio sampling freq coefficient: 1/2\n");
                case 12:
                    printf("Bit 44-47 = 0011: Audio sampling freq coefficient: 1/4\n");
                    break;
                case 2:
                    printf("Bit 44-47 = 0100: Audio sampling freq coefficient: 1/8\n");
                    break;
                case 10:
                    printf("Bit 44-47 = 0101: Audio sampling freq coefficient: 1/16\n");
                    break;
                case 6:
                    printf("Bit 44-47 = 0110: Audio sampling freq coefficient: 1/32\n");
                    break;
                case 13:
                    printf("Bit 44-47 = 0111: Audio sampling freq coefficient: x32\n");
                    break;
                case 3:
                    printf("Bit 44-47 = 1000: Audio sampling freq coefficient: x16\n");
                    break;
                case 11:
                    printf("Bit 44-47 = 1001: Audio sampling freq coefficient: x8\n");
                    break;
                case 7:
                    printf("Bit 44-47 = 1010: Audio sampling freq coefficient: x4\n");
                    break;
                case 15:
                    printf("Bit 44-47 = 1011: Audio sampling freq coefficient: x2\n");
                    break;
                default:
                    printf("All other states of bits 44 to 47 are reserved and shall not be used until further defined\n");
            }
        }
        else if(i==6) {
            printf("\nByte [%d] = 0x%02x and Byte [%d] = 0x%02x : Information hidden in PCM signal and Channel number\n", i, cs_data[i],i+1,cs_data[i+1]);
            switch(cs_data[i] & 0x1) {
                case 0:
                    printf("Bit 48 = 0: No information hidden in PCM signal\n");
                    break;
                case 1:
                    printf("Bit 48 = 1: Information hidden in PCM signal\n");
                    break;
                default:
                    printf("Bit 48 = 11: Reserved\n");
            }
            switch((cs_data[i] >> 1) & 0x3f) {
                case 0:
                    printf("Bit 49-54 = 000000:General channel assignment for A ch: Channel number 1\n");
                    break;
                default:
                    printf("Bit 49-54 = %02x: General channel assignment for A ch: Channel number: %d\n", ((cs_data[i] >> 1) & 0x3f) - 1, ((cs_data[i] >> 1) & 0x3f) - 1);
                    break;
            }
            switch(((cs_data[i+1] & 0x1f)<<1) + (cs_data[i]>>7 & 1)) {
                case 0:
                    printf("Bit 55-60 = 000000:General channel assignment for B ch: Channel number 1\n");
                    break;
                default:
                    printf("Bit 55-60 = %02x: General channel assignment for B ch: Channel number: %d\n", ((cs_data[i+1] & 0x1f)<<1) + (cs_data[i]>>7 & 1) - 1, 
                    ((cs_data[i+1] & 0x1f)<<1) + (cs_data[i]>>7 & 1) - 1);
                    break;
            }
        }
        else {
            // bytes from 6 to 23 are reserved for future use
            printf("\nByte [%d] = 0x%02x : Reserved for future use\n", i, cs_data[i]);
        }
    }
    return 0;
}

int iec60958_deinit(void *ptr, uint8_t *cs_data_left_ch, uint8_t *cs_data_right_ch) {
    free(ptr);
    free(cs_data_left_ch);
    free(cs_data_right_ch);
    return 0;
}

int CS_Comparator(uint8_t *cs, int cs_size) {
    uint8_t *expected_cs = malloc(24 * sizeof(uint8_t));

    for(int i=0; i<24; i++) {
        expected_cs[i] = cs[i];
    }

    for(int i=0; i<cs_size; i++) {
        if(cs[i] != expected_cs[i%24]) {
            printf("Channel status mismatch at byte %d: expected 0x%02x, got 0x%02x\n", i, expected_cs[i%24], cs[i]);
            free(expected_cs);
            return -1;
        }
    }
    printf("Channel status comparision is over and fully matched\n");
    free(expected_cs);
    return 0;
}

int Compare_Left_Right_CS(uint8_t *left_ch, uint8_t *right_ch, int cs_size) {
    for(int i=0; i<cs_size; i++) {
        if(left_ch[i] != right_ch[i]) {
            printf("Channel status mismatch between left and right channel at byte %d: left 0x%02x, right 0x%02x\n", i, left_ch[i], right_ch[i]);
            return -1;
        }
    }
    printf("Channel status comparision between left and right channel is over and fully matched\n");
    return 0;
}