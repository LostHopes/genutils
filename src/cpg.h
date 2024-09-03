#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>

bool isDir(const char *path);
void cpDir();
void cpVerbose();
void cpPrintBytes();