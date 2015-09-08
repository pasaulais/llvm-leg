	.text
	.file	"../../docs/Codeplay/examples/ex7/ex7.ll"
	.globl	ex7
	.type	ex7,@function
ex7:                                    # @ex7
# BB#0:                                 # %entry
	ldr r0, [r0]
	add r0, r0, #42
	str r0, [r1]
	bx lr
.Lfunc_end0:
	.size	ex7, .Lfunc_end0-ex7


	.section	".note.GNU-stack","",@progbits
