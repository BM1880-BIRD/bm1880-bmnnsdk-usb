#ifndef REG_CDMA_H
#define REG_CDMA_H

#define CDMA_ENGINE_DESCRIPTOR_NUM      9
#define CDMA_ENGINE_DESCRIPTOR_DMA_NUM  16

#define CDMA_ENGINE_MAIN_CTRL          (CDMA_ENGINE_BASE_ADDR + 0x800)
#define CDMA_ENGINE_CMD_STATUS         (CDMA_ENGINE_BASE_ADDR + 0x814)
#define CDMA_ENGINE_DDR_INIT           (CDMA_ENGINE_BASE_ADDR + 0x89c)
#define CDMA_DCR_BASE_ADDR             (CDMA_ENGINE_BASE_ADDR + 0x00000878)
#define CDMA_MSG_BASE_ADDR             (CDMA_ENGINE_BASE_ADDR + 0x00000928)

// HDMA is host side CDMA
// FIXME: BASE ADDRESS is allocated runtime on HOST, can do this way
#define HDMA_ENGINE_BASE_ADDR          0
#define HDMA_ENGINE_MAIN_CTRL          (HDMA_ENGINE_BASE_ADDR + 0x800)
#define HDMA_DCR_BASE_ADDR             (HDMA_ENGINE_BASE_ADDR + 0x00000878)
#define HDMA_MSG_BASE_ADDR             (HDMA_ENGINE_BASE_ADDR + 0x00000928)

#define HOST_MINIMAC_BASE              0x8000

