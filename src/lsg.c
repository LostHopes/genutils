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

void getItemsByColumn(DIR *dir) {
    struct dirent *items;
    while ((items = readdir(dir)) != NULL) {
        items->d_name[0] != '.' ?
        printf(
            "\x1b[32;1m %s \n",
            items->d_name
        )
        : 0;
    }
}


void showHidden(DIR *dir) {
    struct dirent *items;
    while ((items = readdir(dir)) != NULL) {
        printf(
            "\x1b[32;1m %s \n",
            items->d_name
        );
    }
}

void showRecursively() {
}

int listItems(void (*itemFunc)()) {
    DIR *dir;
    char cwd_buf[BUFSIZ];

    getcwd(cwd_buf, BUFSIZ);

    if ((dir = opendir(cwd_buf)) == NULL) {
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }

    itemFunc(dir);

    closedir(dir);
    return EXIT_SUCCESS;
}

const char* getHelp() {
    const char* help = "lsg listing files program developed by \u00A9Arsen Melnychuk, 2024\n\
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

int main(int argc, char **argv) {
    // Prints items in dir if no arguments
    if (argc == 1) {
        listItems(getItems);
        exit(EXIT_SUCCESS);
    }

    char options;

    // FIXME: items will be printed 2 times if used double flags (e.g. -la)

    while((options = getopt(argc, argv, "alhR")) != -1) {

        // Lists current directory if no arguments provided
        switch (options) {

        case 'a':
            listItems(showHidden);
            break;

        case 'l':
            listItems(getItemsByColumn);
            break;

        case 'h':
            printf("%s\n", getHelp());
            break;

        case 'R':
            break;
        }
    }

    exit(EXIT_SUCCESS);
}
