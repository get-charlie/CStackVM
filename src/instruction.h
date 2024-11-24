#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "machine.h"

// To add a new instruction add an enum value, an string naming the instruction and a funcion name to the X-macro
// The function header must be declared below with all the other headers. The definition must be in instruction.c
// To manipulate the machine it is encouraged to use the functions declared in machine.h

// X-macro defining Instruction Map
#define INSTRUCTIONS \
    X_INST(PUSH  , "push"  , push_inst  ) \
    X_INST(POP   , "pop"   , pop_inst   ) \
    X_INST(SWAP  , "swap"  , swap_inst  ) \
    X_INST(OVER  , "over"  , over_inst  ) \
    X_INST(DUP   , "dup"   , dup_inst   ) \
    X_INST(SIZE  , "size"  , size_inst  ) \
    X_INST(INC   , "inc"   , inc_inst   ) \
    X_INST(ADD   , "add"   , add_inst   ) \
    X_INST(SUB   , "sub"   , sub_inst   ) \
    X_INST(MUL   , "mul"   , mul_inst   ) \
    X_INST(DIV   , "div"   , div_inst   ) \
    X_INST(MOD   , "mod"   , mod_inst   ) \
    X_INST(NOT   , "not"   , not_inst   ) \
    X_INST(AND   , "and"   , and_inst   ) \
    X_INST(OR    , "or"    , or_inst    ) \
    X_INST(XOR   , "xor"   , xor_inst   ) \
    X_INST(SHL   , "shl"   , shl_inst   ) \
    X_INST(SHR   , "shr"   , shr_inst   ) \
    X_INST(LDI   , "ldi"   , ldi_inst   ) \
    X_INST(LDS   , "lds"   , lds_inst   ) \
    X_INST(STI   , "sti"   , sti_inst   ) \
    X_INST(STS   , "sts"   , sts_inst   ) \
    X_INST(CMP   , "cmp"   , cmp_inst   ) \
    X_INST(NEG   , "neg"   , neg_inst   ) \
    X_INST(JMP   , "jmp"   , jmp_inst   ) \
    X_INST(JNZ   , "jnz"   , jnz_inst   ) \
    X_INST(CALL  , "call"  , call_inst  ) \
    X_INST(RET   , "ret"   , ret_inst   ) \
    X_INST(PRINT , "print" , print_inst ) \
    X_INST(NOP   , "nop"   , nop_inst   ) \
    X_INST(HALT  , "halt"  , halt_inst  ) 

// Stack manipulation
// Pushes an imediate value into the stack
void push_inst  (Machine* machine); 
// Pops the top of the stack
void pop_inst   (Machine* machine); 
// Swaps the top two values 
void swap_inst  (Machine* machine); 
// Pushes the value second from the top
void over_inst  (Machine* machine); 
// Dups the top of the stack
void dup_inst   (Machine* machine); 
// Pushes the size of the stack
void size_inst  (Machine* machine); 

// Arithmetic operarions
// Increases the top by 1
void inc_inst   (Machine* machine); 
// Pops the top two values, adds them and pushes the result
void add_inst   (Machine* machine); 
// Pops the top two values, substracts them and pushes the result
void sub_inst   (Machine* machine); 
// Pops the top two values, multiplies them and pushes the result
void mul_inst   (Machine* machine); 
// Pops the top two values, divides them and pushes the result
void div_inst   (Machine* machine); 
// Pops the top two values, calculates the mod and pushes the result
void mod_inst   (Machine* machine); 

// Binary operations
// Applies the not operation to the top value
void not_inst   (Machine* machine); 
// Applies the and operation to the top two values
void and_inst   (Machine* machine); 
// Applies the and operation to the top two values
void or_inst    (Machine* machine); 
// Applies the or operation to the top two values
void xor_inst   (Machine* machine); 
// Shifts left the bits of the second value of the stack by the top value of the stack
void shl_inst   (Machine* machine); 
// Shifts right the bits of the second value of the stack by the top value of the stack
void shr_inst   (Machine* machine); 

// Memory manipulation
// Pushes the value from the memory address indicated by an imediate value
void ldi_inst   (Machine* machine); 
// Pushes the value from the memory address indicated by the top value of the stack. The top value is poped
void lds_inst   (Machine* machine); 
// Pops the top and stores it on the memory address indicated by an imediate value
void sti_inst   (Machine* machine); 
// Pops the value second from the top and stores it on the memory address indicated by the top of the stack. The memory address is also poped
void sts_inst   (Machine* machine); 

// Control flow
// Pops the top two stack values. If they are equal -1 is pushed, otherwise 0 is pushed
void cmp_inst   (Machine* machine); 
// Pops the top. If it is negative -1 is pushed. Otherwise 0 is pushed.
void neg_inst   (Machine* machine); 
// Jumps to the memory address indicated by an inmediate value
void jmp_inst   (Machine* machine); 
// Pops the top and jumps if it's value is equal to 0. If the value is 0 the program continues
void jnz_inst   (Machine* machine); 
// Calls a tag and stores the current program counter into the call stack
void call_inst  (Machine* machine);
// Returns to the next instruction from the address pointed to by the top of the call stack
void ret_inst   (Machine* machine);

// Misc
// Prints the top of the stack without poping it. If the stack is empty 'EMPTY' is printed
void print_inst (Machine* machine); 
// Does nothing
void nop_inst   (Machine* machine); 
// Exits
void halt_inst  (Machine* machine); 

// User defined instructions...

#endif
