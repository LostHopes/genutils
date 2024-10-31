#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include "lsg.h"

// TODO: add default sort method

void getItems(DIR *dir) {
    struct dirent *items;
    char hiddenObject = '.';

    while ((items = readdir(dir)) != NULL) {
        if (items->d_name[0] != hiddenObject) {
            printf(
                "\x1b[32;1m%s ",
                items->d_name
            );
        }
    }
    printf("\n");
}

void getByColumn(DIR *dir) {
    struct dirent *items;
    struct stat sb;
    char hiddenObject = '.';

    while ((items = readdir(dir)) != NULL) {
        stat(items->d_name, &sb);
        if (items->d_name[0] != hiddenObject) {
            printf(
                "\x1b[32;1m %d %ld B %s \n",
                sb.st_mode,
                sb.st_size,
                items->d_name
            );
        }
    }
}


void getHidden(DIR *dir) {
    struct dirent *items;
    while ((items = readdir(dir)) != NULL) {
        printf(
            "\x1b[32;1m %s ",
            items->d_name
        );
    }
    printf("\n");
}

void getHiddenByColumn(DIR *dir) {
    struct dirent *items;
    struct stat sb;

    while ((items = readdir(dir)) != NULL) {
        stat(items->d_name, &sb);
        printf(
            "\x1b[32;1m %d %ld B %s \n",
            sb.st_mode,
            sb.st_size,
            items->d_name
        );
    }
}

void getRecursively(/*DIR *dir*/) {

}

int listDir(void (*itemFunc)(DIR *dir)) {
    DIR* dir;
    char cwd_buf[BUFSIZ];

    getcwd(cwd_buf, BUFSIZ);

    if ((dir = opendir(cwd_buf)) == NULL) {
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }

    itemFunc(dir);

    closedir(dir);
    exit(EXIT_SUCCESS);
}

int listDirWithPath(void (*itemFunc)(DIR *dir), char* path) {
    DIR* dir;
    
    if ((dir = opendir(path)) == NULL) {
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }

    itemFunc(dir);
    closedir(dir);

    return EXIT_SUCCESS;
}

bool isDir(const char* path) {
    struct stat sb;
    bool status = stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);

    return status;
}

void sortItems(char* items) {

    size_t len = strlen(items);

    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len; j++) {
            if (items[i] > items[j]) {

            }
        }
    }
    
}

typedef struct {
        bool hidden;
        bool byColumn;
        bool recursive;
} Flag;

void parseArgs(int argc, char** argv) {

    char options;
    Flag flag;

    while((options = getopt(argc, argv, "lahvR")) != -1) {
        switch (options) {

        case 'a':
            flag.hidden = true;
            break;

        case 'l':
            flag.byColumn = true;
            break;

        case 'R':
            flag.recursive = true;
            break;

        case 'h':
            printf("%s\n", usage());
            break;

        case 'v':
            printf("%s\n", getVersion());
            break;

        default:
            fprintf(stderr, "%s\n", usage());
        }
    }

    if (flag.hidden && flag.byColumn) {
        listDir(getHiddenByColumn);
    } else if (flag.hidden) {
        listDir(getHidden);
    } else if (flag.byColumn) {
        listDir(getByColumn);
    } else if (flag.recursive) {
    }
}

const char* usage() {
    const char* help = "lsg listing files program developed by \u00A9Arsen Melnychuk, 2024\n \
    \n-a\t shows hidden files \
    \n-l\t shows list column of files with detailed information \
    \n-R \t shows list of files inside the folders recursively \
    \n-v\t shows version \
    \n-h\t shows help information";
    return help;
}

const char* getVersion() {
    const char* version = "lsg listing files program developed by \u00A9Arsen Melnychuk, 2024\
    \nLicense: MIT\
    \nCurrent version: 0.1";
    return version;
}

int main(int argc, char **argv) {
    // Prints items in dir if no arguments
    if (argc == 1) {
        listDir(getItems);
        exit(EXIT_SUCCESS);
    }
    
    parseArgs(argc, argv);

    listDirWithPath(getItems, argv[1]);

    // TODO: add feature to select path to list

    exit(EXIT_SUCCESS);
}
