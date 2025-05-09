#include <stdlib.h>
#include <getopt.h>
#include <stdio.h>
#include "catg.h"

int main(int argc, char** argv) {

    if (argc < 2) {
        fprintf(stderr, "%s: requires the name of a file\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    static struct option long_options[] = {
        {"version", 0, 0, 'v'},
    };
    const char* short_options = "v";
    int option_index = 0;

    exit(EXIT_SUCCESS);
}