	.file	"docs/Codeplay/examples/ex8/ex8.ll"
	.text
	.globl	foo
	.type	foo,@function
foo:                                    # @foo
# BB#0:                                 # %entry
	movw r1, #3
	mul r0, r0, r1
	bx lr
.tmp0:
	.size	foo, .tmp0-foo

	.globl	bar
	.type	bar,@function
bar:                                    # @bar
# BB#0:                                 # %entry
	add r0, r0, #5
	movw r1, foo
	movt r1, foo
	bl r1
	bx lr
.tmp1:
	.size	bar, .tmp1-bar


	.ident	"clang version 3.4.2 "
