#ifndef REG_GDMA_H
#define REG_GDMA_H

#define  GDMA_NORMAL                   0
#define  GDMA_TRANSPOSE                1
#define  GDMA_LRN_SHIFT                2
#define  GDMA_FORMAT_CONVERSION        3
#define  GDMA_CONSTANT                 4

#define  GDMA_SYSTEM_DATA_NEURON       0
#define  GDMA_SYSTEM_DATA_MATRIX       1

#define  GDMA_TYPE_f32           0
#define  GDMA_TYPE_f16           1
#define  GDMA_TYPE_i32           2
#define  GDMA_TYPE_i16           3
#define  GDMA_TYPE_i8            4
#define  GDMA_TYPE_i4            5
#define  GDMA_TYPE_i2            6
#define  GDMA_TYPE_i1            7
#define  LAST_GDMA_TYPE_i1       8

#define  GDMA_DIR_S2L            0
#define  GDMA_DIR_L2S            1
#define  GDMA_DIR_S2S            2
#define  GDMA_DIR_L2L            3

//offset
#define  GDMA_CMD_ACCP0          0
#define  GDMA_CMD_ACCP1          4
#define  GDMA_CMD_ACCP2          8
#define  GDMA_CMD_ACCP3          12
#define  GDMA_CMD_ACCP4          16
#define  GDMA_CMD_ACCP5          20
#define  GDMA_CMD_ACCP6          24
#define  GDMA_CMD_ACCP7          28
#define  GDMA_CMD_ACCP8          32
#define  GDMA_CMD_ACCP9          36
#define  GDMA_CMD_ACCP10         40
#define  GDMA_CMD_ACCP11         44
#define  GDMA_CMD_ACCP12         48
#define  GDMA_CMD_ACCP13         52
#define  GDMA_CMD_ACCP14         56

//index
#define  GDMA_CMD_ACCPI0          0
#define  GDMA_ACCPI0_CMDID2_BIT         16
#define  GDMA_ACCPI0_HOLD_VALUE_BIT     12
#define  GDMA_ACCPI0_COMMON_MODE_BIT    10
#define  GDMA_ACCPI0_BDCAST_ENABLE_BIT  8
#define  GDMA_ACCPI0_DIRECTION_BIT      6
#define  GDMA_ACCPI0_ST_ENABLE_BIT      5
#define  GDMA_ACCPI0_BARRIER_ENABLE_BIT 4
#define  GDMA_ACCPI0_INTERRUPT_BIT      3
#define  GDMA_ACCPI0_EOD_BIT            2
#define  GDMA_ACCPI0_COMMAND_BIT        1
#define  GDMA_ACCPI0_CMD_VALID_BIT      0


#define  GDMA_CMD_ACCPI1          1
#define  GDMA_ACCPI1_CMDID0_BIT         16
#define  GDMA_ACCPI1_CHW_SHARE_BIT      14
#define  GDMA_ACCPI1_LRN_DIRECTION_BIT  13
#define  GDMA_ACCPI1_LRN_STEP_BIT       9
#define  GDMA_ACCPI1_DATA_IS_MATRIX     8
#define  GDMA_ACCPI1_SRC_FMT_BIT        5
#define  GDMA_ACCPI1_DST_FMT_BIT        3
#define  GDMA_ACCPI1_SF_BIT             0
#define  GDMA_SF_TP_VALUE               0
#define  GDMA_SF_LRN_VALUE              2
#define  GDMA_SF_FMTCOVERT_VALUE        3
#define  GDMA_SF_CONS_VALUE             4
#define  GDMA_SF_CWTRANS_VALUE          5
#define  MASK_SHARE_CHW                 ~(1<<GDMA_ACCPI1_CHW_SHARE_BIT)
#define  MASK_LRN_STEP_BIT              ~(1<<GDMA_ACCPI1_LRN_STEP_BIT)

#define  GDMA_CMD_ACCPI2                2
#define  GDMA_ACCPI2_CMDID3_BIT         16

#define  GDMA_CMD_ACCPI3                3
#define  GDMA_CMD_ACCPI4                4
#define  GDMA_ACCPI4_DST_C_ST_BIT       16
#define  GDMA_ACCPI4_DST_H_ST_BIT       0

#define  GDMA_CMD_ACCPI5                5
#define  GDMA_ACCPI5_DST_N_ST_BIT       0

