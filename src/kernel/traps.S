.section .trap

.type trap_handler_0, STT_FUNC
.global trap_handler_0
trap_handler_0:

  /* Save the integer registers on the stack, except sp */
  c.addi16sp sp, -256     /* Must be a multiple of 128 */
  c.sdsp a0, 0(sp)
  c.sdsp a1, 8(sp)
  c.sdsp a2, 16(sp)
  c.sdsp a3, 24(sp)
  c.sdsp a4, 32(sp)
  c.sdsp a5, 40(sp)
  c.sdsp a6, 48(sp)
  c.sdsp a7, 56(sp)
  c.sdsp s0, 64(sp)
  c.sdsp s1, 72(sp)
  c.sdsp s2, 80(sp)
  c.sdsp s3, 88(sp)
  c.sdsp s4, 96(sp)
  c.sdsp s5, 104(sp)
  c.sdsp s6, 112(sp)
  c.sdsp s7, 120(sp)
  c.sdsp s8, 128(sp)
  c.sdsp s9, 136(sp)
  c.sdsp s10, 144(sp)
  c.sdsp s11, 152(sp)
  c.sdsp t0, 160(sp)
  c.sdsp t1, 168(sp)
  c.sdsp t2, 176(sp)
  c.sdsp t3, 184(sp)
  c.sdsp t4, 192(sp)
  c.sdsp t5, 200(sp)
  c.sdsp t6, 208(sp)
  c.sdsp tp, 216(sp)
  c.sdsp gp, 224(sp)
  c.sdsp ra, 232(sp)

  /* TODO: Save the f registers and fcsr if they're enabled */

  call trap_handler

  /* TODO: Restore the f registers and fcsr if they're enabled */

  /* Restore the integer registers from the stack */
  c.ldsp a0, 0(sp)
  c.ldsp a1, 8(sp)
  c.ldsp a2, 16(sp)
  c.ldsp a3, 24(sp)
  c.ldsp a4, 32(sp)
  c.ldsp a5, 40(sp)
  c.ldsp a6, 48(sp)
  c.ldsp a7, 56(sp)
  c.ldsp s0, 64(sp)
  c.ldsp s1, 72(sp)
  c.ldsp s2, 80(sp)
  c.ldsp s3, 88(sp)
  c.ldsp s4, 96(sp)
  c.ldsp s5, 104(sp)
  c.ldsp s6, 112(sp)
  c.ldsp s7, 120(sp)
  c.ldsp s8, 128(sp)
  c.ldsp s9, 136(sp)
  c.ldsp s10, 144(sp)
  c.ldsp s11, 152(sp)
  c.ldsp t0, 160(sp)
  c.ldsp t1, 168(sp)
  c.ldsp t2, 176(sp)
  c.ldsp t3, 184(sp)
  c.ldsp t4, 192(sp)
  c.ldsp t5, 200(sp)
  c.ldsp t6, 208(sp)
  c.ldsp tp, 216(sp)
  c.ldsp gp, 224(sp)
  c.ldsp ra, 232(sp)

  /* Restore sp */
  c.addi16sp sp, 256

  /* Return */
  mret
