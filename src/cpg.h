bool isDir(const char *path);
bool checkExists(const char *path);
void copyFile(const char* fileIn, const char* fileOut);
void copyDir(const char* pathIn, const char* pathOut);
const char* getHelp();
void printVerbose();
void printBytes(const char* item);
void parseArgs(int argc, char** argv);