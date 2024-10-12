        # opensbi loads the kernel at 0x80200000
        # and causes each hart (i.e. CPU) to jump there.
        # kernel.ld causes the following code to
        # be placed at 0x80200000.
        #
        # in this section, we run our os in only one hart 
.section .text
.global _entry
_entry:
        # set up a stack for C.
        # stack0 is declared in start.c,
        # with a 4096-byte stack per CPU.
        # sp = stack0 + (hartid * 4096 * 16)
        la sp, stack0
        li a0, 4096*16
        add sp, sp, a0
        # jump to start() in start.c
        call start
