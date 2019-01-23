#ifndef MEMMAP_H
#define MEMMAP_H

#define LOCAL_MEM_ADDRWIDTH            16
#define LOCAL_MEM_START_ADDR           0x8000000
#define LOCAL_MEM_SIZE                 (64 * 1024)

#define GLOBAL_MEM_START_ADDR_ARM      0x80000000
#define GLOBAL_MEM_START_ADDR          0x100000000

#define UART_CTLR_BASE_ADDR            0x58018000

#define GDMA_ENGINE_BASE_ADDR          0x58000000
#define GDMA_ENGINE_END_ADDR           (GDMA_ENGINE_BASE_ADDR + 0x1000)
#define BD_ENGINE_BASE_ADDR            0x58002000 //"NPS Register" in memory map?
#define BD_ENGINE_END_ADDR             (BD_ENGINE_BASE_ADDR + 0x3000)

#endif /* MEMMAP_H */
