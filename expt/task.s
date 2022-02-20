	.file	"task.cpp"
# GNU C++14 (Ubuntu 9.3.0-17ubuntu1~20.04) version 9.3.0 (x86_64-linux-gnu)
#	compiled by GNU C version 9.3.0, GMP version 6.2.0, MPFR version 4.0.2, MPC version 1.1.0, isl version isl-0.22.1-GMP

# GGC heuristics: --param ggc-min-expand=100 --param ggc-min-heapsize=131072
# options passed:  -imultiarch x86_64-linux-gnu -D_GNU_SOURCE -D_REENTRANT
# task.cpp -mtune=generic -march=x86-64 -fverbose-asm -fopenmp
# -fasynchronous-unwind-tables -fstack-protector-strong -Wformat
# -Wformat-security -fstack-clash-protection -fcf-protection
# options enabled:  -fPIC -fPIE -faggressive-loop-optimizations
# -fassume-phsa -fasynchronous-unwind-tables -fauto-inc-dec -fcommon
# -fdelete-null-pointer-checks -fdwarf2-cfi-asm -fearly-inlining
# -feliminate-unused-debug-types -fexceptions -ffp-int-builtin-inexact
# -ffunction-cse -fgcse-lm -fgnu-runtime -fgnu-unique -fident
# -finline-atomics -fipa-stack-alignment -fira-hoist-pressure
# -fira-share-save-slots -fira-share-spill-slots -fivopts
# -fkeep-static-consts -fleading-underscore -flifetime-dse
# -flto-odr-type-merging -fmath-errno -fmerge-debug-strings -fpeephole
# -fplt -fprefetch-loop-arrays -freg-struct-return
# -fsched-critical-path-heuristic -fsched-dep-count-heuristic
# -fsched-group-heuristic -fsched-interblock -fsched-last-insn-heuristic
# -fsched-rank-heuristic -fsched-spec -fsched-spec-insn-heuristic
# -fsched-stalled-insns-dep -fschedule-fusion -fsemantic-interposition
# -fshow-column -fshrink-wrap-separate -fsigned-zeros
# -fsplit-ivs-in-unroller -fssa-backprop -fstack-clash-protection
# -fstack-protector-strong -fstdarg-opt -fstrict-volatile-bitfields
# -fsync-libcalls -ftrapping-math -ftree-cselim -ftree-forwprop
# -ftree-loop-if-convert -ftree-loop-im -ftree-loop-ivcanon
# -ftree-loop-optimize -ftree-parallelize-loops= -ftree-phiprop
# -ftree-reassoc -ftree-scev-cprop -funit-at-a-time -funwind-tables
# -fverbose-asm -fzero-initialized-in-bss -m128bit-long-double -m64 -m80387
# -malign-stringops -mavx256-split-unaligned-load
# -mavx256-split-unaligned-store -mfancy-math-387 -mfp-ret-in-387 -mfxsr
# -mglibc -mieee-fp -mlong-double-80 -mmmx -mno-sse4 -mpush-args -mred-zone
# -msse -msse2 -mstv -mtls-direct-seg-refs -mvzeroupper

	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
# task.cpp:5: int main() {
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp87
	movq	%rax, -8(%rbp)	# tmp87, D.3822
	xorl	%eax, %eax	# tmp87
# task.cpp:6:   int count = 50;
	movl	$50, -20(%rbp)	#, count
# task.cpp:7: #pragma omp parallel num_threads(4)
	leaq	-20(%rbp), %rax	#, tmp84
	movq	%rax, -16(%rbp)	# tmp84, .omp_data_o.10.count
	leaq	-16(%rbp), %rax	#, tmp85
	movl	$0, %ecx	#,
	movl	$4, %edx	#,
	movq	%rax, %rsi	# tmp85,
	leaq	main._omp_fn.0(%rip), %rdi	#,
	call	GOMP_parallel@PLT	#
# task.cpp:25: }
	movl	$0, %eax	#, _7
	movq	-8(%rbp), %rdx	# D.3822, tmp88
	xorq	%fs:40, %rdx	# MEM[(<address-space-1> long unsigned int *)40B], tmp88
	je	.L3	#,
	call	__stack_chk_fail@PLT	#
.L3:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.type	main._omp_fn.0, @function
main._omp_fn.0:
.LFB1:
	.cfi_startproc
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# .omp_data_i, .omp_data_i
# task.cpp:7: #pragma omp parallel num_threads(4)
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp95
	movq	%rax, -8(%rbp)	# tmp95, D.3824
	xorl	%eax, %eax	# tmp95
	call	GOMP_single_start@PLT	#
	cmpb	$1, %al	#, _5
	je	.L5	#,
.L6:
	call	GOMP_barrier@PLT	#
# task.cpp:7: #pragma omp parallel num_threads(4)
	movq	-8(%rbp), %rax	# D.3824, tmp96
	xorq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp96
	je	.L7	#,
	jmp	.L8	#
.L5:
# task.cpp:10:     while (count > 0) {
	movq	-24(%rbp), %rax	# .omp_data_i, tmp90
	movq	(%rax), %rax	# .omp_data_i_6(D)->count, _7
	movl	(%rax), %eax	# *_7, count.0_8
	testl	%eax, %eax	# count.0_8
	jle	.L6	#,
