; takes the number of iterations as an argument and returns the fibonacci sequence up to that number

        sti     30      ; write command line argument into address 100
        push    0       ; number of iterations
        sti     31      ; write number of iterations to address 110

        push    1       ; fibonacci base case
        push    1

loop:   print           ; output the top of the stack
        swap            ; swap the top values of the stack
        over            ; copy the second element from the top and push it on top
        add             ; add the top two values of the stack

        ldi     31      ; push number of iterations to the top
        inc             ; increase it by 1
        sti     31      ; store it to address memory
        ldi     31      ; push it again as it was poped by last sti
        ldi     30      ; push command line argument

        cmp             ; check if they are equal
        not             ; revert the result of the previous operation
        jnz     loop    ; if they were not equal jump to 10

        halt
