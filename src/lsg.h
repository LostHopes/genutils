#include <dirent.h>
#include <stdbool.h>

const char *getHelp();
int listItems();
void getItems(DIR *dir);
bool isDir(const char* path);
void showByColumn();
void showHidden();
void showRecursively();