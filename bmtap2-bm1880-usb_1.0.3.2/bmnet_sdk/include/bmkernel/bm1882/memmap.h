#ifndef MEMMAP_H
#define MEMMAP_H

/*FIXME need to check*/



#define LOCAL_MEM0_ADDRWIDTH            (16)
#define LOCAL_MEM0_START_ADDR           (0x0C000000)
#define LOCAL_MEM0_SIZE                 (64 * 1024)

#define LOCAL_MEM1_ADDRWIDTH            (16)
#define LOCAL_MEM1_START_ADDR           (0x0D000000)
#define LOCAL_MEM1_SIZE                 (64 * 1024)

#define GLOBAL_MEM_START_ADDR           (0x100000000)

#define UART_CTLR_BASE_ADDR             (0x04140000)

#define TDMA0_ENGINE_BASE_ADDR          (0x0C100000)
#define TDMA0_ENGINE_END_ADDR           (GDMA_ENGINE_BASE_ADDR + 0x1000)

#define TDMA1_ENGINE_BASE_ADDR          (0x0D100000)
#define TDMA1_ENGINE_END_ADDR           (GDMA_ENGINE_BASE_ADDR + 0x1000)
#define TIU0_ENGINE_BASE_ADDR           (0x0C101000) //"NPS Register" in memory map?
#define TIU0_ENGINE_END_ADDR            (BD_ENGINE_BASE_ADDR + 0x1000)


#define TIU1_ENGINE_BASE_ADDR            (0x0D101000) //"NPS Register" in memory map?
#define TIU1_ENGINE_END_ADDR             (BD_ENGINE_BASE_ADDR + 0x1000)

#define LOCAL_MEM_START_ADDR            (LOCAL_MEM0_START_ADDR)
#define LOCAL_MEM_SIZE                  (LOCAL_MEM0_SIZE)

#endif /* MEMMAP_H */
