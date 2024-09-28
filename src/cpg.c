#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include "cpg.h"

bool isDir(const char *path) {
    struct stat sb;
    bool status = stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);

    return status;
}

bool checkExists(const char *file) {
    if (access(file, F_OK) == 0) {
        return false;
    }
    return true;
}

size_t copyFile(const char* fileIn, const char* dir) {

    if(isDir(fileIn)) {
        fprintf(stderr, "cpg: Can't copy a directory %s, use -r flag instead\n", fileIn);
        exit(EXIT_FAILURE);
    }

    if(checkExists(fileIn)) {
        fprintf(stderr, "File %s doesn't exist\n", fileIn);
        exit(EXIT_FAILURE);
    }

    FILE *fp_read = fopen(fileIn, "rb");
    char buffer[BUFSIZ];

    if (!fp_read) {
        fprintf(stderr, "cpg: Couldn't open a file %s for reading\n", fileIn);
        exit(EXIT_FAILURE);
    }
    
    size_t bytesRead = fread(buffer, sizeof(char), BUFSIZ, fp_read);
    fclose(fp_read);


    FILE *fp_write = fopen(dir, "wb");

    if (!fp_write) {
        fprintf(stderr, "cpg: Couldn't open a file %s for writing\n", dir);
        exit(EXIT_FAILURE);
    }

    size_t bytesWritten = fwrite(buffer, sizeof(char), bytesRead, fp_write);

    if (bytesWritten != bytesRead) {
        fprintf(stderr, "cpg: Error copy of file %s\n", dir);
        fclose(fp_write);
        exit(EXIT_FAILURE);
    }

    fclose(fp_write);

    return bytesWritten;
}

size_t copyDir(const char* pathIn, const char* pathOut) {

    if (!isDir(pathIn)) {
        copyFile(pathIn, pathOut);
    }
    

    size_t bytesWritten = 0;

    return bytesWritten;
}

const char* usage() {
    const char* help = "cpg: copy program developed by \u00A9Arsen Melnychuk, 2024";
    return help;
}

void parseArgs(int argc, char** argv) {

    struct Flag
    {
        bool directory;
        bool verbose;
    } flag;
    

    char options;
    while ((options = getopt(argc, argv, "rvh")) != -1)
    {
        switch (options)
        {
        
        case 'r':
            flag.directory = true;
            break;

        case 'v':
            flag.verbose = true;
            break;

        case 'h':
            printf("%s\n", usage());
            exit(EXIT_SUCCESS);
            break;
        
        default:
            fprintf(stderr, "%s\n", usage());
            exit(EXIT_FAILURE);
            break;
        }
    }
    if (flag.directory && flag.verbose) {

    } else if (flag.directory) {
        
    } else if (flag.verbose) {
        printf("Bytes written: %ld\n", copyFile(argv[2], argv[3]));
        exit(EXIT_SUCCESS);
    } else {

    }

    copyFile(argv[1], argv[2]);
}

int main(int argc, char** argv) {

    parseArgs(argc, argv);
    
    exit(EXIT_SUCCESS);
}