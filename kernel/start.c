// entry.S needs one stack per CPU.
// 在这里分配栈空间供每个cpu使用
// 原版xv6使用单个4096的栈，这里分配了一个更大的栈(4096*16)
// 在entry.S中，将栈顶地址设为该数字的高地址，因为riscv的地址从高到低增长
__attribute__ ((aligned (16))) char stack0[4096*16];

void main(void);

void start(void)
{
    // 在xv-riscv中，没有使用opensbi引导，故这里需要一些代码来进入s模式
    // 这里使用opensbi引导，已经进入了s模式，但预留start.c进行一些初始化
    main();
}