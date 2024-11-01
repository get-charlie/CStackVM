#ifndef _MACHINE_H
#define _MACHINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_WORD 32
#define MAX_STK  16
#define MAX_MEM  64

typedef struct {
    int     memory[MAX_MEM];
    size_t  program_c;
    int     stack[MAX_STK];
    size_t  stack_p;
} Machine;

// Program Loading
void load_prog      (Machine* machine, char* program);
// Machine control
void execute_next   (Machine* machine);
int  read_program_c (Machine machine, size_t offset);
void step_program_c (Machine* machine, size_t offset);
void move_stack_p   (Machine* machine, int offset);
void test_stack     (Machine machine, int elements);
// Debugging
void dump_machine   (Machine machine);
#endif







