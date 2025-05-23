#include <stdio.h>
#include <stdbool.h>

struct Flags{
    bool colorful;
    bool line_counter;
};
extern struct Flags flag;
extern char buf[BUFSIZ];

char* readFile(const char* filename);
int getMetadata(const char* filename);
void getLineCounter(const char* filename);
void printColorfulOutput();