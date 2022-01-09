.set MAGIC,    0x1BADB002
.set FLAGS,    0x00000007
.set CHECKSUM, -(MAGIC + FLAGS)

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
.long 1080
.long 720
.long 32

.section .data

stackBottom:
	.skip 104856
stackTop:

.section .text
.global _start
.type _start, @function

_start:
	mov $stackTop, %esp
	pushl %ebx
	pushl %eax
	call main
	cli

hltLoop:
	jmp hltLoop

.size _start, . - _start
