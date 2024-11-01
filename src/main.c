#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "machine.h"

void print_use(char* arg)
{
    fprintf(stderr, "Use: %s <program> <arguments...>\n", arg);
}


int main (int argc, char** argv)
{
    if(argc < 2){
        print_use(argv[0]);
        exit(EXIT_FAILURE);
    }
        
    Machine machine = {0};
    load_prog(&machine, argv[1]); // TODO, load program arguments
    printf("Running %s...\n", argv[1]);

    while(true){
        execute_next(&machine);
        dump_machine(machine);
        sleep(1);
    }
    return 0;
}













