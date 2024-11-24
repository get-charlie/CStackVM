#include "error.h"

void illegal_instruction()
{
    fprintf(stderr, "Error: Illegal instruction\n");
    exit(EXIT_FAILURE);
}

void zero_division()
{
    fprintf(stderr, "Error: Dividing by 0\n");
    exit(EXIT_FAILURE);
}

void memory_out_of_bounds()
{
    fprintf(stderr, "Error: Memory out of bounds\n");
    exit(EXIT_FAILURE);
}

void stack_overflow()
{
    fprintf(stderr, "Error: Stack Overflow\n");
    exit(EXIT_FAILURE);
}

void stack_underflow()
{
    fprintf(stderr, "Error: Stack Underflow\n");
    exit(EXIT_FAILURE);
}

void illegal_stack_access()
{
    fprintf(stderr, "Error: Illegal stack access\n");
    exit(EXIT_FAILURE);
}

void call_stack_overflow()
{
    fprintf(stderr, "Error: Call Stack Overflow\n");
    exit(EXIT_FAILURE);
}

void call_stack_underflow()
{
    fprintf(stderr, "Error: Call Stack Underflow\n");
    exit(EXIT_FAILURE);
}







