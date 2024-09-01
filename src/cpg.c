#include "cpg.h"

int main(int argc, char **argv) {

    char options;

    while ((options = getopt(argc, argv, "r:v")) != -1)
    {
        switch (options)
        {
        
        case 'r':
            break;

        case 'v':

            break;

        case 'h':
            break;
        }
    }
    
    exit(EXIT_SUCCESS);
}