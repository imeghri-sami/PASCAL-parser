#include "./headers/helpers.h"
#include "./headers/core.h"
#include <stdio.h>

int main(int argc, char** argv) {

    if(argc != 2) {
        fprintf(stderr, "Missing file name!\n");
        fprintf(stderr, "Usage : lexer <file_name>");
        return -1;
    }


    open_file(argv[1]);
    start_parser();
    return 0;
}
