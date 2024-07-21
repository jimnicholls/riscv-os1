.section .boot

.type cold_boot, STT_FUNC
.global cold_boot
cold_boot:

  csrci mstatus, 10
1:
  wfi
  j 1b