/* Full Register definitions */
#define REG_BM1680_CHL_CTRL                 0x800
#define REG_BM1680_CHL_CHIP_MODE            0x804
#define REG_BM1680_CHL_INT_MASK             0x808
#define REG_BM1680_CHL_INT_STAT             0x80C
#define REG_BM1680_CHL_GEN_STAT             0x810
#define REG_BM1680_CHL_SYNC_STAT            0x814
#define REG_BM1680_CHL_UP_HDR_IN            0x818
#define REG_BM1680_CHL_DN_HDR_IN            0x838
#define REG_BM1680_CHL_MAN_HDR_OUT          0x858
#define REG_BM1680_CHL_CMD_ACCP_0           0x878
#define REG_BM1680_CHL_CMD_ACCP_1           0x87C
#define REG_BM1680_CHL_CMD_ACCP_2           0x880
#define REG_BM1680_CHL_CMD_ACCP_3           0x884
#define REG_BM1680_CHL_CMD_ACCP_4           0x888
#define REG_BM1680_CHL_CMD_ACCP_5           0x88C
#define REG_BM1680_CHL_CMD_ACCP_6           0x890
#define REG_BM1680_CHL_CMD_ACCP_7           0x894
#define REG_BM1680_CHL_CMD_ACCP_8           0x898
#define REG_BM1680_CHL_CMD_ACCP_9           0x89C
#define REG_BM1680_CHL_CMD_ACCP_10          0x8A0
#define REG_BM1680_CHL_MBX_REG_0            0x8A4
#define REG_BM1680_CHL_MBX_REG_1            0x8A8
#define REG_BM1680_CHL_MBX_REG_2            0x8AC
#define REG_BM1680_CHL_MBX_REG_3            0x8B0
#define REG_BM1680_CHL_MBX_REG_4            0x8B4
#define REG_BM1680_CHL_MBX_REG_5            0x8B8
#define REG_BM1680_CHL_MBX_REG_6            0x8BC
#define REG_BM1680_CHL_MBX_REG_7            0x8C0
#define REG_BM1680_CHL_MBX_REG_8            0x8C4
#define REG_BM1680_CHL_MBX_REG_9            0x8C8
#define REG_BM1680_CHL_MBX_REG_10           0x8CC
#define REG_BM1680_CHL_MBX_REG_11           0x8D0
#define REG_BM1680_CHL_MBX_REG_12           0x8D4
#define REG_BM1680_CHL_MBX_REG_13           0x8D8
#define REG_BM1680_CHL_MBX_REG_14           0x8DC
#define REG_BM1680_CHL_MBX_REG_15           0x8E0
#define REG_BM1680_CHL_MBX_REG_16           0x8E4
#define REG_BM1680_CHL_MBX_REG_17           0x8E8
#define REG_BM1680_CHL_MBX_REG_18           0x8EC
#define REG_BM1680_CHL_MBX_REG_19           0x8F0
#define REG_BM1680_CHL_MBX_REG_20           0x8F4
#define REG_BM1680_CHL_MBX_REG_21           0x8F8
#define REG_BM1680_CHL_MBX_REG_22           0x8FC
#define REG_BM1680_CHL_MBX_REG_23           0x900
#define REG_BM1680_CHL_MBX_REG_24           0x904
#define REG_BM1680_CHL_MBX_REG_25           0x908
#define REG_BM1680_CHL_MBX_REG_26           0x90C
#define REG_BM1680_CHL_MBX_REG_27           0x910
#define REG_BM1680_CHL_MBX_REG_28           0x914
#define REG_BM1680_CHL_MBX_REG_29           0x918
#define REG_BM1680_CHL_CHIP_IDX             0x91C
#define REG_BM1680_CHL_CHIP_IDX_MAX         0x920
#define REG_BM1680_CHL_CHIP_INF             0x924
#define REG_BM1680_CHL_MSG_IN_BASE_L        0x928
#define REG_BM1680_CHL_MSG_IN_BASE_H_SIZE   0x92C
#define REG_BM1680_CHL_MSG_IN_AP            0x930
#define REG_BM1680_CHL_MSG_OUT_AP           0x934
#define REG_BM1680_CHL_MSG_OUT_BASE_L       0x938
#define REG_BM1680_CHL_MSG_OUT_BASE_H_SIZE  0x93C
#define REG_BM1680_CHL_CHIP_FORCE_IDX       0x940
#define REG_BM1680_CHL_DES_BASE_L           0x944
#define REG_BM1680_CHL_DES_BASE_H           0x948
#define REG_BM1680_CHL_MSG_Q_TIMEOUT_THR    0x94C
#define REG_BM1680_CHL_SOFT_RESET           0x950
#define REG_BM1680_CHL_FIFO_STAT            0x954
#define REG_BM1680_CHL_MAC_LINK_STAT_LO     0x958
#define REG_BM1680_CHL_MAC_LINK_STAT_HI     0x95C
#define REG_BM1680_CHL_MAC_CRC_ERR_0_LO     0x960
#define REG_BM1680_CHL_MAC_CRC_ERR_0_HI     0x964
#define REG_BM1680_CHL_MAC_CRC_ERR_1_LO     0x968
#define REG_BM1680_CHL_MAC_CRC_ERR_1_HI     0x96C
#define REG_BM1680_CHL_MAC_RDY              0x970
#define REG_BM1680_CHL_FORCE_IN_MSG_WP      0x974
#define REG_BM1680_CHL_FORCE_OUT_MSG_RP     0x978
#define REG_BM1680_CHL_CHIP_ID              0x97C
#define REG_BM1680_CHL_TX_TO_THRES          0x980
#define REG_BM1680_CHL_RESP_TO_THRES        0x984
#define REG_BM1680_CHL_MST_TO_THRES         0x988
#define REG_BM1680_CHL_DES_TO_THRES         0x98C
#define REG_BM1680_CHL_CUR_DES_ADDR_LO      0x990
#define REG_BM1680_CHL_CUR_DES_ADDR_HI      0x994
#define REG_BM1680_CHL_INT_STAT_RAW         0x998

#define REG_BM1680_CHL_MSG_2_Q_CNT          0xA00
#define REG_BM1680_CHL_MSG_RESP_CNT         0xA04
#define REG_BM1680_CHL_MSG_RTN_DATA_CNT     0xA08
#define REG_BM1680_CHL_MSG_FROM_Q_CNT       0xA0C
#define REG_BM1680_CHL_MSG_RX_CNT           0xA10

