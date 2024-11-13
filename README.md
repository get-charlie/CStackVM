# CStackVM
Some virtual machine that runs some questionably designed assembly.

### Compiling  
Just run the script build.sh. Run the script with the 'debug' flag to enable step by step debugging.

### How to run a program  
Write a program in the machine's assembly. You can find some examples in the examples directory.
Instructions are documented in instruction.h via comments.
Once the machine is compiled and your program is written run the machine with the program as an argument.
All other arguments will be pushed to the machine's stack.

### Adding new instructions
To add new instructions you must add an enum value, an instruction name and a function to the X-macro defined in instruction.h.
Then add the header below. The implementation must be in instructions.c. To manipulate the machine it is encouraged
to use the functions defined in machine.h.

