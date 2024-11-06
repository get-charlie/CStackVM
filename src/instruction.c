#include "instruction.h"
#include "error.h"

// Instructions
void push_inst(Machine* machine)
{
    set_stack_val(machine, 0, read_program_c(machine, 1));
    move_stack_p(machine, 1);
    step_program_c(machine, 2);
}

void pop_inst(Machine* machine)
{
    test_stack(machine, 1);
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void inc_inst(Machine* machine)
{
    test_stack(machine, 1);
    set_stack_val(machine, -1, get_stack_val(machine, -1) + 1);
    step_program_c(machine, 1);
}

void add_inst(Machine* machine)
{
    test_stack(machine, 2);
    set_stack_val(machine, -2, get_stack_val(machine, -2) + get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void sub_inst(Machine* machine)
{
    test_stack(machine, 2);
    set_stack_val(machine, -2, get_stack_val(machine, -2) - get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void mul_inst(Machine* machine)
{
    test_stack(machine, 2);
    set_stack_val(machine, -2, get_stack_val(machine, -2) * get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void div_inst(Machine* machine)
{
    test_stack(machine, 2);
    if(get_stack_val(machine, -1) == 0){
        zero_division();
    }
    set_stack_val(machine, -2, get_stack_val(machine, -2) / get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void mod_inst(Machine* machine)
{
    test_stack(machine, 2);
    if(get_stack_val(machine, -1) == 0){
        zero_division();
    }
    set_stack_val(machine, -2, get_stack_val(machine, -2) % get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void swap_inst(Machine* machine)
{   
    test_stack(machine, 2);
    int aux = get_stack_val(machine, -2);
    set_stack_val(machine, -2, get_stack_val(machine, -1));
    set_stack_val(machine, -1, aux);
    step_program_c(machine, 1);
}

void dup_inst(Machine* machine)
{   
    test_stack(machine, 1);
    set_stack_val(machine, 0, get_stack_val(machine, -1));
    move_stack_p(machine, 1);
    step_program_c(machine, 1);
}

void over_inst(Machine* machine)
{   
    test_stack(machine, 2);
    set_stack_val(machine, 0, get_stack_val(machine, -2));
    move_stack_p(machine, 1);
    step_program_c(machine, 1);
}

void load_inst(Machine* machine)
{
    int address = read_program_c(machine, 1);
    set_stack_val(machine, 0, read_memory(machine, address));
    move_stack_p(machine, 1);
    step_program_c(machine, 2);
}

void store_inst(Machine* machine)
{
    int address = read_program_c(machine, 1);
    test_stack(machine, 1);
    write_memory(machine, address, get_stack_val(machine, -1));
    move_stack_p(machine, -1);
    step_program_c(machine, 2);
}

void jump_inst(Machine* machine)
{
    int address = read_program_c(machine, 1);
    move_program_c(machine, address);
}

void print_inst(Machine* machine)
{
    if(machine->stack_p < 1){
        printf("EMPTY\n");
    }
    else{
        printf("%d\n", machine->stack[machine->stack_p - 1]);
    }
    step_program_c(machine, 1);
}

void sleep_inst(Machine* machine)
{
    int time = read_program_c(machine, 1);
    sleep(time);
    step_program_c(machine, 2);
}

void halt_inst(Machine* machine)
{
    (void)machine; // Remove unused warning
    exit(EXIT_SUCCESS);
}

