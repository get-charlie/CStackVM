#include "machine.h"
#include "instruction.h"

// Global data structures
static int      stack[MAX_STK];
static size_t   stack_p;
static int      program_memory[MAX_MEM];
static size_t   program_c;


// Program loading
struct OpPair {
    const char* opname;
    OpCode  code;
};

static const struct OpPair OpMap [] = {
    {"push" , PUSH},
    {"pop"  , POP},
    {"swap" , SWAP},
    {"over" , OVER},
    {"dup"  , DUP},
    {"inc"  , INC},
    {"add"  , ADD},
    {"sub"  , SUB},
    {"mul"  , MUL},
    {"mod"  , DIV},
    {"load" , LOAD},
    {"store", STORE},
    {"jump" , JUMP},
    {"print", PRINT},
    {"sleep", SLEEP},
    {"halt" , HALT},
};

static int get_op(char* word)
{
    for(int i = 0; i < sizeof(OpMap) / sizeof(struct OpPair); i++){
        if(!strcmp(OpMap[i].opname, word)){
            return OpMap[i].code;
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
            program_memory[i] = get_op(word);
        }
        i++;
    }
    fclose(prog);
}

// Machine Control
void step_prog(size_t step)
{
    program_c += step;
}

int read_mem(size_t offset)
{
   return program_memory[program_c + offset];
}

// Instructions
State push_op(int x)
{
    if(stack_p == MAX_STK){
        return STK_OVERFLOW;
    }
    stack[stack_p] = x;
    stack_p++;
    return NOMINAL;
}

State pop_op()
{
    if(stack_p < 1){
        return STK_UNDERFLOW;
    }
    stack_p--;
    return NOMINAL;
}

State inc_op()
{
    if(stack_p < 1){
        return STK_UNDERFLOW;
    }
    stack[stack_p - 1] += 1;
    return NOMINAL;
}

State add_op()
{
    if(stack_p < 2){
        return STK_UNDERFLOW;
    }
    stack[stack_p - 2] = stack[stack_p - 2] + stack[stack_p - 1];
    stack_p--;
    return NOMINAL;
}

State sub_op()
{
    if(stack_p < 2){
        return STK_UNDERFLOW;
    }
    stack[stack_p - 2] = stack[stack_p - 2] - stack[stack_p - 1];
    stack_p--;
    return NOMINAL;
}

State mul_op()
{
    if(stack_p < 2){
        return STK_UNDERFLOW;
    }
    stack[stack_p - 2] = stack[stack_p - 2] * stack[stack_p - 1];
    stack_p--;
    return NOMINAL;
}

State div_op()
{
    if(stack_p < 2){
        return STK_UNDERFLOW;
    }
    if(stack[stack_p - 1] == 0){
        return ZERO_DIVISION;
    }
    stack[stack_p - 2] = stack[stack_p - 2] / stack[stack_p - 1];
    stack_p--;
    return NOMINAL;
}

State mod_op()
{
    if(stack_p < 2){
        return STK_UNDERFLOW;
    }
    if(stack[stack_p - 1] == 0){
        return ZERO_DIVISION;
    }
    stack[stack_p - 2] = stack[stack_p - 2] % stack[stack_p - 1];
    stack_p--;
    return NOMINAL;
}

State swap_op()
{
    if(stack_p < 2){
        return STK_UNDERFLOW;
    }
    int aux = stack[stack_p - 2];
    stack[stack_p - 2] = stack[stack_p - 1];
    stack[stack_p - 1] = aux;
    return NOMINAL;
}

State dup_op()
{
    if(stack_p == MAX_STK){
        return STK_OVERFLOW;
    }
    stack[stack_p] = stack[stack_p - 1];
    stack_p++;
    return NOMINAL;
}

State over_op()
{
    if(stack_p == MAX_STK){
        return STK_OVERFLOW;
    }
    stack[stack_p] = stack[stack_p - 2];
    stack_p++;
    return NOMINAL;
}

State load_op(size_t address)
{
    if(address < 0 || address >= MAX_MEM){
        return MEM_OUT_OF_BOUNDS;
    }
    if(stack_p == MAX_STK){
        return STK_OVERFLOW;
    }
    stack[stack_p] = program_memory[address];
    stack_p++;
    return NOMINAL;
}

State store_op(size_t address)
{
    if(address < 0 || address >= MAX_MEM){
        return MEM_OUT_OF_BOUNDS;
    }
    if(stack_p < 1){
        return STK_UNDERFLOW;
    }
    program_memory[address] = stack[stack_p - 1];
    stack_p--;
    return NOMINAL;
}

State jump_op(size_t address)
{
    if(address < 0 || address >= MAX_MEM){
        return MEM_OUT_OF_BOUNDS;
    }
    program_c = address;
    return NOMINAL;
}

State print_op()
{
    if(stack_p < 1){
        printf("EMPTY\n");
    }
    else{
        printf("%d\n", stack[stack_p - 1]);
    }
    return NOMINAL;
}

State sleep_op(int time)
{
    sleep(time);
    return NOMINAL;
}

// Error handling functions
const char* state_to_string(State state)
{
    switch (state){
        case NOMINAL:           return "NOMINAL";
        case STK_OVERFLOW:      return "STK_OVERFLOW";
        case STK_UNDERFLOW:     return "STK_UNDERFLOW";
        case ILLEGAL_INST:      return "ILLEGAL_INST";
        case MEM_OUT_OF_BOUNDS: return "MEM_OUT_OF_BOUNDS";
        case ZERO_DIVISION:     return "ZERO_DIVISION";
        default:                return "UNKNOWN";
    }
}

void machine_dump()
{
    fprintf(stderr, "Machine dump:\n");
    for(int i = stack_p; i > 0; i--){
        fprintf(stderr, "%d\n", stack[i - 1]);
    }
}







