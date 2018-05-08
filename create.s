	.file	"create.c"
	.section	.rodata
.LC0:
	.string	"./test.txt"
.LC1:
	.string	"file open error!!"
.LC2:
	.string	"fd=%d\n wcnt=%d\n"
.LC3:
	.string	"rcount=%d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB2:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$320, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$500, %edx
	movl	$578, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	open
	movl	%eax, -316(%rbp)
	cmpl	$-1, -316(%rbp)
	jne	.L2
	movl	$.LC1, %edi
	call	puts
	movl	$-1, %eax
	jmp	.L4
.L2:
	leaq	-304(%rbp), %rax
	movabsq	$7142837030947417924, %rcx
	movq	%rcx, (%rax)
	movabsq	$7307218078149801327, %rsi
	movq	%rsi, 8(%rax)
	movabsq	$2334397804646326816, %rcx
	movq	%rcx, 16(%rax)
	movabsq	$8386098469825505396, %rsi
	movq	%rsi, 24(%rax)
	movl	$682083, 32(%rax)
	leaq	-304(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	movq	%rax, %rdx
	leaq	-304(%rbp), %rcx
	movl	-316(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write
	movl	%eax, -312(%rbp)
	movl	-312(%rbp), %edx
	movl	-316(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	movl	-316(%rbp), %eax
	movl	$0, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	lseek
	movl	%eax, -308(%rbp)
	leaq	-240(%rbp), %rcx
	movl	-316(%rbp), %eax
	movl	$16, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -308(%rbp)
	movl	-308(%rbp), %eax
	cltq
	movb	$0, -240(%rbp,%rax)
	leaq	-240(%rbp), %rax
	movq	$-1, %rcx
	movq	%rax, %rdx
	movl	$0, %eax
	movq	%rdx, %rdi
	repnz scasb
	movq	%rcx, %rax
	notq	%rax
	leaq	-1(%rax), %rdx
	leaq	-240(%rbp), %rax
	addq	%rdx, %rax
	movl	$1734829344, (%rax)
	movw	$115, 4(%rax)
	leaq	-240(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	leaq	-176(%rbp), %rdx
	leaq	-240(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcpy
	movl	-316(%rbp), %eax
	movl	$0, %edx
	movl	$16, %esi
	movl	%eax, %edi
	call	lseek
	movl	%eax, -308(%rbp)
	leaq	-176(%rbp), %rcx
	movl	-316(%rbp), %eax
	movl	$50, %edx
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -308(%rbp)
	leaq	-176(%rbp), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	strcat
	movl	-308(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	puts
	movl	-316(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	$0, %eax
.L4:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L5
	call	__stack_chk_fail
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
