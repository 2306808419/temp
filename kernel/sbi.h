/**
 * 这里根据riscv的sbi接口提供了若干封装好的sbi操作，感兴趣可以学习riscv的sbi调用约定
 */
#ifndef SBI_H
#define SBI_H

void sbi_console_putchar(int);
int sbi_console_getchar();
void sbi_shutdown();

#endif // SBI_H