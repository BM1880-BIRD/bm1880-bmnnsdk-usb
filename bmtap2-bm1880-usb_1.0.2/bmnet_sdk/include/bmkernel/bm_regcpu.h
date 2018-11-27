/*
 * Copyright Bitmain Technologies Inc.
 *
 * Written by:
 *   Wanwei CAI <wanwei.cai@bitmain.com>
 * Created Time: 2017-06-29 15:33
 */

#ifndef _BM_REG_CPU_H
#define _BM_REG_CPU_H

#include <bmkernel/bm_kernel.h>

#define CPU_ENGINE_DESCRIPTOR_NUM     56
#define CPU_ENGINE_DESCRIPTOR_DMA_NUM CPU_ENGINE_DESCRIPTOR_NUM
#define CPU_ENGINE_BYTES              (CPU_ENGINE_DESCRIPTOR_NUM*sizeof(u32))

#define CPU_CMD_ACCPI0                0
#define CPU_CMD_ACCPI1                1
#define CPU_CMD_ACCPI2                2
#define CPU_CMD_ACCPI3                3
#define CPU_CMD_ACCPI4                4
/* CPU_CMD_ACCPI5 ~ CPU_CMD_ACCPI63
defined here if needed */

#define CPU_ACCPI0_OP_BIT             0
#define CPU_ACCPI1_BD_CMDID_BIT       0
#define CPU_ACCPI1_CPU_CMDID_BIT      16
#define CPU_ACCPI2_GDMA_CMDID_BIT     0
#define CPU_ACCPI2_CDMA_CMDID_BIT     16
#define CPU_ACCPI3_NEXT_BD_ADDR_BIT   0
#define CPU_ACCPI4_NEXT_GDMA_ADDR_BIT 0
#define CPU_ACCPI5_NEXT_CDMA_ADDR_BIT 0

typedef enum {
  CPU_OP_SYNC = 2,
  CPU_OP_INST = 3,
  CPU_OP_END
} CPU_OP;

// CPU common structure
typedef struct {
  u32 regs[CPU_ENGINE_DESCRIPTOR_NUM];
} bmk_cpu_desc_t;

// CPU_OP_SYNC structure
typedef struct {
  u32 op_type;  // CPU_CMD_ACCPI0
  u32 num_bd;   // CPU_CMD_ACCPI1
  u32 num_gdma; // CPU_CMD_ACCPI2
  u32 offset_bd; // CPU_CMD_ACCPI3
  u32 offset_gdma; // CPU_CMD_ACCPI4
  u32 reserved[2]; // CPU_CMD_ACCPI5-CPU_CMD_ACCPI6
  char str[(CPU_ENGINE_DESCRIPTOR_NUM - 7) * sizeof(u32)];
} __attribute__((packed)) bmk_cpu_sync_desc_t;

// CPU_OP_INST structure
typedef struct {
  u32 op_type;  // CPU_CMD_ACCPI0
  u32 num_bd;   // CPU_CMD_ACCPI1
  u32 num_gdma; // CPU_CMD_ACCPI2
  u32 offset_bd; // CPU_CMD_ACCPI3
  u32 offset_gdma; // CPU_CMD_ACCPI4
  u32 reserved[2]; // CPU_CMD_ACCPI5-CPU_CMD_ACCPI6
  char lib_name[4*sizeof(u32)]; // CPU_CMD_ACCPI7~CPU_CMD_ACCPI10
  u32 param_size;  //CPU_CMD_ACCPI11
  u8  param[(CPU_ENGINE_DESCRIPTOR_NUM - 12) * sizeof(u32)];
} __attribute__((packed)) bmk_cpu_inst_desc_t;

#endif
