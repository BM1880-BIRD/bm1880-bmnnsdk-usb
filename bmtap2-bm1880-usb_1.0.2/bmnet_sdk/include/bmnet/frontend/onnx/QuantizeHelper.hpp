/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _QUANTIZATIONHELPER_H_
#define _QUANTIZATIONHELPER_H_

#include <onnx/common/ir.h>

namespace bmnet {

void updateQuantizeWeight(ONNX_NAMESPACE::Graph *graph, qWeight_t *q_weight, qBias_t *q_bias);

void QuantizeConv(OnnxOperator *inst, qWeight_t *q_weight, qBias_t *q_bias,
                  NetCTable_t *net_ctable);
void QuantizePool(OnnxOperator *inst, NetCTable_t *net_ctable);
void QuantizeGemm(OnnxOperator *inst, qWeight_t *q_weight, qBias_t *q_bias,
                  NetCTable_t *net_ctable);
void QuantizeLRN(OnnxOperator *inst, qWeight_t *q_weight, qBias_t *q_bias, NetCTable_t *net_ctable);

void QuantizeBN(OnnxOperator *inst, qWeight_t *q_weight, qBias_t *q_bias, NetCTable_t *net_ctable);

void QuantizeConcat(OnnxOperator *inst, qWeight_t *q_weight, qBias_t *q_bias,
                    NetCTable_t *net_ctable);

void QuantizeEltwise(OnnxOperator *inst, qWeight_t *q_weight, qBias_t *q_bias,
                     NetCTable_t *net_ctable);

}  // end namespace bmnet

#endif /* _QUANTIZATIONHELPER_H_ */
