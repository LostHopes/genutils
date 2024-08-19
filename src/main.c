#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "lsg.h"

int main(int argc, char **argv)
{
    char option = getopt(argc, argv, "alh");

    // Lists an current directory if no arguments provided
    switch (option)
    {
    case 'a':
        break;
    
    case 'l':
        break;
    
    case 'h':
        printf("%s\n", getHelp());
        break;
    
    case -1:
        listItems();
        break;
    }

    exit(EXIT_SUCCESS);
}