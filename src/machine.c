#include "machine.h"

#include "instruction.h"
#include "error.h"

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

static void copy_tag(char* dest, char* source){
    size_t i;
    for(i = 0; i < sizeof(source) && source[i] != ':'; i++){
        dest[i] = source[i];
    }
    dest[i] = '\0';
}

struct JumpTag {
    char tag[MAX_WORD];
    int  address;
}; 

static int get_jump_index(struct JumpTag table[MAX_TAGS], size_t table_size, char* tok)
{
    for(size_t i = 0; i < table_size; i++){
        if(!strcmp(tok, table[i].tag)){
            return table[i].address;
        }
    }
    return -1;
}

// Program loading
void load_prog(Machine* machine, char* path)
{
    FILE* prog = fopen(path, "r");
    if(prog == NULL){
       fprintf(stderr, "ERROR: Could not open %s file\n", path);
       exit(EXIT_FAILURE);
    }
    char line[MAX_LINE];
    struct JumpTag jump_table[MAX_TAGS] = {0};
    size_t table_size = 0;
    int cur_dir = 0;
    while(fgets(line, MAX_LINE, prog)){
        char* tok = strtok(line, DELIM);
        while(tok != NULL){
            if(strchr(tok, ';')){
                break;
            }
            if(strchr(tok, ':') && table_size < MAX_TAGS){
                copy_tag(jump_table[table_size].tag, tok);
                jump_table[table_size].address = cur_dir;
                table_size++;
                tok = strtok(NULL, DELIM);
                continue;
            }
            int address = get_jump_index(jump_table, table_size, tok); 
            if(address > 0){
                write_memory(machine, cur_dir, address);
            }
            else if(is_int(tok)){
                write_memory(machine, cur_dir, atoi(tok));
            }
            else{
                write_memory(machine, cur_dir, get_instcode(tok));
            }
            tok = strtok(NULL, DELIM);
            cur_dir++;
        }
    }
    fclose(prog);
}

void push_args(Machine* machine, int argc, char* argv[])
{
    for(int i = 2; i < argc; i++){
        set_stack_val(machine, 0, atoi(argv[i]));
        move_stack_p(machine, 1);
    }
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
    for(int i = 0; i < MAX_MEM; i++){
        printf("dir: %d %3d\n", i, machine.memory[i]);
    }
}



