@@startup
    .section .boot_kernel
    .text
    .global _start
    .align 4

.globl _start
_start:
    @@ Clearn General Register
    mov r0, #0
    mov r1, #0
    mov r2, #0
    mov r3, #0
    mov r4, #0
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    mov r9, #0
    mov r10, #0
    mov r11, #0

    @@ CPSR (32bit)
    @     09: Data endianness bit 
    @     08: Imprecise abort disable bit
    @     07: IRQ disable 
    @     06: FIQ disable
    @     05: Thumb state bit
    @  04-00: Modeb its
    ldr r0, = 0x000000d3
    msr cpsr, r0

    @@ Stack pointer using SVC mode
    mov sp, #0x8000

    @@ jump to C-function main
    bl main
    @@ terminate (infinite loop)
    b   .
