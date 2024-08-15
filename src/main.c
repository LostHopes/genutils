#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>

#include "lsg.h"

int main(int argc, char **argv)
{
    int option = getopt(argc, argv, "--help");

    // Lists an current directory if no arguments provided
    if(option == -1){
        listItems();
    }

    exit(EXIT_SUCCESS);
}