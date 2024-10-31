#include "machine.h"
#include "error.h"

// Global data structures
static int      stack[MAX_STK];
static size_t   stack_p;
static int      program_memory[MAX_MEM];
static size_t   program_c;

typedef enum {
    #define X_OP(opcode, opname, execute) opcode,
    OPERATIONS
    #undef  X_OP
    ILLEGAL
} OpCode;

struct Operation {
    OpCode opcode;
    const char* opname;
    void(*execute)();
};

static const struct Operation OpMap[] = {
    #define X_OP(opcode, opname, execute) {opcode, opname, execute},
    OPERATIONS
    #undef  X_OP
};

// Helper functions
static int get_opcode(char* word)
{
    for(size_t i = 0; i < sizeof(OpMap) / sizeof(struct Operation); i++){
        if(!strcmp(OpMap[i].opname, word)){
            return OpMap[i].opcode;
        }
    }
    return ILLEGAL; 
}

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

static void step_program_c(size_t offset)
{
    if(program_c + offset >= MAX_MEM){
        memory_out_of_bounds();
    }
    program_c += offset;
}

static int read_program_c(size_t offset)
{
    if(program_c + offset >= MAX_MEM){
        memory_out_of_bounds();
    }
    return program_memory[program_c + offset];
}

static void move_stack_p(int offset)
{
    if(stack_p + offset > MAX_STK){
        stack_overflow();
    }
    if((int)stack_p + offset < 0){
        stack_underflow();
    }
    stack_p += offset;
}

static void test_stack(int elements)
{
    if((int)stack_p < elements){
        stack_underflow();
    }
}

// Program loading
void load_prog(char* program)
{
    FILE* prog = fopen(program, "r");
    if(prog == NULL){
       fprintf(stderr, "ERROR: Could not open %s file\n", program);
       exit(EXIT_FAILURE);
    }
    char word[MAX_WORD];
    int i = 0;
    while(fscanf(prog, "%s", word) == 1){
        if(is_int(word)){
            program_memory[i] = atoi(word);
        }
        else{
            program_memory[i] = get_opcode(word);
        }
        i++;
    }
    fclose(prog);
}

// Program execution
void execute_next()
{
    OpCode op = read_program_c(0);
    if(op == ILLEGAL){
        illegal_instruction();
    }
    OpMap[op].execute();
}

// Instructions
void push_op()
{
    stack[stack_p] = read_program_c(1);
    move_stack_p(1);
    step_program_c(2);
}

void pop_op()
{
    test_stack(1);
    move_stack_p(-1);
    step_program_c(1);
}

void inc_op()
{
    test_stack(1);
    stack[stack_p - 1] += 1;
    step_program_c(1);
}

void add_op()
{
    test_stack(2);
    stack[stack_p - 2] = stack[stack_p - 2] + stack[stack_p - 1];
    move_stack_p(-1);
    step_program_c(1);
}

void sub_op()
{
    test_stack(2);
    stack[stack_p - 2] = stack[stack_p - 2] - stack[stack_p - 1];
    move_stack_p(-1);
    step_program_c(1);
}

void mul_op()
{
    test_stack(2);
    stack[stack_p - 2] = stack[stack_p - 2] * stack[stack_p - 1];
    move_stack_p(-1);
    step_program_c(1);
}

void div_op()
{
    test_stack(2);
    if(stack[stack_p - 1] == 0){
        zero_division();
    }
    stack[stack_p - 2] = stack[stack_p - 2] / stack[stack_p - 1];
    move_stack_p(-1);
    step_program_c(1);
}

void mod_op()
{
    test_stack(2);
    if(stack[stack_p - 1] == 0){
        zero_division();
    }
    stack[stack_p - 2] = stack[stack_p - 2] % stack[stack_p - 1];
    move_stack_p(-1);
    step_program_c(1);
}

void swap_op()
{   
    test_stack(2);
    int aux = stack[stack_p - 2];
    stack[stack_p - 2] = stack[stack_p - 1];
    stack[stack_p - 1] = aux;
    step_program_c(1);
}

void dup_op()
{   
    test_stack(1);
    stack[stack_p] = stack[stack_p - 1];
    move_stack_p(1);
    step_program_c(1);
}

void over_op()
{   
    test_stack(2);
    stack[stack_p] = stack[stack_p - 2];
    move_stack_p(1);
    step_program_c(1);
}

void load_op()
{
    int address = read_program_c(1);
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    stack[stack_p] = program_memory[address];
    move_stack_p(1);
    step_program_c(2);
}

void store_op()
{
    int address = read_program_c(1);
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    test_stack(1);
    program_memory[address] = stack[stack_p - 1];
    move_stack_p(-1);
    step_program_c(2);
}

void jump_op()
{
    int address = read_program_c(1);
    if(address >= MAX_MEM){
        memory_out_of_bounds();
    }
    program_c = address;
}

void print_op()
{
    if(stack_p < 1){
        printf("EMPTY\n");
    }
    else{
        printf("%d\n", stack[stack_p - 1]);
    }
    step_program_c(1);
}

void sleep_op()
{
    int time = read_program_c(1);
    sleep(time);
    step_program_c(2);
}

void halt_op()
{
    exit(EXIT_SUCCESS);
}

void dump_machine()
{
    for(int i = 0; i < (int)stack_p; i++){
        printf("%d, ", stack[i]);
    }
    printf("\n");
}







