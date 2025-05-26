#ifndef LSG_H
#define LSG_H

#include <dirent.h>
#include <stdbool.h>

const char* usage();
const char* getVersion();
int listDir(void (*itemFunc)(DIR *dir), const char* path);
void getItems(DIR* dir);
bool isDir(const char* path);
void getByColumn(DIR* dir);
void getHidden(DIR* dir);
void getRecursively(DIR *dir);
void sortItems();
void parseArgs(int argc, char** argv);

#endif