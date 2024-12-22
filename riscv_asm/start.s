# .global main
main:
    addi    sp, sp, -16     # allocate stack space
    sd      ra, 0(sp)       # save RA register since we're calling
    la      a0, test_solve  # load registers for function call
    call    solve           # call the function "solve"
    mv      a0, zero        # get ready to return from main (return 0)
    ld      ra, 0(sp)       # load back the return address
    addi    sp, sp, 16      # deallocate the stack space
    ret                     # return!

# li t1, 1
# li t2, 2
# add a0, t1, t2
# nop