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

typedef enum { 
    PUSH, POP, SWAP, OVER, DUP, INC, ADD, SUB, MUL, DIV, MOD, LOAD, STORE, JUMP, PRINT, SLEEP, HALT, ILLEGAL,
} OpCode;

// Program Loading
void  load_prog     (char* program);
// Machine control
void execute_next   ();
// Stack manipulation
void push_op    ();
void pop_op     ();
void swap_op    ();
void over_op    ();
void dup_op     ();
// Arithmetic operarions
void inc_op     ();
void add_op     ();
void sub_op     ();
void mul_op     ();
void div_op     ();
void mod_op     ();
// Memory manipulation
void load_op    ();
void store_op   ();
// Control flow
void jump_op    ();
// Output operations
void print_op   ();
// Misc
void sleep_op   ();
void halt_op    ();
// Debugging
void dump_machine   ();

#endif







