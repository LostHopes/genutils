#include "cpg.h"

int main(int argc, char **argv) {

    char options;

    while ((options = getopt(argc, argv, "v")) != -1)
    {
        switch (options)
        {
        case 'v':

            break;
        }
    }
    
    exit(EXIT_SUCCESS);
}