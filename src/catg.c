#include "catg.h"
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>

struct Flags flag;

int getMetadata(const char* filename) {
    struct stat sb;

    if (stat(filename, &sb) != -1) {
        fprintf(stdout, "%s has %ld bytes\n", filename, sb.st_size);
    }

    return EXIT_SUCCESS;
}

void getLineCounter(const char* filename) {
    char* local_buf = readFile(filename);
    if (!local_buf) return;

    int line_number = 1;
    char* pointer = local_buf;
    char* line_start = pointer;

    while (*pointer) {
        if (*pointer == '\n') {
            *pointer = '\0';
            fprintf(stdout, "%d\t%s\n", line_number++, line_start);
            *pointer = '\n';
            line_start = pointer + 1;
        }
        pointer++;
    }
    if (line_start < pointer) {
        fprintf(stdout, "%d\t%s\n", line_number++, line_start);
    }

    free(local_buf);
}

char* readFile(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t filesize = st.st_size;
    char* buffer = malloc(filesize + 1);
    if (!buffer) {
        perror("malloc");
        close(fd);
        exit(EXIT_FAILURE);
    }

    size_t total_read = 0;
    while (total_read < filesize) {
        ssize_t bytes_read = read(fd, buffer + total_read, filesize - total_read);
        if (bytes_read <= 0) {
            perror("read");
            free(buffer);
            close(fd);
            exit(EXIT_FAILURE);
        }
        total_read += bytes_read;
    }
    buffer[filesize] = '\0';

    if (close(fd) == -1) {
        perror("close");
        free(buffer);
        exit(EXIT_FAILURE);
    }

    return buffer;
}

int main(int argc, char** argv) {

    if (argc < 2) {
        fprintf(stderr, "%s: requires the name of a file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    static struct option long_options[] = {
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"colorful", no_argument, 0, 'c'},
        {"line-counter", required_argument, 0, 'n'},
        {"metadata", required_argument, 0, 'm'},
    };

    const char* short_options = "vhcn:m:";
    int option_index = 0;
    int option = 0;

    while ((option = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (option) {
            case 'n':
                flag.line_counter = true;
                
                for (int i = 2; i < argc; i++) {
                    getLineCounter(argv[i]);
                }
                break;
            case 'c':
                flag.colorful = true;
                break;
            case 'm':
                for (int i = 1; i < argc; i++) {
                    getMetadata(argv[i]);
                }
                break;
            case 'v':
                exit(EXIT_SUCCESS);
                break;
            case 'h':
                exit(EXIT_SUCCESS);
                break;
        }
        exit(EXIT_SUCCESS);
    }

    for (int i = 1; i < argc; i++) {
        fprintf(stdout, "%s\n", readFile(argv[i]));
    }

    exit(EXIT_SUCCESS);
}