	.text
	.file	"../../docs/Codeplay/examples/ex6/ex6.ll"
	.globl	ex6
	.type	ex6,@function
ex6:                                    # @ex6
# BB#0:                                 # %entry
	cmp r0, r1
	ble .LBB0_2
# BB#1:                                 # %if.then
	add r0, r0, r1
	bx lr
.LBB0_2:                                # %if.else
	sub r0, r0, r1
	bx lr
.Ltmp0:
	.size	ex6, .Ltmp0-ex6


	.ident	"clang version 3.6.0 "
	.section	".note.GNU-stack","",@progbits
