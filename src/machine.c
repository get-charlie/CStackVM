#include "machine.h"
#include "error.h"
#include "instruction.h"

typedef enum {
    #define X_INST(instcode, instname, execute) instcode,
    INSTRUCTIONS
    #undef  X_INST
    ILLEGAL
} InstCode;

struct Instrucion {
    InstCode instcode;
    const char* instname;
    void(*execute)(Machine* machine);
};

static const struct Instrucion InstMap[] = {
    #define X_INST(instcode, instname, execute) {instcode, instname, execute},
    INSTRUCTIONS
    #undef  X_INST
};

// Helper functions
static bool is_int(char* str)
{
    if(str == NULL || str[0] == '\0'){
        return false;
    }
    int i = 0;
    if(str[i] == '-' || str[i] == '+'){
        i++;
    }
    while(str[i]) {
        if(!isdigit(str[i])){
            return false;
        }
        i++;
    }
    return true;
}

static int get_instcode(char* word)
{
    for(size_t i = 0; i < sizeof(InstMap) / sizeof(struct Instrucion); i++){
        if(!strcmp(InstMap[i].instname, word)){
            return InstMap[i].instcode;
        }
    }
    return ILLEGAL; 
}

// Program loading
void load_prog(Machine* machine, char* program)
{
    FILE* prog = fopen(program, "r");
    if(prog == NULL){
       fprintf(stderr, "ERROR: Could not open %s file\n", program);
       exit(EXIT_FAILURE);
    }
    char word[MAX_WORD];
    int i = 0;
    while(fscanf(prog, "%s", word) == 1){
        if(i > MAX_MEM){
           memory_out_of_bounds(); 
        }
        if(is_int(word)){
            machine->memory[i] = atoi(word);
        }
        else{
            machine->memory[i] = get_instcode(word);
        }
        i++;
    }
    fclose(prog);
}

// Program execution
void execute_next(Machine* machine)
{
    InstCode inst = read_program_c(machine, 0);
    if(inst == ILLEGAL){
        illegal_instruction();
    }
    InstMap[inst].execute(machine);
}

// Machine control
void step_program_c(Machine* machine, size_t offset)
{
    if(machine->program_c + offset >= MAX_MEM){
        memory_out_of_bounds();
    }
    machine->program_c += offset;
}

int read_program_c(Machine* machine, size_t offset)
{
    if(machine->program_c + offset >= MAX_MEM){
        memory_out_of_bounds();
    }
    return machine->memory[machine->program_c + offset];
}

void move_program_c (Machine* machine, size_t address)
{   
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    machine->program_c = address;
}

int read_memory(Machine* machine, size_t address)
{
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    return machine->memory[address];
}

void write_memory(Machine* machine, size_t address, int val)
{
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    machine->memory[address] = val;
}

void test_stack(Machine* machine, int elements)
{
    if((int)machine->stack_p < elements){
        stack_underflow();
    }
}

int get_stack_val (Machine* machine, int offset)
{
    if((int)machine->stack_p + offset < 0 || machine->stack_p + offset > machine->stack_p){
        illegal_stack_access(); 
    }
    return machine->stack[machine->stack_p + offset];
}

void set_stack_val(Machine* machine, int offset, int val)
{
    if((int)machine->stack_p + offset < 0 || machine->stack_p + offset > MAX_STK){
        illegal_stack_access(); 
    }
    machine->stack[machine->stack_p + offset] = val;
}

void move_stack_p(Machine* machine, int offset)
{
    if(machine->stack_p + offset > MAX_STK){
        stack_overflow();
    }
    if((int)machine->stack_p + offset < 0){
        stack_underflow();
    }
    machine->stack_p += offset;
}

// Debugging
void dump_machine(Machine machine)
{
    for(int i = 0; i < (int)machine.stack_p; i++){
        printf("%d, ", machine.stack[i]);
    }
    printf("\n");
}



