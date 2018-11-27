#ifndef CAFFE_BMNET_LAYER_HPP_
#define CAFFE_BMNET_LAYER_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"
#include <libbmruntime/bmruntime.h>
#include <libbmruntime/bmruntime_bmnet.h>

namespace caffe {

template <typename Dtype>
class BMNetLayer : public Layer<Dtype> {
 public:
  explicit BMNetLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "BMNet"; }
  virtual inline int ExactNumBottomBlobs() const { return 1; }
  virtual inline int MinNumTopBlobs() const { return 1; }

 protected:
  /// @copydoc BMNetLayer
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);
  virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom);


  bmctx_t ctx_;
  bmnet_t net_;
  bmnet_output_info_t output_info_;
  uint32_t total_neuron_size_;
  float in_threshold_;
};

}  // namespace caffe

#endif  // CAFFE_BMNET_LAYER_HPP_
