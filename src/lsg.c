#include "lsg.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>


void getItems(DIR *dir)
{
  struct dirent *items;
  char hiddenObject = '.';
  struct stat sb;

  while ((items = readdir(dir)) != NULL)
  {
    if (items->d_name[0] != hiddenObject)
    {
      stat(items->d_name, &sb);
      if (S_ISDIR(sb.st_mode)) 
      {
        printf("\x1b[32;1m%s ", items->d_name);
      } else {
        printf("\x1b[0;31m%s ", items->d_name);
      }
    }
  }
  printf("\n");
}

void getByColumn(DIR *dir)
{
  struct dirent *items;
  struct stat sb;
  char hiddenObject = '.';

  while ((items = readdir(dir)) != NULL)
  {
    stat(items->d_name, &sb);
    if (items->d_name[0] != hiddenObject)
    {
      if (S_ISDIR(sb.st_mode)) {
        printf("\x1b[32;1m %d %ldB %s \n", sb.st_mode, sb.st_size,
             items->d_name);
      } else {
        printf("\x1b[0;31m %d %ldB %s \n", sb.st_mode, sb.st_size,
          items->d_name);
      }
    }
  }
}

void getHidden(DIR *dir)
{
  struct dirent *items;
  struct stat sb;

  while ((items = readdir(dir)) != NULL)
  {
    stat(items->d_name, &sb);
    if (S_ISDIR(sb.st_mode)) 
    {
      printf("\x1b[32;1m%s ", items->d_name);
    } else {
      printf("\x1b[0;31m%s ", items->d_name);
    }
  }
  printf("\n");
}

void getHiddenByColumn(DIR *dir)
{
  struct dirent *items;
  struct stat sb;

  while ((items = readdir(dir)) != NULL)
  {
    stat(items->d_name, &sb);

    if (S_ISDIR(sb.st_mode))
    {
      printf("\x1b[32;1m %d %ld B %s \n", sb.st_mode, sb.st_size, items->d_name);
    } else {
      printf("\x1b[0;31m %d %ld B %s \n", sb.st_mode, sb.st_size, items->d_name);
    }
  }
}

void getRecursively(DIR *dir)
{
    struct dirent *entry;

    int fd = dirfd(dir);
    if (fd == -1)
    {
        perror("Failed to get directory file descriptor");
        return;
    }

    int isSubDir = (fd != AT_FDCWD);

    while ((entry = readdir(dir)) != NULL)
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
        {
            continue;
        }

        struct stat entryStat;
        if (fstatat(fd, entry->d_name, &entryStat, AT_SYMLINK_NOFOLLOW) == -1)
        {
            perror("Error getting file stats");
            continue;
        }

        char fullPath[PATH_MAX];
        if (snprintf(fullPath, sizeof(fullPath), "%s", entry->d_name) >= (int)sizeof(fullPath))
        {
            fprintf(stderr, "Path too long: %s\n", entry->d_name);
            continue;
        }

        if (S_ISDIR(entryStat.st_mode))
        {
            DIR *subDir = opendir(fullPath);
            if (subDir)
            {
                printf("\x1b[32;1mDIR: %s\n", fullPath);
                getRecursively(subDir);
                closedir(subDir);
            }
            else
            {
                perror("Error opening subdirectory");
            }
        }
        else
        {
            if (isSubDir)
            {
                printf("\t\x1b[32;1mFile: %s\n", fullPath);
            }
            else
            {
                printf("\x1b[32;1mFile: %s\n", fullPath);
            }
        }
    }
}

int listDir(void (*itemFunc)(DIR *dir), const char *path)
{
  DIR *dir;

  if ((dir = opendir(path)) == NULL)
  {
    perror("Can't open directory");
    return EXIT_FAILURE;
  }

  itemFunc(dir);
  closedir(dir);

  return EXIT_SUCCESS;
}

bool isDir(const char *path)
{
  struct stat sb;
  return stat(path, &sb) == 0 && S_ISDIR(sb.st_mode);
}

typedef struct
{
  bool hidden;
  bool byColumn;
  bool recursive;
} Flag;

void parseArgs(int argc, char **argv)
{

  char options;
  Flag flag = {.byColumn = false, .hidden = false, .recursive = false};

  while ((options = getopt(argc, argv, "lahvR")) != -1)
  {
    switch (options)
    {
    case 'a':
      flag.hidden = true;
      break;
    case 'l':
      flag.byColumn = true;
      break;
    case 'R':
      flag.recursive = true;
      break;
    case 'h':
      fprintf(stdout, "%s\n", usage());
      exit(EXIT_SUCCESS);
      break;
    case 'v':
      fprintf(stdout, "%s\n", getVersion());
      exit(EXIT_SUCCESS);
      break;
    default:
      fprintf(stderr, "%s\n", usage());
      exit(EXIT_SUCCESS);
      break;
    }
  }

  const char *targetPath = (optind < argc) ? argv[optind] : ".";

  if (flag.hidden && flag.byColumn)
  {
    listDir(getHiddenByColumn, targetPath);
  }
  else if (flag.hidden)
  {
    listDir(getHidden, targetPath);
  }
  else if (flag.byColumn)
  {
    listDir(getByColumn, targetPath);
  }
  else if (flag.recursive)
  {
    listDir(getRecursively, targetPath);
  }
  else
  {
    listDir(getItems, targetPath);
  }
}

const char *usage()
{
  return "lsg listing files program developed by ©Arsen Melnychuk, 2024\n"
         "\n-a\t shows hidden files "
         "\n-l\t shows list column of files with detailed information "
         "\n-R \t shows list of files inside the folders recursively "
         "\n-v\t shows version "
         "\n-h\t shows help information";
}

const char *getVersion()
{
  return "lsg listing files program developed by ©Arsen Melnychuk, 2024"
         "\nLicense: MIT"
         "\nCurrent version: 0.1.0";
}

int main(int argc, char **argv)
{

  parseArgs(argc, argv);

  exit(EXIT_SUCCESS);
}