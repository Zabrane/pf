#include<asm/unistd_32.h>

#define F(n) .globl n;n:

#define S(n) F(n)movl %ecx,%r10;movl $__NR_##n,%eax;syscall;ret;

//F(_start)lea 8(%rsp),%rdi;jmp main;

_start:
    movl $4, %eax   ; use the `write` [interrupt-flavor] system call
    movl $1, %ebx   ; write to stdout
    movl $msg, %ecx ; use string "Hello World"
    movl $12, %edx  ; write 12 characters
    int $0x80       ; make system call
    
    movl $1, %eax   ; use the `_exit` [interrupt-flavor] system call
    movl $0, %ebx   ; error code 0
    int $0x80       ; make system call


S(write)
S(exit)

//:~
