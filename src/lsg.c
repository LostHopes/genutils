#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "lsg.h"

// TODO: add default sort method

void getItems(DIR *dir) {
    struct dirent *items;
    while ((items = readdir(dir)) != NULL) {
        items->d_name[0] != '.' ?
        printf(
            "\x1b[32;1m%s ",
            items->d_name
        ) 
        : 0;
    }
    printf("\n");
}

int listItems() {
    DIR *path;
    char cwd_buf[BUFSIZ];

    getcwd(cwd_buf, BUFSIZ);

    if ((path = opendir(cwd_buf)) == NULL) {
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }

    getItems(path);

    closedir(path);
    return EXIT_SUCCESS;
}

const char* getHelp() {
    const char* help = "lsg listing files program \u00A9Arsen Melnychuk 2024\n\
    \n-a\t shows hidden files \
    \n-l\t shows list column of files with detailed information \
    \n-R \t shows list of files inside the folders recursively";
    return help;
}

bool isDir(const char* path) {
    struct stat sb;
    bool status = stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);

    return status;
}

void showByColumn() {
}

void showHidden() {
}

void showRecursively() {
}

int main(int argc, char **argv) {
    // Prints items in dir if no arguments
    if (argc == 1) {
        listItems();
        exit(EXIT_SUCCESS);
    }

    char options = getopt(argc, argv, "alhR");

    // Lists current directory if no arguments provided
    switch (options) {

    case 'a':
        break;
    
    case 'l':
        break;
    
    case 'h':
        printf("%s\n", getHelp());
        break;

    case 'R':
        break;
    }

    exit(EXIT_SUCCESS);
}
