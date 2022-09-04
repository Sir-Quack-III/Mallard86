/* Declare constants for the multiboot header. */
.set ALIGN,    1<<0             /* align loaded modules on page boundaries */
.set MEMINFO,  1<<1             /* provide memory map */
.set FLAGS,    ALIGN | MEMINFO  /* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       /* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) /* checksum of above, to prove we are multiboot */
 
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
 
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
 
.section .text
.global gdt_flush 
.extern _gp
gdt_flush:
    lgdt [gp]
    mov %ax, 0x10 
    mov %ds, %ax
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
	# jmp 0x08:flush2
    jmp flush2
flush2:
    ret

.global reload_segments
reload_segments:
   # Reload CS register containing code selector:
   jmp 	 reload_CS # 0x08 is a stand-in for your code segment
reload_CS:
   # Reload data segment registers:
   mov   %AX, 0x10 # 0x10 is a stand-in for your data segment
   mov   %DS, %AX
   mov   %ES, %AX
   mov   %FS, %AX
   mov   %GS, %AX
   mov   %SS, %AX
   ret

.global _start
.type _start, @function
_start:
	mov $stack_top, %esp
	call kernel_main
	cli
1:	hlt
	jmp 1b

 
.size _start, . - _start