#define BM1680_CHL_CTRL_DMA_EN                  (0x01 << 0)
#define BM1680_CHL_CTRL_DMA_MODE_SEL            (0x01 << 1)
#define BM1680_CHL_CTRL_SYNC_ID_RST             (0x01 << 2)
#define BM1680_CHL_CTRL_INT_EN                 (0x01 << 3)
#define BM1680_CHL_CTRL_RSVD_0                  (0x01 << 4)
#define BM1680_CHL_CTRL_CHIP_BYPASS             (0x01 << 5)

#define BM1680_CHL_MODE_TASK_STEP_MODE          (0x01 << 0)
#define BM1680_CHL_MODE_MSG_EN                  (0x01 << 1)
#define BM1680_CHL_MODE_TXDMA_OSTD_EN           (0x01 << 2)
#define BM1680_CHL_MODE_RXDMA_OSTD_EN           (0x01 << 3)

#define BM1680_CHL_MAC_UP_TX_RDY                (0x01 << 0)
#define BM1680_CHL_MAC_UP_RX_RDY                (0x01 << 1)
#define BM1680_CHL_MAC_DOWN_TX_RDY              (0x01 << 2)
#define BM1680_CHL_MAC_DOWN_RX_RDY              (0x01 << 3)

/* attention for Write-1-clear or Write-0-clear */
#define BM1680_CHL_INT_DESC_STAT_UPDATED        (0x01 << 0)
#define BM1680_CHL_INT_INVALID_DESC             (0x01 << 1)
#define BM1680_CHL_INT_CMD_FIFO_OVERFLOW        (0x01 << 2)
#define BM1680_CHL_INT_CMD_FIFO_EMPTY           (0x01 << 3)
#define BM1680_CHL_INT_MSG_IN_FULL              (0x01 << 4)
#define BM1680_CHL_INT_MSG_IN_NOT_EMPTY         (0x01 << 5)
#define BM1680_CHL_INT_MSG_OUT_EMPTY            (0x01 << 6)
#define BM1680_CHL_INT_MSG_OUT_NOT_FULL         (0x01 << 7)
#define BM1680_CHL_INT_MSG_PKT_RECV             (0x01 << 8)
#define BM1680_CHL_INT_DATA_PKT_RECV            (0x01 << 9)
#define BM1680_CHL_INT_MSG_IN_OVERFLOW          (0x01 << 10)
#define BM1680_CHL_INT_MSG_OUT_INVALID          (0x01 << 11)
#define BM1680_CHL_INT_MSG_RX_DMA_ERR           (0x01 << 12)
#define BM1680_CHL_INT_MSG_TX_DMA_ERR           (0x01 << 13)
#define BM1680_CHL_INT_DMA_RX_DMA_ERR           (0x01 << 14)
#define BM1680_CHL_INT_DMA_TX_DMA_ERR           (0x01 << 15)
#define BM1680_CHL_INT_MSG_2_Q_RECV             (0x01 << 16)
#define BM1680_CHL_INT_RESP_MSG_2_Q_RECV        (0x01 << 17)
#define BM1680_CHL_INT_RESP_MSG_2_MEM_RECV_H    (0x01 << 18)
#define BM1680_CHL_INT_WRITE_MSG_RECV_C         (0x01 << 18)
#define BM1680_CHL_INT_RDATA_MSG_2_Q_RECV       (0x01 << 19)
#define BM1680_CHL_INT_RDATA_MSG_2_MEM_RECV_H   (0x01 << 20)
#define BM1680_CHL_INT_READ_MSG_RECV_C          (0x01 << 20)
#define BM1680_CHL_INT_CRC0_ERR_DET             (0x01 << 21)
#define BM1680_CHL_INT_CRC1_ERR_DET             (0x01 << 22)
#define BM1680_CHL_INT_MAC0_OVF_DET             (0x01 << 23)
#define BM1680_CHL_INT_MAC1_OVF_DET             (0x01 << 24)
#define BM1680_CHL_INT_MSG_TO                   (0x01 << 25)
#define BM1680_CHL_INT_MSG_RESP_TO              (0x01 << 26)
#define BM1680_CHL_INT_MSG_TX_Q_TO              (0x01 << 27)
#define BM1680_CHL_INT_DESC_TO                  (0x01 << 28)

