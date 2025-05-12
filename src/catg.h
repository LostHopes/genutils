#include <unistd.h>
#include <fcntl.h>

struct Flags{
    bool colorful;
    bool line_counter;
}flag;

int readFile(const char* filename);
int getMetadata(const char* filename);
void getLineCounter();
void printColorfulOutput();