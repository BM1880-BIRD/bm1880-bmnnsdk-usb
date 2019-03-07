#ifndef REG_BDCAST_H
#define REG_BDCAST_H

#define BD_ENGINE_DESCRIPTOR_NUM      30
#define BD_REG_BYTES                  (BD_ENGINE_DESCRIPTOR_NUM * 4)
#define BDC_ENGINE_CMD_ALIGNED_BIT    8

#define BD_CMD_BASE_ADDR              (BD_ENGINE_BASE_ADDR + 0)
#define BD_CTRL_BASE_ADDR             (BD_ENGINE_BASE_ADDR + 0x100)
#define BD_ENGINE_MAIN_CTRL           (BD_CTRL_BASE_ADDR + 0)
#define BD_ENGINE_DESC_ADDR           (BD_CTRL_BASE_ADDR + 0x4)

//
// BD operations for 168s
//
#define DCR_TYPE_CONV                 0
#define DCR_TYPE_DEPTHWISE_POOL       1
#define DCR_TYPE_FC                   2
#define DCR_TYPE_TENSOR_ARITH         3
#define DCR_TYPE_FC_TYPE_2            4
#define DCR_TYPE_CONV_CORRELATION     5
#define DCR_TYPE_TABLE_LOOKUP         6
#define DCR_TYPE_MD_SUM               7
#define DCR_TYPE_MD_SCALAR            8
#define DCR_TYPE_MD_SFU               9
#define DCR_TYPE_MD_LINEAR            10
#define DCR_TYPE_LMEM_ARRANGE         11
#define DCR_TYPE_DECOMPRESS           12
#define NR_DCR_TYPES                  13

// BD control bits base on BD_CTRL_BASE_ADDR
#define BD_TPU_EN                     0    // TPU Enable bit
#define BD_DES_ADDR_VLD               30   // enable descriptor mode
#define BD_INTR_ENABLE                31   // TIU interrupt global enable

#endif /* REG_BDCAST_H */
