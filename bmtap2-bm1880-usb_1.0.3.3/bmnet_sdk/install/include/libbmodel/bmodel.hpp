/*
 * Copyright Bitmain Technologies Inc.
 * Written by:
 *   Pengchao Hu <pengchao.hu@bitmain.com>
 * Created Time: 2018-05-21 15:34
 */
#ifndef LIBBMODEL_HPP_
#define LIBBMODEL_HPP_

#include <bmkernel/bm_kernel.h>
#include <libbmodel/bmodel.pb.h>
#include <string>

namespace bmodel {

// save model to bmodel file
bmerr_t save(const Model &model, const std::string &filename);

// print model info as json format
void print(const Model &model);

}  // namespace bmodel

#endif  // LOADABLE_HPP_
