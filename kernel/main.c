#include "sbi.h"
#include "console.h"
#include "printf.c"

void main(void)
{
    const unsigned char hello[] = "Hello World!\n";
    // 进行控制台的初始化
    console_init();
    // 实现你的printf，在riscv上输出hello world
    printf(hello);
    sbi_shutdown();
}