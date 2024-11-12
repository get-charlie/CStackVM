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
    #ifdef DEBUG
        printf("Running %s...\n", argv[1]);
        printf("Press ENTER to step the program\n");
    #endif
    while(true){
        #ifdef DEBUG
            debug_machine(&machine);
        #endif
        execute_next(&machine);
        #ifdef DEBUG
            getchar();
        #endif
    }
    return 0;
}













