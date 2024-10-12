#!/bin/bash

# 启动 gdb-multiarch，读取预设的gdb配置(.gdbinit)
gdb-multiarch \
  -q -iex "set auto-load safe-path /home/lwb/riscv-os/.gdbinit" \
  -ex "file kernel/kernel"
  
