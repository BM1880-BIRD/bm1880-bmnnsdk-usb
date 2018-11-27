/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#ifndef _FIXUP_BOTTOM_NAME_H_
#define _FIXUP_BOTTOM_NAME_H_

#include <iostream>
#include <vector>
#include <bmnet/utils/common.hpp>
#include <bmnet/proto/TensorOps.hpp>
#include <bmnet/codegen/Graph.hpp>

namespace bmnet {

class FixupBottomName {
public:
  static void dumpGraph(Graph *graph) {
    Node *node = graph->traverse_start();
    while (node) {
      std::cout << "Node " << node->op_name()
                << ", prev_size " << node->prev_size()
                << ", next_size " << node->next_size()
                << std::endl;
      for (int i = 0; i < node->prev_size(); i++) {
        std::cout << "  prev(" << i << ") <= " << node->prev(i)->op_name()
                  << std::endl;
      }
      for (int i = 0; i < node->next_size(); i++) {
        std::cout << "  next(" << i << ") <= " << node->next(i)->op_name()
                  << std::endl;
      }

      TensorOp *op = node->op();
      for (int i = 0; i < op->bottom_size(); i++) {
        std::cout << "  op bottom(" << i << ") <= " << op->bottom(i)
                  << std::endl;
      }
      for (int i = 0; i < op->top_size(); i++) {
        std::cout << "  op top(" << i << ") <= " << op->top(i)
                  << std::endl;
      }

      node = graph->traverse_next();
    }
    graph->traverse_end();
  }

  // called when some node is removed during optimization
  // the names in op are not updated along with graph node changes
  static void fixupGraph(Graph *graph) {
    LOG(INFO) << "FixupBottomName";
    Node *node = graph->traverse_start();
    while (node) {
      LOG(INFO) << "Node " << node->op_name();
      TensorOp *op = node->op();

      if (node->prev_size() != op->bottom_size()) {
        LOG(FATAL) << "  prev size not match " << node->prev_size()
                   << " vs " << op->bottom_size();
      }
      for (int i = 0; i < node->prev_size(); i++) {
        if (node->prev(i)->op_name() != op->bottom(i)) {
          LOG(INFO) << "  bottom(" << i << ") name " << op->bottom(i)
                    << " => " << node->prev(i)->op_name();
          op->set_bottom(i, node->prev(i)->op_name());
        }
      }

      node = graph->traverse_next();
    }
    graph->traverse_end();
  }
};

} // end namespace bmnet

#endif /* _FIXUP_BOTTOM_NAME_H_ */
