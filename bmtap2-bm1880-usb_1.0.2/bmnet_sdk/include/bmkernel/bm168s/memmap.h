#ifndef MEMMAP_H
#define MEMMAP_H

#define LOCAL_MEM_ADDRWIDTH            19
#define LOCAL_MEM_START_ADDR           0x8000000
#define LOCAL_MEM_SIZE                 (512 * 1024)

#define L2_SRAM_START_ADDR             0x10000000
#define L2_SRAM_SIZE                   (4 * 1024 * 1024)

#define GLOBAL_MEM_START_ADDR_ARM      0x80000000
#define GLOBAL_MEM_START_ADDR          0x200000000

#define UART_CTLR_BASE_ADDR            0x50118000

#define GDMA_ENGINE_BASE_ADDR          0x58000000
#define GDMA_ENGINE_END_ADDR           (GDMA_ENGINE_BASE_ADDR + 0x1000)
#define BD_ENGINE_BASE_ADDR            0x58001000
#define BD_ENGINE_END_ADDR             (BD_ENGINE_BASE_ADDR + 0x1000)

#endif /* MEMMAP_H */
