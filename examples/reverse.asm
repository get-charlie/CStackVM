; takes an argument array and prints it in reverse order
; writes all the arguments into a vector and reads from the vector

        push    0       ; vector size
        sti     90      ; stored at 90

        push    0       ; iterator
        sti     91      ; stored at 91

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
    
read:   ldi     90      ; check if size and iterator are equal
        ldi     91
        cmp
        jnz     end     ; if they are equal jump to end
        
        push    100     ; read the vector
        ldi     91
        add
        
        lds             ; load vector + iterator
        
        print           ; output the valie
        pop
        
        ldi     91      ; increment iterator
        inc
        sti     91

        jmp     read    ; repeat

end:    halt

