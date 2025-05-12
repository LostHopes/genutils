#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

struct Flags{
    bool colorful;
    bool line_counter;
}flag;
extern char buf[BUFSIZ];

const char* readFile(const char* filename);
int getMetadata(const char* filename);
void getLineCounter();
void printColorfulOutput();