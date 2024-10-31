#include <dirent.h>

const char* usage();
const char* getVersion();
int listDir(void (*itemFunc)());
int listDirWithPath(void (*itemFunc)(DIR *dir), char* path);
void getItems(DIR* dir);
bool isDir(const char* path);
void getByColumn(DIR* dir);
void getHidden(DIR* dir);
void getRecursively(/*DIR* dir*/);
void sortItems();
void parseArgs(int argc, char** argv);