#define  GDMA_CMD_ACCPI6                6
#define  GDMA_ACCPI6_SRC_C_ST_BIT       16
#define  GDMA_ACCPI6_SRC_H_ST_BIT       0

#define  GDMA_CMD_ACCPI7                7
#define  GDMA_ACCPI7_SRC_N_ST_BIT       0

#define  GDMA_CMD_ACCPI8                8
#define  GDMA_ACCPI8_SRC_C_BIT          16
#define  GDMA_ACCPI8_DST_C_BIT          0

#define  GDMA_CMD_ACCPI9                9
#define  GDMA_ACCPI9_DST_H_BIT          16
#define  GDMA_ACCPI9_DST_W_BIT          0

#define  GDMA_CMD_ACCPI10               10
#define  GDMA_ACCPI10_SRC_H_BIT         16
#define  GDMA_ACCPI10_SRC_W_BIT         0

#define  GDMA_CMD_ACCPI11               11
#define  GDMA_CMD_ACCPI12               12
#define  GDMA_CMD_ACCPI13               13
#define  GDMA_CMD_ACCPI14               14
#define  GDMA_ACCPI14_DST_C_ST_BIT      16
#define  GDMA_ACCPI14_SRC_C_ST_BIT      0


#define  GDMA_CMD_ACCP0_DEFAULT   0x00000
#define  GDMA_CMD_ACCP1_DEFAULT   ((1 << GDMA_ACCPI1_LRN_STEP_BIT) | (1 << GDMA_ACCPI1_CHW_SHARE_BIT) | (4 << GDMA_ACCPI1_SRC_FMT_BIT) | (1 << GDMA_ACCPI1_DST_FMT_BIT))
#define  GDMA_CMD_ACCP2_DEFAULT   0x0
#define  GDMA_CMD_ACCP3_DEFAULT   0x0
#define  GDMA_CMD_ACCP4_DEFAULT   0x0
#define  GDMA_CMD_ACCP5_DEFAULT   0x0
#define  GDMA_CMD_ACCP6_DEFAULT   0x0
#define  GDMA_CMD_ACCP7_DEFAULT   0x0
#define  GDMA_CMD_ACCP8_DEFAULT   0x10001
#define  GDMA_CMD_ACCP9_DEFAULT   0x10001
#define  GDMA_CMD_ACCP10_DEFAULT  0x10001
#define  GDMA_CMD_ACCP11_DEFAULT  0x00000
#define  GDMA_CMD_ACCP12_DEFAULT  0x00000
#define  GDMA_CMD_ACCP13_DEFAULT  0x00001
#define  GDMA_CMD_ACCP14_DEFAULT  0x00000

#define GDMA_ENGINE_MAIN_CTRL          (GDMA_ENGINE_BASE_ADDR + 0x0)
#define GDMA_ENGINE_DDR_INIT           (GDMA_ENGINE_BASE_ADDR + 0x4)
#define GDMA_ENGINE_INT_MASK           (GDMA_ENGINE_BASE_ADDR + 0x8)
#define GDMA_ENGINE_CMD_STATUS         (GDMA_ENGINE_BASE_ADDR + 0xC)
#define GDMA_CMD_BASE_ADDR             (GDMA_ENGINE_BASE_ADDR + 0x00000010)

//#define GDMA_ENIGNE_COMMAND_NUM        15
//#define GDMA_ENIGNE_COMMAND_NUM_FIX8B        32
#define GDMA_ENGINE_DESCRIPTOR_NUM    16
#define GDMA_ENGINE_CMD_ALIGNED_BIT    6

// DMA_CTRL bits base on GDMA_ENGINE_MAIN_CTRL
#define GDMA_CLEAR_CMD_ID_BIT          2
#define GDMA_DMA_MODE_BIT              1
#define GDMA_DMA_ENABLE_BIT            0



//This function only supports the following condition
//localmem2tensor or tensor2localmem
//The source and dst shares the the same format
//Data is 32 bit
//no stride
//We use it in the forward_cpu backward_cpu
static inline int get_index_data_format(int size)
{
  if (size == 1) {
    return GDMA_TYPE_i1;
  } else if (size <= 16) {
    return GDMA_TYPE_i4;
  } else if (size <= 256){
    return GDMA_TYPE_i8;
  } else {
	return GDMA_TYPE_i16;
  }
}
#define LRN_LEFT_SHIFT  0
#define LRN_RIGHT_SHIFT 1

#endif /* REG_GDMA_H */
