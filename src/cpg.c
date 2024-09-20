#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "cpg.h"

bool isDir(const char *path) {
    return path;
}

void copyItem() {

}

void printBytes() {

}

const char* getHelp() {
    const char* help = "";
    return help;   
}

void parseArgs(int argc, char** argv) {

    if(argc > 3) {
        fprintf(stderr, "Provided too many arguments \n");
        exit(EXIT_FAILURE);
    }

    char options;
    bool verbose, directory;
    while ((options = getopt(argc, argv, "rvh")) != -1)
    {
        switch (options)
        {
        
        case 'r':
            directory = true;
            break;

        case 'v':
            verbose = true;
            break;

        case 'h':
            printf("%s\n", getHelp());
            break;
        
        default:
            fprintf(stderr, "%s\n", getHelp());
            break;
        }
    }
}

int main(int argc, char** argv) {

    parseArgs(argc, argv);
    
    exit(EXIT_SUCCESS);
}