#define BM1680_CHL_INT_MSG_ERR_GROUP            BM1680_CHL_INT_MSG_IN_FULL  \
                                                | BM1680_CHL_INT_MSG_IN_OVERFLOW  \
                                                | BM1680_CHL_INT_MSG_OUT_INVALID  \
                                                | BM1680_CHL_INT_MSG_TO  \
                                                | BM1680_CHL_INT_MSG_TX_DMA_ERR  \
                                                | BM1680_CHL_INT_MSG_TX_Q_TO  \
                                                | BM1680_CHL_INT_MSG_RESP_TO  \
                                                | BM1680_CHL_INT_MSG_RX_DMA_ERR  \
                                                | BM1680_CHL_INT_CRC0_ERR_DET  \
                                                | BM1680_CHL_INT_CRC1_ERR_DET  \
                                                | BM1680_CHL_INT_MAC0_OVF_DET  \
                                                | BM1680_CHL_INT_MAC1_OVF_DET

/*#define BM1680_CHL_INT_DATA_PKT_RECV            (0x01 << 9)*/

#define BM1680_CHL_INT_DMA_ERR_GROUP            BM1680_CHL_INT_INVALID_DESC  \
                                                | BM1680_CHL_INT_CMD_FIFO_OVERFLOW  \
                                                | BM1680_CHL_INT_DMA_RX_DMA_ERR  \
                                                | BM1680_CHL_INT_DMA_TX_DMA_ERR  \
                                                | BM1680_CHL_INT_DESC_TO  \
                                                | BM1680_CHL_INT_CRC0_ERR_DET  \
                                                | BM1680_CHL_INT_CRC1_ERR_DET  \
                                                | BM1680_CHL_INT_MAC0_OVF_DET  \
                                                | BM1680_CHL_INT_MAC1_OVF_DET

#define BM1680_CHL_INT_DESC_GROUP               BM1680_CHL_INT_DESC_STAT_UPDATED \
                                                | BM1680_CHL_INT_DMA_ERR_GROUP
                                                //FIXME: do not enable desc fifo empty int for now. wait for new working flow
                                                //| BM1680_CHL_INT_CMD_FIFO_EMPTY

#define BM1680_CHL_INT_MSG_GROUP                BM1680_CHL_INT_MSG_PKT_RECV  \
                                                | BM1680_CHL_INT_MSG_2_Q_RECV  \
                                                | BM1680_CHL_INT_RESP_MSG_2_Q_RECV  \
                                                | BM1680_CHL_INT_RESP_MSG_2_MEM_RECV_H  \
                                                | BM1680_CHL_INT_WRITE_MSG_RECV_C  \
                                                | BM1680_CHL_INT_RDATA_MSG_2_Q_RECV  \
                                                | BM1680_CHL_INT_RDATA_MSG_2_MEM_RECV_H  \
                                                | BM1680_CHL_INT_READ_MSG_RECV_C  \
                                                | BM1680_CHL_INT_MSG_ERR_GROUP

#define BM1680_CHL_INT_DESC_STAT_UPDATED_MASK   (0x01 << 0)
#define BM1680_CHL_INT_INVALID_DESC_MASK        (0x01 << 1)
#define BM1680_CHL_INT_CMD_FIFO_OVERFLOW_MASK   (0x01 << 2)
#define BM1680_CHL_INT_CMD_FIFO_EMPTY_MASK      (0x01 << 3)
#define BM1680_CHL_INT_MSG_IN_FULL_MASK_MASK    (0x01 << 4)
#define BM1680_CHL_INT_MSG_IN_NOT_EMPTY_MASK    (0x01 << 5)
#define BM1680_CHL_INT_MSG_OUT_EMPTY_MASK       (0x01 << 6)
#define BM1680_CHL_INT_MSG_OUT_NOT_FULL_MASK    (0x01 << 7)
#define BM1680_CHL_INT_DOWN_STREAM_PKT_RECV_MASK (0x01 << 8)
#define BM1680_CHL_INT_UP_STREAM_PKT_RECV_MASK  (0x01 << 9)
#define BM1680_CHL_INT_MSG_IN_OVERFLOW_MASK     (0x01 << 10)

