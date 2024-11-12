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

typedef struct {
    char tag[MAX_WORD];
    int  address;
} JumpTag; 

typedef struct{
    JumpTag vector[MAX_TAGS];
    size_t  size;
} JumpTable;

static int get_jump_index(JumpTable jtable, char* tok)
{
    for(size_t i = 0; i < jtable.size; i++){
        if(!strcmp(tok, jtable.vector[i].tag)){
            return jtable.vector[i].address;
        }
    }
    return -1;
}

static void set_jump_table(JumpTable* table, FILE* prog)
{
    char line[MAX_LINE];
    int  cur_dir = 0;
    while(fgets(line, MAX_LINE, prog)){
        char* tok = strtok(line, DELIM);
        while(tok != NULL){
            if(table->size >= MAX_TAGS){
                fprintf(stderr, "Error: maximum number of jumps exceeded\n");
                exit(EXIT_FAILURE);
            }
            if(strchr(tok, ';')){
                break;
            }
            if(strchr(tok, ':')){
                copy_tag(table->vector[table->size].tag, tok);
                table->vector[table->size].address = cur_dir;
                // printf("%2d - tag: %8s, %2d\n", cur_dir, table->vector[table->size].tag, cur_dir);
                table->size++;
            }
            else{
                cur_dir++;
            }
            tok = strtok(NULL, DELIM);
        }
    }
}

void load_memory(Machine* machine, JumpTable jtable, FILE* prog)
{
    char line[MAX_LINE];
    int  cur_dir = 0;
    while(fgets(line, MAX_LINE, prog)){
        char* tok = strtok(line, DELIM);
        while(tok != NULL){
            if(strchr(tok, ';')){
                break;
            }
            if(strchr(tok, ':')){
                tok = strtok(NULL, DELIM);
                continue;
            }
            int address = get_jump_index(jtable, tok);
            if(address >= 0){
                write_memory(machine, cur_dir, address);
                // printf("%2d - jmp: %8s, %2d\n", cur_dir, tok, address);
            }
            else if(is_int(tok)){
                write_memory(machine, cur_dir, atoi(tok));
                // printf("%2d - num: %8s\n", cur_dir, tok);
            }
            else{
                write_memory(machine, cur_dir, get_instcode(tok));
                // printf("%2d - ins: %8s\n", cur_dir, tok);
            }
            tok = strtok(NULL, DELIM);
            cur_dir++;
        }
    }
}

// Program loading
void load_prog(Machine* machine, char* path)
{
    FILE* prog = fopen(path, "r");
    if(prog == NULL){
       fprintf(stderr, "ERROR: Could not open %s file\n", path);
       exit(EXIT_FAILURE);
    }
    
    JumpTable jtable = {0};
    set_jump_table(&jtable, prog);
    rewind(prog);
   
    load_memory(machine, jtable, prog);

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
    // printf("\n");
    // for(int i = 0; i < MAX_MEM; i++){
    //     printf("%3d ", i);
    // }
    // printf("\n");
    // for(int i = 0; i < MAX_MEM; i++){
    //     printf("%3d ", machine.memory[i]);
    // }
}



