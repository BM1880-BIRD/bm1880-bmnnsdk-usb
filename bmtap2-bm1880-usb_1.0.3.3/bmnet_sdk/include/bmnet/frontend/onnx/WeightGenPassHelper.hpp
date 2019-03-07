/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _WEIGHT_GEN_PASS_HELPER_HPP_
#define _WEIGHT_GEN_PASS_HELPER_HPP_

#include <cstdint>
#include <vector>

namespace bmnet {
class OnnxOperator;

void reorderConvWeight(std::vector<int8_t> &vec, const OnnxOperator *inst);
void reorder16bit(std::vector<int16_t> &vec);
void reorderConvTransposeWeight(std::vector<int8_t> &vec, const OnnxOperator *inst);

}  // namespace bmnet

#endif  //_WEIGHT_GEN_PASS_HELPER_HPP_
