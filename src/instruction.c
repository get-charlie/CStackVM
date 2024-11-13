#include "instruction.h"
#include "error.h"

// Instructions

// Stack manipulation
void push_inst(Machine* machine)
{
    set_stack_val(machine, 0, read_program_c(machine, 1));
    move_stack_p(machine, 1);
    step_program_c(machine, 2);
}

void pop_inst(Machine* machine)
{
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void swap_inst(Machine* machine)
{   
    int aux = get_stack_val(machine, -2);
    set_stack_val(machine, -2, get_stack_val(machine, -1));
    set_stack_val(machine, -1, aux);
    step_program_c(machine, 1);
}

void dup_inst(Machine* machine)
{   
    set_stack_val(machine, 0, get_stack_val(machine, -1));
    move_stack_p(machine, 1);
    step_program_c(machine, 1);
}

void over_inst(Machine* machine)
{   
    set_stack_val(machine, 0, get_stack_val(machine, -2));
    move_stack_p(machine, 1);
    step_program_c(machine, 1);
}

void size_inst(Machine* machine)
{   
    set_stack_val(machine, 0, machine->stack_p);
    move_stack_p(machine, 1);
    step_program_c(machine, 1);
}

// Arithmetic operarions
void inc_inst(Machine* machine)
{
    set_stack_val(machine, -1, get_stack_val(machine, -1) + 1);
    step_program_c(machine, 1);
}

void add_inst(Machine* machine)
{
    set_stack_val(machine, -2, get_stack_val(machine, -2) + get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void sub_inst(Machine* machine)
{
    set_stack_val(machine, -2, get_stack_val(machine, -2) - get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void mul_inst(Machine* machine)
{
    set_stack_val(machine, -2, get_stack_val(machine, -2) * get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void div_inst(Machine* machine)
{
    if(get_stack_val(machine, -1) == 0){
        zero_division();
    }
    set_stack_val(machine, -2, get_stack_val(machine, -2) / get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void mod_inst(Machine* machine)
{
    if(get_stack_val(machine, -1) == 0){
        zero_division();
    }
    set_stack_val(machine, -2, get_stack_val(machine, -2) % get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

// Binary operations
void not_inst(Machine* machine)
{
    set_stack_val(machine, -1, ~get_stack_val(machine, -1));
    step_program_c(machine, 1);
}

void and_inst(Machine* machine)
{
    set_stack_val(machine, -2, get_stack_val(machine, -2) & get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void or_inst(Machine* machine)
{
    set_stack_val(machine, -2, get_stack_val(machine, -2) | get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void xor_inst(Machine* machine)
{
    set_stack_val(machine, -2, get_stack_val(machine, -2) ^ get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void shl_inst(Machine* machine)
{
    set_stack_val(machine, -2, (unsigned)get_stack_val(machine, -2) << (unsigned)get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void shr_inst(Machine* machine)
{
    set_stack_val(machine, -2, (unsigned)get_stack_val(machine, -2) >> (unsigned)get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

// Memory manipulation
void ldi_inst(Machine* machine)
{
    int address = read_program_c(machine, 1);
    set_stack_val(machine, 0, read_memory(machine, address));
    move_stack_p(machine, 1);
    step_program_c(machine, 2);
}

void lds_inst(Machine* machine)
{
    int address = get_stack_val(machine, -1);
    set_stack_val(machine, -1, read_memory(machine, address));
    step_program_c(machine, 1);
}

void sti_inst(Machine* machine)
{
    int address = read_program_c(machine, 1);
    write_memory(machine, address, get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 2);
}

void sts_inst(Machine* machine)
{
    int address = get_stack_val(machine, -1);
    write_memory(machine, address, get_stack_val(machine, -2));
    move_stack_p(machine, -2);
    step_program_c(machine, 1);
}

// Control flow
void cmp_inst(Machine* machine)
{
    int a = get_stack_val(machine, -1);
    int b = get_stack_val(machine, -2);
    set_stack_val(machine, -2, a == b ? -1 : 0);
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void neg_inst(Machine* machine)
{
    int a = get_stack_val(machine, -1);
    set_stack_val(machine, -1, a < 0 ? -1 : 0);
}

void jmp_inst(Machine* machine)
{
    int address = read_program_c(machine, 1);
    move_program_c(machine, address);
}

void jnz_inst(Machine* machine)
{
    int top = get_stack_val(machine, -1);
    move_stack_p(machine, -1);
    if(top != 0){
        jmp_inst(machine);
    }
    else{
        step_program_c(machine, 2);
    }
}

// Misc
void print_inst(Machine* machine)
{
    #ifdef DEBUG
        printf("OUT: ");
    #endif
    if(machine->stack_p < 1){
        printf("EMPTY");
    }
    else{
        printf("%-8d ", machine->stack[machine->stack_p - 1]);
    }
    #ifndef DEBUG
        printf("\n");
    #endif
    step_program_c(machine, 1);
}

void nop_inst(Machine* machine)
{
    step_program_c(machine, 1);
}

void halt_inst(Machine* machine)
{
    (void)machine; // Remove unused warning
    #ifdef DEBUG
        printf("\n");
    #endif
    exit(EXIT_SUCCESS);
}

// User defined instructions...
