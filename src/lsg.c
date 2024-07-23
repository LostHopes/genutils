#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "lsg.h"

int listItems()
{
    DIR *dir;
    struct dirent* items;

    char cwd_buf[BUFSIZ];
    getcwd(cwd_buf, BUFSIZ);

    if ((dir = opendir(cwd_buf)) == NULL)
    {
        perror("Can't open directory");
        exit(1);
    }

    while ((items = readdir(dir)) != NULL)
    {
        printf(
            "%s ",
            items->d_name
        );
    }
    printf("\n");
    
    closedir(dir);

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