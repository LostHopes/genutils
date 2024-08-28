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

void getByColumn(DIR *dir) {
    struct dirent *items;
    struct stat sb;

    while ((items = readdir(dir)) != NULL) {
        stat(items->d_name, &sb);
        items->d_name[0] != '.' ?
        printf(
            "\x1b[32;1m %d %ld B %s \n",
            sb.st_mode,
            sb.st_size,
            items->d_name
        )
        : 0;
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
    while ((items = readdir(dir)) != NULL) {
        printf(
            "\x1b[32;1m %s \n",
            items->d_name
        );
    }
}

void getRecursively() {
}

int listDir(void (*itemFunc)()) {
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

bool isDir(const char* path) {
    struct stat sb;
    bool status = stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);

    return status;
}

void sortItems() {

}

const char* getHelp() {
    const char* help = "lsg listing files program developed by \u00A9Arsen Melnychuk, 2024\n\
    \n-a\t shows hidden files \
    \n-l\t shows list column of files with detailed information \
    \n-R \t shows list of files inside the folders recursively";
    return help;
}

int main(int argc, char **argv) {
    // Prints items in dir if no arguments
    if (argc == 1) {
        listDir(getItems);
        exit(EXIT_SUCCESS);
    }

    char options;

    // FIXME: items will be printed 2 times if used double flags (e.g. -la)

    // argument l and R have optional arguments
    while((options = getopt(argc, argv, "alhR")) != -1) {

        // Lists current directory if no arguments provided
        switch (options) {

        case 'a':
            listDir(getHidden);
            break;

        case 'l':
            listDir(getByColumn);
            break;

        case 'h':
            printf("%s\n", getHelp());
            break;

        case 'R':
            break;

        case '?':
            exit(EXIT_FAILURE);
            break;

        default:
            break;
        }

    }

    exit(EXIT_SUCCESS);
}
