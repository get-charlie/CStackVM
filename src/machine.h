#ifndef _MACHINE_H
#define _MACHINE_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

// Lexer stuff
#define DELIM           " \n\t" // Delimiters used by the tokenizer
#define MAX_LINE        128     // Maximum length for the line read by the lexer
// Jumps
#define MAX_WORD        32      // Maximum string length for a named jump
#define MAX_TAGS        64      // Maximum numer of named jumps
// Machine
#define MAX_STK         16      // Maximum stack size
#define MAX_MEM         256     // Maximum memory size
#define MAX_CALL_STK    16      // Maximim call stack 

typedef struct { // The machine in question
    // Program memory containing data and instructions
    int     memory[MAX_MEM];
    size_t  program_c;
    // Stack containing data
    int     stack[MAX_STK];
    size_t  stack_p;
    // Call stack containing return instrcutions
    size_t  call_stack[MAX_CALL_STK];
    size_t  call_stack_p;
} Machine;

// Program Loading
// Loads the program into memory
void load_prog          (Machine* machine, char* prog); 
// Pushes cli arguments into the stack
void push_args          (Machine* machine, int argc, char* argv[]); 
// Machine control
// Executes next instruction
void execute_next       (Machine* machine);
// Returns the value pointed at by the program counter plus an offset
int  read_program_c     (Machine* machine, size_t offset); 
// Steps the program counter by a set ammount
void step_program_c     (Machine* machine, size_t offset); 
// Moves the program counter to a memory location
void move_program_c     (Machine* machine, size_t addr); 
// Reads an arbitrary memory location
int  read_memory        (Machine* machine, size_t addr); 
// Writes to a memory location
void write_memory       (Machine* machine, size_t addr, int val); 
// Moves the stack pointer by a set amount
void move_stack_p       (Machine* machine, int offset);
// Returns the value pointed by the stack pointer plus an offset. The offset must be negative
int  get_stack_val      (Machine* machine, int offset); 
// Sets a stack value in reference to the stack pointer
void set_stack_val      (Machine* machine, int offset, int val); 
// Pushes an address into the call stack
void push_call_stack    (Machine* machine, size_t addr);
// Pops an address from the call stack and returns it
int  pop_call_stack     (Machine* machine);

// Debugging
// Prints the value of the program counter and the current instruction
void debug_memory       (Machine* machine); 
// Prints the state of the stack
void debug_stack        (Machine* machine); 

#endif

