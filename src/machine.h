#ifndef _MACHINE_H
#define _MACHINE_H

#define MAX_WORD 32
#define MAX_STK  16
#define MAX_MEM  64

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

typedef enum {
    NOMINAL, STK_OVERFLOW, STK_UNDERFLOW, ILLEGAL_INST, MEM_OUT_OF_BOUNDS, ZERO_DIVISION,
} State;

// Program Loading
void  load_prog     (char* program);
// Machine Control, not instructions
void  step_prog     (size_t step);
int   read_mem      (size_t offset);
void  print_state   (State state);
// Stack manipulation
State push_op       (int x);
State pop_op        ();
State swap_op       ();
State over_op       ();
State dup_op        ();
// Arithmetic operarions
State inc_op        ();
State add_op        ();
State sub_op        ();
State mul_op        ();
State div_op        ();
State mod_op        ();
// Memory manipulation
State load_op       (size_t address);
State store_op      (size_t address);
// Control flow
State jump_op       (size_t address);
// Output operations
State print_op      ();
// Misc
State sleep_op      (int time);

// Debugging
const char* state_to_string(State state);
void        machine_dump();

#endif







