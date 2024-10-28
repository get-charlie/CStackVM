#ifndef _INSTRUCTION_H
#define _INSTRUCTION_H
    
typedef enum { 
    PUSH, POP, SWAP, OVER, DUP, INC, ADD, SUB, MUL, DIV, MOD, LOAD, STORE, JUMP, PRINT, SLEEP, HALT, ILLEGAL,
} OpCode;

#endif
