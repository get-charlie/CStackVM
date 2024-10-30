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
        int op = read_program_c(0);
        switch(op){
            case PUSH:  push_op();  break;
            case POP:   pop_op();   break;
            case SWAP:  swap_op();  break;
            case OVER:  over_op();  break;
            case DUP:   dup_op();   break;
            case INC:   inc_op();   break;
            case ADD:   add_op();   break;
            case SUB:   sub_op();   break;
            case MUL:   mul_op();   break;
            case DIV:   div_op();   break;
            case MOD:   mod_op();   break;
            case LOAD:  load_op();  break;
            case STORE: store_op(); break;
            case JUMP:  jump_op();  break;
            case PRINT: print_op(); break;
            case SLEEP: sleep_op(); break;
            case HALT:  return 0;
            default:
                fprintf(stderr, "Illegal inst\n");
                exit(EXIT_FAILURE);
        }
        dump_machine();
        sleep(1);
    }
    return 0;
}













