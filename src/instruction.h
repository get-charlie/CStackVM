#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "machine.h"

// X-macro defining Instruction Map
#define INSTRUCTIONS \
    X_INST(PUSH  , "push"  , push_inst  ) \
    X_INST(POP   , "pop"   , pop_inst   ) \
    X_INST(SWAP  , "swap"  , swap_inst  ) \
    X_INST(OVER  , "over"  , over_inst  ) \
    X_INST(DUP   , "dup"   , dup_inst   ) \
    X_INST(INC   , "inc"   , inc_inst   ) \
    X_INST(ADD   , "add"   , add_inst   ) \
    X_INST(SUB   , "sub"   , sub_inst   ) \
    X_INST(MUL   , "mul"   , mul_inst   ) \
    X_INST(DIV   , "div"   , div_inst   ) \
    X_INST(MOD   , "mod"   , mod_inst   ) \
    X_INST(NOT   , "not"   , not_inst   ) \
    X_INST(AND   , "and"   , and_inst   ) \
    X_INST(OR    , "or"   ,  or_inst    ) \
    X_INST(XOR   , "xor"   , xor_inst   ) \
    X_INST(LOAD  , "load"  , load_inst  ) \
    X_INST(STORE , "store" , store_inst ) \
    X_INST(JUMP  , "jump"  , jump_inst  ) \
    X_INST(CMP   , "cmp"   , cmp_inst   ) \
    X_INST(JNZ   , "jnz"   , jnz_inst   ) \
    X_INST(SIZE  , "size"  , size_inst  ) \
    X_INST(PRINT , "print" , print_inst ) \
    X_INST(SLEEP , "sleep" , sleep_inst ) \
    X_INST(NOP   , "nop"   , nop_inst   ) \
    X_INST(HALT  , "halt"  , halt_inst  ) 

// Stack manipulation
void push_inst          (Machine* machine);
void pop_inst           (Machine* machine);
void swap_inst          (Machine* machine);
void over_inst          (Machine* machine);
void dup_inst           (Machine* machine);
void size_inst          (Machine* machine);
// Arithmetic operarions
void inc_inst           (Machine* machine);
void add_inst           (Machine* machine);
void sub_inst           (Machine* machine);
void mul_inst           (Machine* machine);
void div_inst           (Machine* machine);
void mod_inst           (Machine* machine);
// Binary operations
void not_inst           (Machine* machine);
void and_inst           (Machine* machine);
void or_inst            (Machine* machine);
void xor_inst           (Machine* machine);
// Memory manipulation
void load_inst          (Machine* machine);
void store_inst         (Machine* machine);
// Control flow
void jump_inst          (Machine* machine);
void cmp_inst           (Machine* machine);
void jnz_inst           (Machine* machine);
// Output operations
void print_inst         (Machine* machine);
// Misc
void sleep_inst         (Machine* machine);
void halt_inst          (Machine* machine);
void nop_inst           (Machine* machine);

#endif
