	.file	"cpycommit.c"
	.section	.rodata
.LC0:
	.string	"HLOG0 arg\352\260\200 \353\213\244\353\246\205\353\213\210\353\213\244."
.LC1:
	.string	"HLOG1 fp=%d\trfp=%d\n"
	.align 8
.LC2:
	.string	"ERROR:\354\232\251\353\237\211\354\235\264 \353\204\210\353\254\264 \355\201\275\353\213\210\353\213\244."
.LC3:
	.string	"HLOG2 mal=%s\n"
.LC4:
	.string	"HLOG3 fpbit=%d\t,\trfbbit=%d\n"
.LC5:
	.string	"HLOG4 bit=%d\n"
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
	subq	$576, %rsp
	movl	%edi, -564(%rbp)
	movq	%rsi, -576(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	leaq	-528(%rbp), %rdx
	movl	$0, %eax
	movl	$64, %ecx
	movq	%rdx, %rdi
	rep stosq
	cmpl	$3, -564(%rbp)
	je	.L2
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	movl	$-1, %eax
	jmp	.L6
.L2:
	movq	-576(%rbp), %rax
	addq	$8, %rax
	movq	(%rax), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, -556(%rbp)
	movq	-576(%rbp), %rax
	addq	$16, %rax
	movq	(%rax), %rax
	movl	$420, %edx
	movl	$1054198, %esi
	movq	%rax, %rdi
	movl	$0, %eax
	call	open
	movl	%eax, -552(%rbp)
	movl	-552(%rbp), %edx
	movl	-556(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	movl	-556(%rbp), %eax
	movl	$2, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	lseek
	movl	%eax, -548(%rbp)
	movl	-556(%rbp), %eax
	movl	$0, %edx
	movl	$0, %esi
	movl	%eax, %edi
	call	lseek
	cmpl	$104857599, -548(%rbp)
	jle	.L4
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	jmp	.L5
.L4:
	movl	-548(%rbp), %eax
	cltq
	salq	$3, %rax
	movq	%rax, %rdi
	call	malloc
	movq	%rax, -536(%rbp)
	movl	-548(%rbp), %eax
	movslq	%eax, %rdx
	movq	-536(%rbp), %rcx
	movl	-556(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	read
	movl	%eax, -544(%rbp)
	movl	-548(%rbp), %eax
	movslq	%eax, %rdx
	movq	-536(%rbp), %rcx
	movl	-552(%rbp), %eax
	movq	%rcx, %rsi
	movl	%eax, %edi
	call	write
	movl	%eax, -540(%rbp)
	movq	-536(%rbp), %rax
	movq	%rax, %rsi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
	movl	-540(%rbp), %edx
	movl	-544(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC4, %edi
	movl	$0, %eax
	call	printf
	movl	-548(%rbp), %eax
	movl	%eax, %esi
	movl	$.LC5, %edi
	movl	$0, %eax
	call	printf
.L5:
	movq	-536(%rbp), %rax
	movq	%rax, %rdi
	call	free
	movl	-556(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	-552(%rbp), %eax
	movl	%eax, %edi
	call	close
	movl	$0, %eax
.L6:
	movq	-8(%rbp), %rcx
	xorq	%fs:40, %rcx
	je	.L7
	call	__stack_chk_fail
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.9) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
