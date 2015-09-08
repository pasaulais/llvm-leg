	.text
	.file	"../../docs/Codeplay/examples/ex5/ex5.ll"
	.globl	foo
	.type	foo,@function
foo:                                    # @foo
# BB#0:
	movw r1, #2
	movt r1, #1
	add r0, r0, r1
	bx lr
.Lfunc_end0:
	.size	foo, .Lfunc_end0-foo


	.section	".note.GNU-stack","",@progbits
