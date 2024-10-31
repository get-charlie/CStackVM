#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

#include "machine.h"

void print_use(char* arg)
{
    fprintf(stderr, "Use: %s <program> <arguments...>\n", arg);
}

void load_arguments(int argc, char** argv) // TODO fix, broken because no push_op
{
    for(int i = 2; i < argc; i++){
        push_op(atoi(argv[i]));
    }
}

int main (int argc, char** argv)
{
    if(argc < 2){
        print_use(argv[0]);
        exit(EXIT_FAILURE);
    }
        
    load_prog(argv[1]);

    load_arguments(argc, argv);

    printf("Running %s...\n", argv[1]);

    while(true){
        execute_next();
        dump_machine();
        sleep(1);
    }
    return 0;
}













