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

// X-macro defining Operation Map
#define OPERATIONS \
    X_OP(PUSH  , "push"  , push_op  ) \
    X_OP(POP   , "pop"   , pop_op   ) \
    X_OP(SWAP  , "swap"  , swap_op  ) \
    X_OP(OVER  , "over"  , over_op  ) \
    X_OP(DUP   , "dup"   , dup_op   ) \
    X_OP(INC   , "inc"   , inc_op   ) \
    X_OP(ADD   , "add"   , add_op   ) \
    X_OP(SUB   , "sub"   , sub_op   ) \
    X_OP(MUL   , "mul"   , mul_op   ) \
    X_OP(DIV   , "div"   , div_op   ) \
    X_OP(MOD   , "mod"   , mod_op   ) \
    X_OP(LOAD  , "load"  , load_op  ) \
    X_OP(STORE , "store" , store_op ) \
    X_OP(JUMP  , "jump"  , jump_op  ) \
    X_OP(PRINT , "print" , print_op ) \
    X_OP(SLEEP , "sleep" , sleep_op ) \
    X_OP(HALT  , "halt"  , halt_op  )

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







