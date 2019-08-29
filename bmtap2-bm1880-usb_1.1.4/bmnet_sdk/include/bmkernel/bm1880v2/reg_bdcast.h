#ifndef REG_BDCAST_H
#define REG_BDCAST_H

#define BD_ENGINE_DESCRIPTOR_NUM      28
#define BD_REG_BYTES                  (BD_ENGINE_DESCRIPTOR_NUM * 4)
#define BDC_ENGINE_CMD_ALIGNED_BIT    8

#define BD_CMD_BASE_ADDR              (TIU_ENGINE_BASE_ADDR + 0)
#define BD_CTRL_BASE_ADDR             (TIU_ENGINE_BASE_ADDR + 0x100)
#define BD_ENGINE_MAIN_CTRL           (TIU_ENGINE_BASE_ADDR + 0)
#define BD_ENGINE_DESC_ADDR           (TIU_ENGINE_BASE_ADDR + 0x4)

//
// BD operations for BIRD
//
#define DCR_TYPE_CONV_FIX8B           0
#define DCR_TYPE_DEPTHWISE_POOL_FIX8B 1
#define DCR_TYPE_FC_FIX8B             2
#define DCR_TYPE_TENSOR_ARITH_FIX8B   3
#define DCR_TYPE_FC_TYPE_2_FIX8B      4

// BD control bits base on BD_CTRL_BASE_ADDR
#define BD_TPU_EN                     0    // TPU Enable bit
#define BD_LANE_NUM                   22   // Lane number bit[29:22]
#define BD_DES_ADDR_VLD               30   // enable descriptor mode
#define BD_INTR_ENABLE                31   // TIU interrupt global enable

#endif /* REG_BDCAST_H */
