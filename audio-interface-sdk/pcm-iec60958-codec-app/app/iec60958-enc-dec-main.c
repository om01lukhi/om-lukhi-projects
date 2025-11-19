#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <iec958_custom.h>

typedef struct
{
    char riff[4];
    uint32_t file_size;
    char file_type[4];
    char format[4];
    uint32_t format_length;
    uint16_t format_type;
    uint16_t channel_no;
    uint32_t sample_rate;
    uint32_t bit_rate;
    uint16_t block_align;
    uint16_t bps;
    char chunk_header[4];
    int32_t size;
} WavHeader;

int main(int argc, char *argv[]) {

    int offset = 0;
    uint8_t *cs_data_left_ch = malloc(sizeof(uint8_t) * 80000); // channel status data storage
    uint8_t *cs_data_right_ch = malloc(sizeof(uint8_t) * 80000);

    if (argc < 3) {
        printf("Format: ./app-iec60958-enc-dec [encode/decode] [src_file] [dst_file] [raw/wav]\n");
        printf("Mentioning raw or wav is optional (wav is DEFAULT), NOTE: for encoding raw input is not allowed as wavHeader is must for iec958 framing\n");
        exit(EXIT_FAILURE);
    }

    const char *d;
    const char *a = argv[2];
    const char *b = argv[3];
    const char *c = argv[1];

    if(argv[4] == NULL)
        d = "wav"; // Default is given wav, if not mentioned otherwise
    else
        d = argv[4];

    FILE *srcfile = fopen(a, "rb");
    FILE *dstfile = fopen(b, "wb");

    if (srcfile == NULL) {
        printf("Your sourcefile path is invalid\n)");
        exit(EXIT_FAILURE);
    } else if (dstfile == NULL) {
        printf("Your destination file path is invalid\n");
        exit(EXIT_FAILURE);
    }

    /* If raw is mentioned in encoding, app will print error, else header will be printed and encoding will take place */
    if(strcmp(d,"raw") == 0 && strcmp(c,"encode")==0) {
        printf("Raw data is not accepeted in framing/encoding, as CS are required wavheader parameters\n");
        return EXIT_FAILURE;
    }
    size_t num_frames_to_process = 384; // 192 samples per channel, for 2 channel it will be 384
    size_t num_out_frames_to_write = 0;
    void *iec958_handle;

    if (strcmp(c, "encode") == 0) {
        WavHeader header;
        fread(&header, sizeof(WavHeader), 1, srcfile);
        iec60958_init(&iec958_handle, header.sample_rate, header.channel_no, header.bps, header.size);

        printf("chunk_name: %.4s \n", header.riff);
        printf("file size: %d \n", header.file_size);
        printf("format: %.4s \n", header.file_type);
        printf("chunk_id: %.4s \n", header.format);
        printf("format size: %d \n", header.format_length);
        printf("format type: %d \n", header.format_type);
        printf("number of channel: %d \n", header.channel_no);
        printf("sample rate: %d \n", header.sample_rate);
        printf("speed (bytes per second): %d \n", header.bit_rate);
        printf("header block align: %d \n", header.block_align);
        printf("bits per sample: %d \n", header.bps);
        printf("chunk header: %.4s \n", header.chunk_header);
        printf("file size(data): %d \n", header.size);

        fseek(srcfile, 44, SEEK_SET);

        uint16_t *iec_in = (uint16_t *)malloc(sizeof(uint16_t) * num_frames_to_process);
        int ret;
        iec958Frame *iec_out = (iec958Frame *)malloc(sizeof(iec958Frame) * num_frames_to_process);

        num_frames_to_process = num_frames_to_process < BUFFER_SIZE ? num_frames_to_process : BUFFER_SIZE;
        while ((fread(iec_in, sizeof(uint16_t), num_frames_to_process, srcfile)) > 0) {
            ret = iec60958_encode(iec958_handle, iec_in, num_frames_to_process, iec_out, &num_out_frames_to_write);
            if (ret != EXIT_SUCCESS) {
                printf("Process error\n");
                return ret;
            }
            fwrite(iec_out, sizeof(iec958Frame), num_out_frames_to_write, dstfile);
        }
    } else if (strcmp(c, "decode") == 0) {
        uint32_t *iec_in = (uint32_t *)malloc(sizeof(uint32_t) * num_frames_to_process);
        uint16_t *iec_out = (uint16_t *)malloc(sizeof(uint16_t) * num_frames_to_process);
        int ret;

        /* if not mentioned raw, wav header will also be included along with extracted PCM */
        if(strcmp(d,"wav")==0)  {
            /* as of now it will print zero header, in more advanced app channel status will be parsed
            and wavheader parameters will be extracted from status values*/
            // fwrite(cs_data, 44, 1, dstfile);
        }

        srcfile = fopen(a, "rb"); // reopening file to reset cursor position
        num_frames_to_process = num_frames_to_process < BUFFER_SIZE ? num_frames_to_process : BUFFER_SIZE;
        while ((fread(iec_in, sizeof(uint32_t), num_frames_to_process, srcfile)) > 0) {

            ret = extract_cs(iec_in,num_frames_to_process,srcfile,cs_data_left_ch,cs_data_right_ch,offset);
            if (ret < 0) {
                printf("Process error in extracting channel status\n");
                return ret;
            }

            /* number of frames are total subframes in block and for every 16 subframes 1 byte of left and right CS is extracted */
            offset += num_frames_to_process/16;

            ret = iec60958_decode(iec_in, num_frames_to_process, iec_out, &num_out_frames_to_write);
            if (ret != EXIT_SUCCESS) {
                printf("Process error\n");
                return ret;
            }
            fwrite(iec_out, sizeof(uint16_t), num_out_frames_to_write, dstfile);
        }

        ret = Compare_Left_Right_CS(cs_data_left_ch, cs_data_right_ch, offset);
        if (ret < 0)
            return ret;

            // printing channel status information
        ret = cs_logging(cs_data_left_ch);
        if (ret < 0) {
            printf("Process error in logging channel status\n");
            return ret;
        }

        printf("\nTotal number of channel status bytes extracted: %d\n", offset);
        CS_Comparator(cs_data_left_ch, offset);
    }

    for(int i=0;i<384;i++) {
        if(i%24 == 0 && i!=0)
            printf("\n");
        printf("0x%02x ", cs_data_left_ch[i]);
    }
    iec60958_deinit(iec958_handle, cs_data_left_ch, cs_data_right_ch);
    fclose(srcfile);
    fclose(dstfile);
}