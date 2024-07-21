# riscv-os1
An operating system for the QEMU RISC-V virt machine loosely based on CP/M



## Building

### Prerequisites

These can all be installed via `brew` on macOS.

|package|version|
|:------|:------|
|meson|1.5.0|
|ninja|1.12.1|
|riscv64-elf-binutils|2.42|
|riscv64-elf-gcc|14.1.0|
|riscv64-elf-gdb|15.1|

> [!note]
> If you didn't use `brew`, you might need to change `gcc_base_path` and `arch` in meson-cross-file.txt.



## Running

### Prerequisites

These can all be installed via `brew` on macOS.

| package |version|
|:--------|:--|
| QEMU    |9.0.2|
