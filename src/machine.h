#ifndef _MACHINE_H
#define _MACHINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_LINE 128
#define DELIM " \n\t"

#define MAX_STK  16
#define MAX_MEM  256

#define MAX_WORD 32
#define MAX_TAGS 64


typedef struct {
    int     memory[MAX_MEM];
    size_t  program_c;
    int     stack[MAX_STK];
    size_t  stack_p;
} Machine;

// Program Loading
void load_prog      (Machine* machine, char* prog);
void push_args      (Machine* machine, int argc, char* argv[]);
// Machine control
void execute_next   (Machine* machine);
int  read_program_c (Machine* machine, size_t offset);
void step_program_c (Machine* machine, size_t offset);
void move_program_c (Machine* machine, size_t address);
int  read_memory    (Machine* machine, size_t address);
void write_memory   (Machine* machine, size_t address, int val);

void move_stack_p   (Machine* machine, int offset);
int  get_stack_val  (Machine* machine, int offset);
void set_stack_val  (Machine* machine, int offset, int val);

// Debugging
void debug_memory   (Machine* machine);
void debug_stack    (Machine* machine);

#endif







