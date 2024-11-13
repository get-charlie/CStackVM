#ifndef _MACHINE_H
#define _MACHINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

// Parser stuff
#define DELIM " \n\t"   // Delimiters used by the tokenizer
#define MAX_LINE 128    // Maximum length for the line read by the parser 
// Jumps
#define MAX_WORD 32     // Maximum string length for a named jump
#define MAX_TAGS 64     // Maximum numer of named jumps
// Machine
#define MAX_STK  16     // Maximum stack size
#define MAX_MEM  256    // Maximum memory size

typedef struct { // The machine in question
    int     memory[MAX_MEM];
    size_t  program_c;
    int     stack[MAX_STK];
    size_t  stack_p;
} Machine;

// Program Loading
void load_prog      (Machine* machine, char* prog); // Loads the program into memory
void push_args      (Machine* machine, int argc, char* argv[]); // Pushes cli arguments into the stack
// Machine control
void execute_next   (Machine* machine); // Executes next instruction

int  read_program_c (Machine* machine, size_t offset); // Returns the value pointed at by the program counter plus an offset
void step_program_c (Machine* machine, size_t offset); // Steps the program counter by a set ammount
void move_program_c (Machine* machine, size_t address); // Moves the program counter to a memory location
int  read_memory    (Machine* machine, size_t address); // Reads an arbitrary memory location
void write_memory   (Machine* machine, size_t address, int val); // Writes to a memory location

void move_stack_p   (Machine* machine, int offset); // Moves the stack pointer by a set amount
int  get_stack_val  (Machine* machine, int offset); // Returns the value pointed by the stack pointer plus an offset. The offset must be negative
void set_stack_val  (Machine* machine, int offset, int val); // Sets a stack value in reference to the stack pointer

// Debugging
void debug_memory   (Machine* machine); // Prints the value of the program counter and the current instruction
void debug_stack    (Machine* machine); // Prints the state of the stack

#endif

