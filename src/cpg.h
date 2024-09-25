bool isDir(const char *path);
bool checkExists(const char *path);
size_t copyFile(const char* fileIn, const char* dir);
size_t copyDir(const char* pathIn, const char* pathOut);
const char* usage();
void printVerbose();
void parseArgs(int argc, char** argv);