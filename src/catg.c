#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include <sys/stat.h>
#include "catg.h"

struct Flags{
    bool colorful;
    bool line_counter;
}flag;

int getMetadata(const char* filename) {
    struct stat sb;

    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "File %s has %ld bytes\n", filename, sb.st_size);

    return EXIT_SUCCESS;
}

int readFile(const char* filename) {
    int fd = open(filename, O_RDONLY);
    char buf[BUFSIZ];

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = read(fd, buf, BUFSIZ);

    if(close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    fprintf(stdout, "%s\n", buf);
    return EXIT_SUCCESS;
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
        {"line-counter", no_argument, 0, 'n'},
        {"metadata", required_argument, 0, 'm'},
    };

    const char* short_options = "vhcnm:";
    int option_index = 0;
    int option = 0;

    while ((option = getopt_long(argc, argv, short_options, long_options, &option_index)) != -1) {
        switch (option) {
            case 'n':
                flag.line_counter = true;
                break;
            case 'c':
                flag.colorful = true;
                break;
            case 'm':
                getMetadata(optarg);
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
        readFile(argv[i]);
    }

    exit(EXIT_SUCCESS);
}