# task.cpp:11: #pragma omp task
	movq	-24(%rbp), %rax	# .omp_data_i, tmp91
	movq	(%rax), %rax	# .omp_data_i_6(D)->count, _9
	movq	%rax, -16(%rbp)	# _9, .omp_data_o.9.count
	leaq	-16(%rbp), %rax	#, tmp92
	subq	$8, %rsp	#,
	pushq	$0	#
	pushq	$0	#
	pushq	$0	#
	movl	$1, %r9d	#,
	movl	$8, %r8d	#,
	movl	$8, %ecx	#,
	movl	$0, %edx	#,
	movq	%rax, %rsi	# tmp92,
	leaq	main._omp_fn.1(%rip), %rdi	#,
	call	GOMP_task@PLT	#
	addq	$32, %rsp	#,
# task.cpp:21:       count--;
	movq	-24(%rbp), %rax	# .omp_data_i, tmp93
	movq	(%rax), %rax	# .omp_data_i_6(D)->count, _13
	movl	(%rax), %eax	# *_13, count.4_14
	leal	-1(%rax), %edx	#, count.5_15
	movq	-24(%rbp), %rax	# .omp_data_i, tmp94
	movq	(%rax), %rax	# .omp_data_i_6(D)->count, _16
	movl	%edx, (%rax)	# count.5_15, *_16
# task.cpp:22: #pragma omp flush
	mfence	
# task.cpp:10:     while (count > 0) {
	jmp	.L5	#
.L8:
# task.cpp:7: #pragma omp parallel num_threads(4)
	call	__stack_chk_fail@PLT	#
.L7:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE1:
	.size	main._omp_fn.0, .-main._omp_fn.0
	.section	.rodata
.LC0:
	.string	"Task10: %d,%d\n"
	.text
	.type	main._omp_fn.1, @function
main._omp_fn.1:
.LFB2:
	.cfi_startproc
	.cfi_personality 0x9b,DW.ref.__gxx_personality_v0
	.cfi_lsda 0x1b,.LLSDA2
	endbr64	
	pushq	%rbp	#
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp	#,
	.cfi_def_cfa_register 6
	subq	$32, %rsp	#,
	movq	%rdi, -24(%rbp)	# .omp_data_i, .omp_data_i
# task.cpp:11: #pragma omp task
	movq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp98
	movq	%rax, -8(%rbp)	# tmp98, D.3825
	xorl	%eax, %eax	# tmp98
# task.cpp:13:         int count2 = count;
	movq	-24(%rbp), %rax	# .omp_data_i, tmp91
	movq	(%rax), %rax	# .omp_data_i_3(D)->count, _4
	movl	(%rax), %eax	# *_4, tmp92
	movl	%eax, -12(%rbp)	# tmp92, count2
# task.cpp:14:         if (count == 10) {
	movq	-24(%rbp), %rax	# .omp_data_i, tmp93
	movq	(%rax), %rax	# .omp_data_i_3(D)->count, _6
	movl	(%rax), %eax	# *_6, count.1_7
# task.cpp:14:         if (count == 10) {
	cmpl	$10, %eax	#, count.1_7
	jne	.L9	#,
# task.cpp:15:           sleep(1);
	movl	$1, %edi	#,
	call	sleep@PLT	#
# task.cpp:17:           count = count;
	movq	-24(%rbp), %rax	# .omp_data_i, tmp94
	movq	(%rax), %rax	# .omp_data_i_3(D)->count, _9
	movl	(%rax), %eax	#* _9, _11
	movl	%eax, %edx	# _11, count.2_12
	movq	-24(%rbp), %rax	# .omp_data_i, tmp95
	movq	(%rax), %rax	# .omp_data_i_3(D)->count, _13
	movl	%edx, (%rax)	# count.2_12, *_13
# task.cpp:18:           printf("Task10: %d,%d\n", count, count2);
	movq	-24(%rbp), %rax	# .omp_data_i, tmp96
	movq	(%rax), %rax	# .omp_data_i_3(D)->count, _15
	movl	(%rax), %eax	# *_15, count.3_16
	movl	-12(%rbp), %edx	# count2, tmp97
	movl	%eax, %esi	# count.3_16,
	leaq	.LC0(%rip), %rdi	#,
	movl	$0, %eax	#,
	call	printf@PLT	#
.L9:
# task.cpp:11: #pragma omp task
	movq	-8(%rbp), %rax	# D.3825, tmp99
	xorq	%fs:40, %rax	# MEM[(<address-space-1> long unsigned int *)40B], tmp99
	je	.L12	#,
	call	__stack_chk_fail@PLT	#
.L12:
	leave	
	.cfi_def_cfa 7, 8
	ret	
	.cfi_endproc
.LFE2:
	.globl	__gxx_personality_v0
	.section	.gcc_except_table,"a",@progbits
.LLSDA2:
	.byte	0xff
	.byte	0xff
	.byte	0x1
	.uleb128 .LLSDACSE2-.LLSDACSB2
.LLSDACSB2:
.LLSDACSE2:
	.text
	.size	main._omp_fn.1, .-main._omp_fn.1
	.hidden	DW.ref.__gxx_personality_v0
	.weak	DW.ref.__gxx_personality_v0
	.section	.data.rel.local.DW.ref.__gxx_personality_v0,"awG",@progbits,DW.ref.__gxx_personality_v0,comdat
	.align 8
	.type	DW.ref.__gxx_personality_v0, @object
	.size	DW.ref.__gxx_personality_v0, 8
DW.ref.__gxx_personality_v0:
	.quad	__gxx_personality_v0
	.ident	"GCC: (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	 1f - 0f
	.long	 4f - 1f
	.long	 5
0:
	.string	 "GNU"
1:
	.align 8
	.long	 0xc0000002
	.long	 3f - 2f
2:
	.long	 0x3
3:
	.align 8
4:
