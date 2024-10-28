#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "machine.h"
#include "instruction.h"

void print_use(char* arg)
{
    fprintf(stderr, "Use: %s <program> <arguments...>\n", arg);
}

void load_arguments(int argc, char** argv)
{
    for(int i = 2; i < argc; i++){ // TODO check if arguments are ints
        push_op(atoi(argv[i]));
    }
}

int main (int argc, char** argv)
{
    State state = NOMINAL;
    
    if(argc < 2){
        print_use(argv[0]);
        exit(EXIT_FAILURE);
    }
        
    load_prog(argv[1]);

    load_arguments(argc, argv);

    while(state == NOMINAL){
        int op = read_mem(0);
        switch(op){
            case PUSH:  state = push_op(read_mem(1));  step_prog(2);    break;
            case POP:   state = pop_op();              step_prog(1);    break;
            case SWAP:  state = swap_op();             step_prog(1);    break;
            case OVER:  state = over_op();             step_prog(1);    break;
            case DUP:   state = dup_op();              step_prog(1);    break;
            case INC:   state = inc_op();              step_prog(1);    break;
            case ADD:   state = add_op();              step_prog(1);    break;
            case SUB:   state = sub_op();              step_prog(1);    break;
            case MUL:   state = mul_op();              step_prog(1);    break;
            case DIV:   state = div_op();              step_prog(1);    break;
            case MOD:   state = mod_op();              step_prog(1);    break;
            case LOAD:  state = load_op(read_mem(1));  step_prog(2);    break;
            case STORE: state = store_op(read_mem(1)); step_prog(2);    break;
            case JUMP:  state = jump_op(read_mem(1));                   break;
            case PRINT: state = print_op(read_mem(1)); step_prog(1);    break;
            case SLEEP: state = sleep_op(read_mem(1)); step_prog(2);    break;
            case HALT:  return 0;
            default:    state = ILLEGAL_INST;
        }
    }
    if(state != NOMINAL){
        fprintf(stderr, "Error %s\n", state_to_string(state));
        machine_dump();
    }
    return 0;
}













