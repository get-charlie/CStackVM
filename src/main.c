#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "machine.h"

void print_use(char* arg)
{
    fprintf(stderr, "Use: %s <program> <arguments...>\n", arg);
}

int main (int argc, char* argv[])
{
    if(argc < 2){
        print_use(argv[0]);
        exit(EXIT_FAILURE);
    }
        
    Machine machine = {0};
    load_prog(&machine, argv[1]);
    push_args(&machine, argc, argv);

    while(true){
        execute_next(&machine);
    }
    return 0;
}













