; takes an argument array and prints it
; writes all the arguments into a vector and reads from the vector

        size            ; if no arguments end
        push    0       
        cmp
        jnz     end

        push    0       ; vector size
        sti     90      ; stored at 90

write:  size            ; check is the stack is empty
        push    0
        cmp
        jnz     read    ; if its empty write on the vector
        
        ldi     90
        push    100     ; vector starts at 100
        add             ; next address = vector + size

        sts             ; store in address on top of the stack

        ldi     90      ; increment vector size
        inc     
        sti     90
            
        jmp     write   ; repeat
    
read:   ldi     90      ; subtract 1 from size
        push    1
        sub
        sti     90

        push    100
        ldi     90
        add
        lds

        print
        pop
        
        ldi     90      ; if size is 0 end
        push    0
        cmp
        jnz     end

        jmp     read    ; repeat

end:    halt

