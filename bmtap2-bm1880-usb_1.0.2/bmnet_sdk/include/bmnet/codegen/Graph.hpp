/*
 * Copyright (C) Bitmain Technologies Inc.
 * All Rights Reserved.
 */
#pragma once

#include <bmnet/proto/TensorOps.hpp>
#include <bmnet/utils/common.hpp>
#include <vector>

namespace bmnet {

class Node {
 public:
  Node() {}
  Node(TensorOp op) { op_.CopyFrom(op); }
  virtual ~Node() {}

  void copy_op(const TensorOp &op) { op_.CopyFrom(op); }
  void add_prev(Node *node) { prev_.push_back(node); }
  void add_prev(Node *node, const std::string& name) {
    int i = 0;
    for (; i < op_.bottom_size(); i++) {
      if (name == op_.bottom(i))
        break;
    }
    assert(i < op_.bottom_size());

    int j = 0;
    for (; j < p_order_.size(); j++) {
      if (i < p_order_[j]) {
        break;
      }
    }
    p_order_.insert(p_order_.begin() + j, i);
    prev_.insert(prev_.begin() + j, node);
  }

  void add_next(Node *node) { next_.push_back(node); }
  void add_next(Node *node, const std::string& name) {
    int i = 0;
    for (; i < op_.top_size(); i++) {
      if (name == op_.top(i))
        break;
    }
    assert(i < op_.top_size());

    int j = 0;
    for (; j < n_order_.size(); j++) {
      if (i < n_order_[j]) {
        break;
      }
    }
    n_order_.insert(n_order_.begin() + j, i);
    next_.insert(next_.begin() + j, node);
  }

  int prev_size() { return prev_.size(); }
  int next_size() { return next_.size(); }
  Node *prev(int index) { return prev_[index]; }
  Node *next(int index) { return next_[index]; }
  void set_prev(int index, Node *node) { prev_[index] = node; }
  void set_next(int index, Node *node) { next_[index] = node; }
  TensorOp *op() { return &op_; }
  std::string op_name() { return op_.name(); }
  // for graph traverse
  int cur_index() { return cur_index_; }
  void inc_cur_index() { cur_index_++; }
  void reset_cur_index() { cur_index_ = 0; }

 private:
  std::vector<Node *> next_;
  std::vector<Node *> prev_;
  std::vector<int> p_order_;
  std::vector<int> n_order_;
  TensorOp op_;
  // for graph traverse
  int cur_index_ = 0;
};

//
// Notes on build graph
// 1. Node prev pointers need to be consistent with op bottom
//    Node next pointers need to be consistent with op top
// 2. [split nodes]: only split node has multiple next/top
//    [merge nodes]: only concat and eltsize node has multiple prev/bottom
// 3. all nodes should have top name same as its op name (inplace is not allowed)
//    except for [split nodes], top names are {op_name}_0, {op_name}_1, etc
// 4. [leaf nodes]: build time concept, meaning open-ended
//    by the time build end, should be only one leaf node left, the "end" node
// 5. Caffe inplace node is with top name same as bottom name
//    bmnet graph does NOT support inplace, need to convert in frontend
// 6. Does not allow to create empty node, have to generate TensorOp first
//
// Notes on traverse graph
// 1. No TensorOp information needed
//
// Notes on modify graph
//
class Graph {
 public:
  Graph();
  Graph(NetParameter *in_net);
  virtual ~Graph();

  Node *add_node(const TensorOp &op);
  std::vector<Node *> build_output_nodes();
  void build_start();
  void build_end();
  Node *traverse_start();
  Node *traverse_next();
  void traverse_end();
  void traverse_quit();
  // suspend traversing current branch,
  // switch to another one.
  bool traverse_suspend();
  void remove_node(Node *node);
  void insert_node(Node *parent, Node *node);
  void add_exposed_nodes(Node* cur);
  void remove_segment(Node *seg_start, int seg_len);
  void insert_segment(Node *parent, Node *seg_start, int seg_len);
  void set_name(std::string name);
  std::string name();
  void fixup_caffe_net_crop(NetParameter &param, NetParameter *param_fixed);
  void output_to_net(NetParameter *out_net);
  void input_from_net(NetParameter *in_net);

 private:
  Node *root_node_ = nullptr;
  std::string name_;

  //
  // build graph and traverse are exclusive states
  // can not do at the same time
  //
  bool is_doing_build_ = false;
  bool is_doing_traverse_ = false;
  Node *node_cur_ = nullptr;
  std::vector<Node *> split_list_;
  std::vector<Node *> leaf_list_;
  std::vector<Node *> suspend_list_;

  bool is_split_node(Node *node);
  bool is_merge_node(Node *node);
  bool is_child_of(Node *parent, Node *child);
};

}  // end namespace bmnet
