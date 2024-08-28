#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

const char *getHelp();
int listDir(void (*itemFunc)());
void getItems(DIR *dir);
bool isDir(const char* path);
void getByColumn();
void getHidden();
void getRecursively();
void sortItems();