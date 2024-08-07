#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "lsg.h"

// TODO: add default sort method

void printItems(DIR *dir)
{
    struct dirent* items;
    while ((items = readdir(dir)) != NULL)
    {
        items->d_name[0] != '.' ? printf("\x1b[32;1m%s ", items->d_name) : 0;
    }
    printf("\n");
}

int listItems()
{
    DIR *dir;

    char cwd_buf[BUFSIZ];
    getcwd(cwd_buf, BUFSIZ);

    if ((dir = opendir(cwd_buf)) == NULL)
    {
        perror("Can't open directory");
        exit(EXIT_FAILURE);
    }

    printItems(dir);
    
    closedir(dir);
    exit(EXIT_SUCCESS);
}

void showByColumn()
{
}

void showHidden()
{
}

void showRecursively()
{
}