/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _FIXUP_NEURON_OFFSET_H_
#define _FIXUP_NEURON_OFFSET_H_

#include <iostream>
#include <vector>
#include <bmnet/utils/common.hpp>
#include <bmnet/proto/TensorOps.hpp>
#include <bmnet/codegen/Graph.hpp>

namespace bmnet {

class FixupNeuronOffset {
public:
  // very minimal fixup, with zero consideration on saving memory
  static void fixupGraph(Graph *graph) {
    LOG(INFO) << "FixupNeuronOffset";
    Node *node = graph->traverse_start();
    uint64_t last_global_offset = 0;
    while (node) {
      TensorOp *op = node->op();
      LOG(INFO) << "Fix Neuron Offset for " << node->op_name();

      if (op->type() == "start") {
        CHECK_EQ(last_global_offset, 0);
        op->add_global_output(last_global_offset);
      }

      if (op->type() != "start" && op->type() != "end" && op->type() != "tg_split") {
        CHECK(op->global_input_size() && op->global_output_size());
        CHECK_EQ(node->next_size(), 1);
        CHECK_EQ(node->op()->top_size(), 1);

        // prev output is the current input
        for (int i = 0; i < node->prev_size(); i++) {
          // find the corresponding top index
          int prev_top_size = node->prev(i)->op()->top_size();
          int j = 0;
          for (j = 0; j < prev_top_size; j++) {
            if (node->prev(i)->op()->top(j) == node->op()->bottom(i)) {
              LOG(INFO) << "  input " << i << " use " << node->prev(i)->op_name()
                        << " top "<< j;
              break;
            }
          }
          CHECK(j < prev_top_size);
          op->set_global_input(i, node->prev(i)->op()->global_output(j));
        }

        // calc the new output address
        for (int i = 0; i < node->prev_size(); i++) {
          const TensorShape &input_shape = op->input_shape(i);
          last_global_offset += GetTensorSize(input_shape);
        }
        op->set_global_output(0, last_global_offset);

        // for concat, fix the prev output address to make sure it is in-place
        if (op->type() == "tg_concat") {
          uint64_t concat_global_offset = op->global_output(0);
          for (int i = 0; i < node->prev_size(); i++) {
            CHECK_EQ(node->prev(i)->op()->top_size(), 1);
            node->prev(i)->op()->set_global_output(0, concat_global_offset);
            op->set_global_input(i, concat_global_offset);
            concat_global_offset += GetTensorSize(node->prev(i)->op()->output_shape(0));
          }
        }
      }

      if (op->type() == "tg_split") {
        CHECK_EQ(node->prev_size(), 1);
        CHECK_EQ(node->prev(0)->next_size(), 1);
        CHECK_EQ(node->prev(0)->op()->top(0), node->op()->bottom(0));
        uint64_t split_global_offset = node->prev(0)->op()->global_output(0);
        op->set_global_input(0, split_global_offset);
        for (int i = 0; i < op->top_size(); i++) {
          op->set_global_output(i, split_global_offset);
        }
      }

      if (op->type() == "end") {
        const TensorShape &input_shape = op->input_shape(0);

        EndParameter* out_param = op->mutable_end_param();
        out_param->set_output_offset(last_global_offset);
        out_param->set_output_size(GetTensorSize(input_shape));
        last_global_offset += GetTensorSize(input_shape);
        out_param->set_total_neuron_size(last_global_offset);
      }

      node = graph->traverse_next();
    }
    graph->traverse_end();
  }
};

} // end namespace bmnet

#endif /* _FIXUP_NEURON_OFFSET_H_ */
