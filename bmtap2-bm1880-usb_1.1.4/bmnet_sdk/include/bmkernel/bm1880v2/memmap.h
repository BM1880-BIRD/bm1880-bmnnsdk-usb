#ifndef MEMMAP_H
#define MEMMAP_H

#define LOCAL_MEM_ADDRWIDTH            (15)
#define LOCAL_MEM_START_ADDR           (0x0C000000)
#define LOCAL_MEM_SIZE                 (1 << LOCAL_MEM_ADDRWIDTH)

#define GLOBAL_MEM_START_ADDR           (0x100000000)
#define UART_CTLR_BASE_ADDR             (0x04140000)

#define TDMA_ENGINE_BASE_ADDR          (0x0C100000)
#define TDMA_ENGINE_END_ADDR           (TDMA_ENGINE_BASE_ADDR + 0x1000)

#define TIU_ENGINE_BASE_ADDR           (0x0C101000) //"NPS Register" in memory map?
#define TIU_ENGINE_END_ADDR            (TIU_ENGINE_BASE_ADDR + 0x1000)

#endif /* MEMMAP_H */
