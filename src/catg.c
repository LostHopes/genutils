#include "catg.h"
#include <stdlib.h>
#include <getopt.h>
#include <sys/stat.h>

struct Flags{
    bool colorful;
    bool line_counter;
}flag;

int getMetadata(const char* filename) {
    struct stat sb;

    if (stat(filename, &sb) != -1) {
        fprintf(stdout, "%s has %ld bytes\n", filename, sb.st_size);
    }

    return EXIT_SUCCESS;
}

void getLineCounter() {
    int firstLine = 1;

    // Idea: read one line and append number before it in a loop
}

const char* readFile(const char* filename) {
    int fd = open(filename, O_RDONLY);

    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_read = read(fd, buf, BUFSIZ);

    if(close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
    return buf;
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
                long unsigned int i = optind;
                while (i <= sizeof(argv)) {
                    getMetadata(argv[i]);
                    i++;
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