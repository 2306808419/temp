#include "memlayout.h"
#include "param.h"
#include "riscv.h"
// #include "types.h"

#define THR 0                 // transmit holding register (for output bytes)
#define LSR 5                 // line status register
#define LSR_TX_IDLE (1 << 5)  // THR can accept another character to send
#define Reg(reg) ((volatile unsigned char *)(UART0 + (reg)))
#define ReadReg(reg) (*(Reg(reg)))
#define WriteReg(reg, v) (*(Reg(reg)) = (v))

// void main();
// void timerinit();

// entry.S needs one stack per CPU.
__attribute__((aligned(16))) char stack0[4096];

void uartputc_sync(int c) {
  // wait for Transmit Holding Empty to be set in LSR.
  while ((ReadReg(LSR) & LSR_TX_IDLE) == 0);
  WriteReg(THR, c);
}

char helloStr[] = "Hello World!";

// entry.S jumps here in machine mode on stack0.
void start() {
  // disable paging for now.
  // w_satp(0);
  for (uint i = 0; i < sizeof(helloStr); i++) {
    uartputc_sync(helloStr[i]);
  }
  //   // set M Previous Privilege mode to Supervisor, for mret.
  //   unsigned long x = r_mstatus();
  //   x &= ~MSTATUS_MPP_MASK;
  //   x |= MSTATUS_MPP_S;
  //   w_mstatus(x);

  //   // set M Exception Program Counter to main, for mret.
  //   // requires gcc -mcmodel=medany
  //   w_mepc((uint64)main);

  //   // disable paging for now.
  //   w_satp(0);

  //   // delegate all interrupts and exceptions to supervisor mode.
  //   w_medeleg(0xffff);
  //   w_mideleg(0xffff);
  //   w_sie(r_sie() | SIE_SEIE | SIE_STIE | SIE_SSIE);

  //   // configure Physical Memory Protection to give supervisor mode
  //   // access to all of physical memory.
  //   w_pmpaddr0(0x3fffffffffffffull);
  //   w_pmpcfg0(0xf);

  //   // ask for clock interrupts.
  //   timerinit();

  //   // keep each CPU's hartid in its tp register, for cpuid().
  //   int id = r_mhartid();
  //   w_tp(id);

  //   // switch to supervisor mode and jump to main().
  //   asm volatile("mret");
}

// // ask each hart to generate timer interrupts.
// void timerinit() {
//   // enable supervisor-mode timer interrupts.
//   w_mie(r_mie() | MIE_STIE);

//   // enable the sstc extension (i.e. stimecmp).
//   w_menvcfg(r_menvcfg() | (1L << 63));

//   // allow supervisor to use stimecmp and time.
//   w_mcounteren(r_mcounteren() | 2);

//   // ask for the very first timer interrupt.
//   w_stimecmp(r_time() + 1000000);
// }
