OUTPUT_ARCH( "riscv" )
ENTRY(cold_boot)

MEMORY {
  ram : ORIGIN = 0x80000000, LENGTH = 1M
}

PHDRS {
  text PT_LOAD;
}

SECTIONS {

  __ram_start = ORIGIN(ram);
  __ram_end = ORIGIN(ram) + LENGTH(ram);

  .text : ALIGN(8) {
    *kernel_boot.S*(.boot);
  } >ram AT>ram :text

  __heap_start = .;

}
