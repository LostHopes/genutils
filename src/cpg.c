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

bool checkExists(const char *file) {
    if (access(file, F_OK) == 0) {
        return false;
    }
    return true;
}

void copyFile(const char* fileIn, const char* fileOut) {

    // TODO: write check if it's directory or file, then copy

    if(checkExists(fileIn)) {
        fprintf(stderr, "File %s doesn't exist\n", fileIn);
        exit(EXIT_FAILURE);
    }

    FILE *fp_read = fopen(fileIn, "rb");
    char buffer[BUFSIZ];

    if (!fp_read)
    {
        fprintf(stderr, "Couldn't open a file %s for reading\n", fileIn);
        exit(EXIT_FAILURE);
    }
    
    size_t bytesRead = fread(buffer, sizeof(char), BUFSIZ, fp_read);
    fclose(fp_read);


    FILE *fp_write = fopen(fileOut, "wb");

    if (!fp_write) {
        fprintf(stderr, "Couldn't open a file %s for writing\n", fileOut);
        exit(EXIT_FAILURE);
    }

    size_t bytesWritten = fwrite(buffer, sizeof(char), bytesRead, fp_write);

    if (bytesWritten != bytesRead) {
        fprintf(stderr, "Error copy of file %s\n", fileOut);
        fclose(fp_write);
        exit(EXIT_FAILURE);
    }

    fclose(fp_write);

    printf("Bytes copied %i\n", bytesWritten);
}

void copyDir(const char* pathIn, const char* pathOut) {

}

void printBytes(const char* item) {

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
    if (directory && verbose) {

    } else if (directory) {
        
    } else {

    }
    copyFile(argv[1], argv[2]);
}

int main(int argc, char** argv) {

    parseArgs(argc, argv);
    
    exit(EXIT_SUCCESS);
}