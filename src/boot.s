.set MAGIC,    0x1BADB002
.set FLAGS,    0x00000007
.set CHECKSUM, -(MAGIC + FLAGS)

.set VM_BASE,     0x2000000
.set PDE_INDEX,   (VM_BASE >> 22)
.set PSE_BIT,     0x00000010
.set PG_BIT,      0x80000000

.section .multiboot
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0
.long 0
.long 0
.long 0
.long 0
.long 0
.long 800
.long 600
.long 32

.section .data
.global TEMP_PAGE_DIRECTORY
TEMP_PAGE_DIRECTORY:
    .long 0x00000083
    .space (PDE_INDEX - 1)
    .long 0x00000083
    .space (1024 - PDE_INDEX - 1) 

.section .initial_stack, "aw", @nobits
.align 4

stackBottom:
	.skip 104856
stackTop:

.section .text
.global _start
.type _start, @function
.global _l_start
.set _l_start,	(_start - VM_BASE)

_start:
    mov (TEMP_PAGE_DIRECTORY - VM_BASE), %ecx
    mov %ecx, %cr3

    mov %cr4, %ecx
    or PSE_BIT, %ecx
    mov %ecx, %cr4

    mov %cr0, %ecx
    or PG_BIT, %ecx
    mov %ecx, %cr0

	lea _remaining, %ecx
    jmp %ecx


_remaining:
	mov $stackTop, %esp
	pushl %ebx
	pushl %eax
	call main
	cli

hltLoop:
	jmp hltLoop

.size _start, . - _start
