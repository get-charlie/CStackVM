; takes a list of ints and returns the sum
        
loop:   size
        push    1 
        cmp
        jnz     end
        add
        jmp     loop

end:    print
        halt
