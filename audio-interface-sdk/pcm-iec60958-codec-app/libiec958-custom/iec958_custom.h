#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define BUFFER_SIZE 384

typedef struct {
    uint32_t preamble : 4;
    uint32_t aux : 4;
    uint32_t data : 20;
    uint32_t valid : 1;
    uint32_t user : 1;
    uint32_t cs : 1;
    uint32_t parity : 1;
} iec958Frame;

/* iec60958_init: Function initialise the context with channel status values based on input parameters */
int iec60958_init(void **ptr_header, uint32_t sample_rate, uint16_t channel_no, uint16_t bps, uint32_t size);

/* iec60958_encode: Function encodes the PCM data into IEC60958 frames with channel status, user data, validity and preamble */
int iec60958_encode(void *ptr, uint16_t *iec_in, size_t in_size, iec958Frame *iec_out, size_t *num_out_frames_to_write);

/* iec60958_decode: Function decodes the IEC60958 frames into PCM data */
uint16_t iec60958_decode(uint32_t *iec_in, size_t in_size, uint16_t *iec_out, size_t *num_out_frames_to_write);

/* extract_cs: Function extracts channel status from IEC60958 frames */
int extract_cs(uint32_t *iec_in, size_t in_size, FILE *srcfile, uint8_t *cs_data_left_ch, uint8_t *cs_data_right_ch, int offset);

/* cs_logging: Function logs the channel status information in human readable format */
int cs_logging(uint8_t *cs_data);

/* iec60958_deinit: Function deinitialises the context and frees the allocated memory */
int iec60958_deinit(void *ptr, uint8_t *cs_data_left_ch, uint8_t *cs_data_right_ch);

/* CS_Comparator: Function compares the extracted channel status with expected channel status */
int CS_Comparator(uint8_t *cs_data, int cs_size);

/* Compare_Left_Right_CS: Function compares the left and right channel status for consistency */
int Compare_Left_Right_CS(uint8_t *left_ch, uint8_t *right_ch, int cs_size);