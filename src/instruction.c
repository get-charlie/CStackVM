#include "instruction.h"
#include "error.h"

// Instructions
void push_inst(Machine* machine)
{
    machine->stack[machine->stack_p] = read_program_c(*machine, 1);
    move_stack_p(machine, 1);
    step_program_c(machine, 2);
}

void pop_inst(Machine* machine)
{
    test_stack(*machine, 1);
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void inc_inst(Machine* machine)
{
    test_stack(*machine, 1);
    machine->stack[machine->stack_p - 1] += 1;
    step_program_c(machine, 1);
}

void add_inst(Machine* machine)
{
    test_stack(*machine, 2);
    machine->stack[machine->stack_p - 2] = machine->stack[machine->stack_p - 2] + machine->stack[machine->stack_p - 1];
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void sub_inst(Machine* machine)
{
    test_stack(*machine, 2);
    machine->stack[machine->stack_p - 2] = machine->stack[machine->stack_p - 2] - machine->stack[machine->stack_p - 1];
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void mul_inst(Machine* machine)
{
    test_stack(*machine, 2);
    machine->stack[machine->stack_p - 2] = machine->stack[machine->stack_p - 2] * machine->stack[machine->stack_p - 1];
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void div_inst(Machine* machine)
{
    test_stack(*machine, 2);
    if(machine->stack[machine->stack_p - 1] == 0){
        zero_division();
    }
    machine->stack[machine->stack_p - 2] = machine->stack[machine->stack_p - 2] / machine->stack[machine->stack_p - 1];
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void mod_inst(Machine* machine)
{
    test_stack(*machine, 2);
    if(machine->stack[machine->stack_p - 1] == 0){
        zero_division();
    }
    machine->stack[machine->stack_p - 2] = machine->stack[machine->stack_p - 2] % machine->stack[machine->stack_p - 1];
    move_stack_p(machine, -1);
    step_program_c(machine, 1);
}

void swap_inst(Machine* machine)
{   
    test_stack(*machine, 2);
    int aux = machine->stack[machine->stack_p - 2];
    machine->stack[machine->stack_p - 2] = machine->stack[machine->stack_p - 1];
    machine->stack[machine->stack_p - 1] = aux;
    step_program_c(machine, 1);
}

void dup_inst(Machine* machine)
{   
    test_stack(*machine, 1);
    machine->stack[machine->stack_p] = machine->stack[machine->stack_p - 1];
    move_stack_p(machine, 1);
    step_program_c(machine, 1);
}

void over_inst(Machine* machine)
{   
    test_stack(*machine, 2);
    machine->stack[machine->stack_p] = machine->stack[machine->stack_p - 2];
    move_stack_p(machine, 1);
    step_program_c(machine, 1);
}

void load_inst(Machine* machine)
{
    int address = read_program_c(*machine, 1);
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    machine->stack[machine->stack_p] = machine->memory[address];
    move_stack_p(machine, 1);
    step_program_c(machine, 2);
}

void store_inst(Machine* machine)
{
    int address = read_program_c(*machine, 1);
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    test_stack(*machine, 1);
    machine->memory[address] = machine->stack[machine->stack_p - 1];
    move_stack_p(machine, -1);
    step_program_c(machine, 2);
}

void jump_inst(Machine* machine)
{
    int address = read_program_c(*machine, 1);
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    machine->program_c = address;
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
    int time = read_program_c(*machine, 1);
    sleep(time);
    step_program_c(machine, 2);
}

void halt_inst(Machine* machine)
{
    (void)machine; // Remove unused warning
    exit(EXIT_SUCCESS);
}

