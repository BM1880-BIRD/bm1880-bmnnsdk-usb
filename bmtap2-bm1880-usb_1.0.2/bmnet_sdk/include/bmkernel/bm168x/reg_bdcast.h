#ifndef REG_BDCAST_H
#define REG_BDCAST_H

#define BD_ENGINE_DESCRIPTOR_NUM       24
#define BD_ENGINE_DESCRIPTOR_DMA_NUM   32
#define BDC_ENGINE_CMD_ALIGNED_BIT     8

#define BD_ENGINE_MAIN_CTRL            (BD_ENGINE_BASE_ADDR + 0x00000000)
#define BD_ENGINE_RUN_STATUS           (BD_ENGINE_BASE_ADDR + 0x00000004)
#define BD_ENGINE_CMD_STATUS           (BD_ENGINE_BASE_ADDR + 0x00000008)
#define BD_ENGINE_DDR_INIT             (BD_ENGINE_BASE_ADDR + 0x0000000C)
#define BD_ENGINE_NP_ID                (BD_ENGINE_BASE_ADDR + 0x00000010)
#define BD_ENGINE_CMD_FILE             (BD_ENGINE_BASE_ADDR + 0x00000018) // BM1682 only
#define BD_DCR_BASE_ADDR               (BD_ENGINE_BASE_ADDR + 0x00000020)

/*
 * BD Spec describe cmd register, using index from 1, not from 0
 */
#define BD_CMD_REG1                    0x00
#define BD_CMD_REG2                    0x04
#define BD_CMD_REG3                    0x08
#define BD_CMD_REG4                    0x0c
#define BD_CMD_REG5                    0x10
#define BD_CMD_REG6                    0x14
#define BD_CMD_REG7                    0x18
#define BD_CMD_REG8                    0x1c
#define BD_CMD_REG9                    0x20
#define BD_CMD_REG10                   0x24
#define BD_CMD_REG11                   0x28
#define BD_CMD_REG12                   0x2c
#define BD_CMD_REG13                   0x30
#define BD_CMD_REG14                   0x34
#define BD_CMD_REG15                   0x38
#define BD_CMD_REG16                   0x3c
#define BD_CMD_REG17                   0x40
#define BD_CMD_REG18                   0x44
#define BD_CMD_REG19                   0x48
#define BD_CMD_REG20                   0x4c
#define BD_CMD_REG21                   0x50
#define BD_CMD_REG22                   0x54
#define BD_CMD_REG23                   0x58
#define BD_CMD_REG24                   0x5c

#define BD_CMD_REGI1                   0
#define BD_CMD_REGI2                   1
#define BD_CMD_REGI3                   2
#define BD_CMD_REGI4                   3
#define BD_CMD_REGI5                   4
#define BD_CMD_REGI6                   5
#define BD_CMD_REGI7                   6
#define BD_CMD_REGI8                   7
#define BD_CMD_REGI9                   8
#define BD_CMD_REGI10                  9
#define BD_CMD_REGI11                  10
#define BD_CMD_REGI12                  11
#define BD_CMD_REGI13                  12
#define BD_CMD_REGI14                  13
#define BD_CMD_REGI15                  14
#define BD_CMD_REGI16                  15
#define BD_CMD_REGI17                  16
#define BD_CMD_REGI18                  17
#define BD_CMD_REGI19                  18
#define BD_CMD_REGI20                  19
#define BD_CMD_REGI21                  20
#define BD_CMD_REGI22                  21
#define BD_CMD_REGI23                  22
#define BD_CMD_REGI24                  23

#define DCR_TYPE_CONV                  0
#define DCR_TYPE_CONV_COEFF            1
#define DCR_TYPE_MD_SUM                2
#define DCR_TYPE_MD_LINEAR             3
#define DCR_TYPE_MD_SCALAR             4
#define DCR_TYPE_MD_SFU                5
#define DCR_TYPE_MD_CMP                6
#define DCR_TYPE_POOLING_FWD           7
#define DCR_TYPE_POOLING_BWD           8
#define DCR_TYPE_MATRIX_MULTIPLY       9
#define DCR_TYPE_IMAGE_SUM             10
#define DCR_TYPE_CONV_COEFF_MAC        11
#define DCR_TYPE_LMEM_ARRANGE          12
#define DCR_TYPE_TENSOR_ARITHMETIC     13
#define NR_DCR_TYPES                   14

#define CONV_KERNEL_CH_STRIDE_REG      14
#define CONV_KERNEL_NSTRIDE_REG        13

#define CONV_KERNEL_STRIDE_ENABLE_BIT  25

#define MD_CMP_A_CONST_BIT             22
#define MD_CMP_B_CONST_BIT             21
#define MD_CMP_C_CONST_BIT             20
#define MD_CMP_D_CONST_BIT             19
#define MD_CMP_SKIP_CD_BIT             26
#define MD_CMP_C_PRECISION_BIT         24
#define MD_CMP_D_PRECISION_BIT         23

#define MD_SCALAR_OPMODE_BIT           19  // BM1682 only
#define MD_SCALAR_B_CONST_BIT          21
#define MD_SCALAR_A_CONST_BIT          22
#define MD_SCALAR_B_PRECISION_BIT      23
#define MD_SCALAR_B_ONE_IMAGE_BIT      24
#define MD_SCALAR_STORE_STRIDE_BIT     25
#define MD_SCALAR_RESULT_ADD_BIT       26
#define MD_SCALAR_RESULT_RELU_BIT      31

#define MD_SFU_OPMODE_BIT              22  // BM1682 only
#define MD_SFU_EUCMD_EXP               0x6000000F  // BM1680 only
#define MD_SFU_EUCMD_LNX               0x61000010  // BM1680 only
#define MD_SFU_EUCMD_POWEXP            0x62000011  // BM1680 only
#define MD_SFU_EUCMD_POWN              0x43000000  // BM1680 only
#define MD_SFU_EUCMD_RSQ               0x74000004  // BM1680 only

#define MD_SUM_RELU_BIT                31
#define MD_SUM_RESULT_ADD_BIT          26
#define MD_SUM_STRIDE_STORE_BIT        25

#define MD_LINEAR_RESULT_RELU_BIT      31  // BM1680 only
#define MD_LINEAR_S_CONST_BIT          30
#define MD_LINEAR_B_CONST_BIT          29
#define MD_LINEAR_IS_POWER_AB_BIT      28
#define MD_LINEAR_POWER_ADD_BIT        27  // BM1682 only
#define MD_LINEAR_RESULT_ADD_BIT       26
#define MD_LINEAR_STORE_STRIDE_BIT     25  // BM1680 only
#define MD_LINEAR_EUCMD_MAC            0x4f000002  // BM1680 only
#define MD_LINEAR_EUCMD_ADD_SQR        0x04000001  // BM1680 only
#define MD_LINEAR_EUCMD_SUB_SQR        0x13000001  // BM1680 only

#define BD_DMA_MODE_BIT                0
#define BD_DMA_ENABLE_BIT              1
#define BD_CLEAR_CMD_ID_BIT            2

#define BD_BARRIER_ENABLE_BIT          1
#define BD_USE_MICO_TABLE_BIT          2
#define DCR_NEED_RETURN_BIT            3
#define BD_NOT_ALL_BLOB_SAME_BIT       4
#define BD_DESC_ENABLE_BIT             5
#define BD_EOD_BIT                     7
#define DCR_TYPE_BIT                   8

#endif /* REG_BDCAST_H */
