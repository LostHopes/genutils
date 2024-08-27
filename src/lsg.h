#include <dirent.h>
#include <stdbool.h>

const char *getHelp();
int listItems();
void getItems(DIR *dir);
bool isDir(const char* path);
void getItemsByColumn();
void showHidden();
void showRecursively();