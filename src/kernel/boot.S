.section .boot

.type cold_boot, STT_FUNC
.global cold_boot
cold_boot:

  /* Set $sp to the end of ram */
  la sp, __ram_end

  /* Set $gp to the start of the heap */
  .option push
  .option norelax
  la gp, __heap_start
  .option pop

  /* Set the trap handler */
  la t0, trap_handler_0
  csrw mtvec, t0

  /* Ensure interrupts are disabled */
  csrci mstatus, 10

  /* Don't delegate anything to S-mode because there is nothing there. */
  csrw medeleg, zero
  csrw mideleg, zero

  /* Print the boot message */
  li t0, 0x10000000
  la t1, boot_msg
  j 2f
1:
  sb t2, 0(t0)
  c.addi t1, 1
2:
  lb t2, 0(t1)
  bne t2, zero, 1b

  /* Clear the BSS section */
  la t0, __bss_start
  la t1, __bss_end
1:
  sw zero, (t0)
  c.addi t0, 4
  bltu t0, t1, 1b

  /* The linker script puts kmain immediately after this. */


.section .rodata

.global g_ram_end
g_ram_end: .dword __ram_end

.global boot_msg
boot_msg: .asciz "Booting...\n"
