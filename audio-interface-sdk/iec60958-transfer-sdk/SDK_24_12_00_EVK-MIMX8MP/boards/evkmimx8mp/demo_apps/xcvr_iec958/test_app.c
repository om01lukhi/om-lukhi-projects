#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUF_SIZE 4096

int main(int argc, char *argv[]) {

    // Check if the user provided a file path as an argument
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file_path>\n", argv[0]);
        return EXIT_FAILURE;
    } 
    const char *dev_path = "/dev/sdma_dump";
    const char *out_path = argv[1];

    int char_dev = open(dev_path, O_RDONLY);
    if (char_dev < 0) {
        fprintf(stderr,"Failed to open /dev/sdma_dump");
        close(char_dev);
        return EXIT_FAILURE;
    }

    int out_file = open(out_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (out_file < 0) {
        fprintf(stderr, "Failed to open output file %s\n", out_path);
        close(out_file);
        return EXIT_FAILURE;
    }

    char *buffer = malloc(BUF_SIZE);
    if(!buffer) {
        fprintf(stderr, "Memory not allocated\n");
        return EXIT_FAILURE;
    }

    ssize_t rd_bytes = 0, wr_bytes = 0;
    while((rd_bytes = read(char_dev, buffer, sizeof(buffer))) > 0) {
        wr_bytes = write(out_file, buffer, rd_bytes);
        if(rd_bytes != wr_bytes) {
            fprintf(stderr, "Write error\n");
            free(buffer);
            close(char_dev);
            close(out_file);
            return EXIT_FAILURE;
        }
    }

    free(buffer);
    close(char_dev);
    close(out_file);
    return EXIT_SUCCESS;
}