#define BM1680_CHL_SOFT_RESET_EN                (0x01 << 0)
#define BM1680_CHL_NODECHIP_CHAIN_SOFT_RESET_EN (0x01 << 1)
#define BM1680_CHL_MISC_SOFT_RESET_EN           (0x01 << 2)

#define CDMA_CMD_ACCP0                0
#define CDMA_CMD_ACCP1                4
#define CDMA_CMD_ACCP2                8
#define CDMA_CMD_ACCP3                12
#define CDMA_CMD_ACCP4                16
#define CDMA_CMD_ACCP5                20
#define CDMA_CMD_ACCP6                24
#define CDMA_CMD_ACCP7                28
#define CDMA_CMD_ACCP8                32

#define CDMA_CMD_ACCPI0               0
#define CDMA_CMD_ACCPI1               1
#define CDMA_CMD_ACCPI2               2
#define CDMA_CMD_ACCPI3               3
#define CDMA_CMD_ACCPI4               4
#define CDMA_CMD_ACCPI5               5
#define CDMA_CMD_ACCPI6               6
#define CDMA_CMD_ACCPI7               7
#define CDMA_CMD_ACCPI8               8

#define CDMA_CMD_ACCP0_DEFAULT         0x0
#define CDMA_CMD_ACCP1_DEFAULT         0x1
#define CDMA_CMD_ACCP2_DEFAULT         0x0
#define CDMA_CMD_ACCP3_DEFAULT         0x0
#define CDMA_CMD_ACCP4_DEFAULT         0x0
#define CDMA_CMD_ACCP5_DEFAULT         0x0
#define CDMA_CMD_ACCP6_DEFAULT         0x0
#define CDMA_CMD_ACCP7_DEFAULT         0x0
#define CDMA_CMD_ACCP8_DEFAULT         0x0

#define CDMA_LOCALMEM_UNI              0
#define CDMA_LOCALMEM_UNI_BROADCAST    1
#define CDMA_BROADCAST                 2
#define CDMA_CONCAT                    3
#define CDMA_HOST_BROADCAST            4
#define CDMA_HOST_DISTRIBUTE           5
#define CDMA_HOST_CONCAT               6
#define CDMA_HOST_SINGLE_READ          7

#define CDMA_CLEAR_CMD_ID_BIT          2
#define CDMA_DMA_MODE_BIT              1
#define CDMA_DMA_ENABLE_BIT            0

#define CDMA_ENABLE_BIT                0
#define CDMA_EOD_BIT                   2
#define CMDA_INT_EN_BIT                3
#define CDMA_BARRIER_ENABLE_BIT        4
#define CDMA_STRIDE_ENABLE_BIT         5
#define CDMA_PLAIN_DATA_BIT            6
#define CDMA_OP_CODE_SHIFT             8
#define CDMA_SCATTERLIST_BIT           11  // host only
#define CDMA_SYNC_MODE_BIT             12  // concat & plain data only

#define CDMA_DESCRIPTOR_BIT            1

#define CDMA_MSG_REG_NUM               6
#define CDMA_MSG_IN_BASE_L             (0x00)
#define CDMA_MSG_IN_BASE_H_SIZE        (0x04)
#define CDMA_MSG_IN_RP_WP              (0x08)
#define CDMA_MSG_OUT_RP_WP             (0x0c)
#define CDMA_MSG_OUT_BASE_L            (0x10)
#define CDMA_MSG_OUT_BASE_H_SIZE       (0x14)

#endif /* REG_CDMA_H */
