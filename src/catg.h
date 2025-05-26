#ifndef CATG_H
#define CATG_H

#include <stdio.h>
#include <stdbool.h>

struct Flags{
    bool colorful;
    bool line_counter;
};
extern struct Flags flag;

char* readFile(const char* filename);
int getMetadata(const char* filename);
void getLineCounter(const char* filename);

#endif