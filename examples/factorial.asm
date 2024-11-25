; recursive algorithm that prints the factorial of a number

is0:    push    1       ; if the input was 0 print 1 and end
        print   
        jmp     end

; factorial subroutine
fact:   dup             ; calculate the next element
        push    1
        sub
        
        dup             ; if the value is 0 end recurssion
        jnz     else
        pop
        ret

else:   call    fact    ; otherwise call the subroutine recursively
        mul             ; multiply all the elements on the stack after recurssion and return
        ret

; start program at main
main:   dup             ; if the input is negative exit
        neg
        jnz     end
        
        dup             ; check if the input is 0
        push    0
        cmp
        jnz     is0

        call    fact    ; call the subroutine and print the result when it has ended
        print
end:    halt

    








