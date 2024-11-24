#ifndef _ERROR_H
#define _ERROR_H

#include <stdio.h>
#include <stdlib.h>

// Error handling
// Print an error message and exit
void illegal_instruction();
void zero_division();
void memory_out_of_bounds();
void stack_overflow();
void stack_underflow();
void illegal_stack_access();
void call_stack_overflow();
void call_stack_underflow();

#endif

