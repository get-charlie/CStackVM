; takes the number of iterations as an argument and returns the fibonacci sequence up to that number

        push    0       ; store number of iterations
        sti     100     ; store number of iterations to dir 100

        sti     110     ; store cli argumet to 110
       
        ldi     110     ; if argument is negative end
        neg
        jnz     end
        
        ldi     110     ; if argument is 0 end
        push    0
        jnz     end

        push    1       ; fibonacci base case
        push    1
        print

loop:   ldi     100     ; increase the number of iterarions
        inc 
        sti     100 

        ldi     100     ; if cli argument == number of iterations end
        ldi     110
        cmp
        jnz     end
        
        swap            ; swap the top values of the stack
        over            ; copy the second element from the top and push it on top
        add             ; add the top two values of the stack
        print           ; output the top of the stack

        jmp     loop    ; repeat

end:    halt

