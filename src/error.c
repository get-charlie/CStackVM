#include "error.h"

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











