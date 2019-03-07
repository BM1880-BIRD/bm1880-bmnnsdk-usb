#ifndef __BM_CMDBUF_H__
#define __BM_CMDBUF_H__

#include <bmkernel/bm_kernel.h>

#ifdef __cplusplus
extern "C" {
#endif

void bm_cmdbuf_relocate(
    u32 chip_version,
    uint8_t *cmdbuf,
    size_t cmdbuf_len,
    uint64_t gmem_input_base,
    uint64_t gmem_weight_base);

void bm_cmdbuf_dump(uint8_t *cmdbuf, size_t cmdbuf_len);

void bm_cmdbuf_get_descnum(uint8_t *cmdbuf, size_t cmdbuf_len, uint32_t *bd_num, uint32_t *gdma_num);

#ifdef __cplusplus
}
#endif

#endif /* __BM_CMDBUF_H__ */
