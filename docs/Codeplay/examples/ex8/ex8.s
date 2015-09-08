	.text
	.file	"../../docs/Codeplay/examples/ex8/ex8.ll"
	.globl	foo
	.type	foo,@function
foo:                                    # @foo
# BB#0:                                 # %entry
	movw r1, #3
	mul r0, r0, r1
	bx lr
.Lfunc_end0:
	.size	foo, .Lfunc_end0-foo

	.globl	bar
	.type	bar,@function
bar:                                    # @bar
# BB#0:                                 # %entry
	add r0, r0, #5
	movw r1, foo
	movt r1, foo
	bl r1
	bx lr
.Lfunc_end1:
	.size	bar, .Lfunc_end1-bar


	.section	".note.GNU-stack","",@progbits
