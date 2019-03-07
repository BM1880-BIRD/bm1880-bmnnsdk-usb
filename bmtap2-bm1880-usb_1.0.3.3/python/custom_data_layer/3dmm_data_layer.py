# ------------------------------------------------------------------------------------------------
# This file is a modified version of https://github.com/rbgirshick/py-faster-rcnn by Ross Girshick
# Modified by Mahyar Najibi
# ------------------------------------------------------------------------------------------------
import os, sys

cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, '../../../caffe/python'))

import caffe
import yaml
from glob import glob
class Face3dmm2DataLayer(caffe.Layer):

    def setup(self, bottom, top):
        """Setup the DataLayer."""
        # parse the layer parameter string, which must be valid YAML
        layer_params = yaml.load(self.param_str)
        self.mean_path = layer_params['mean_file']
        self.imgs = layer_params['img']
	top[0].reshape(1, 3, 224, 224)


    def forward(self, bottom, top):
        """Read meanfile and image data"""
        proto_data = open(self.mean_path, "rb").read()
        a = caffe.io.caffe_pb2.BlobProto.FromString(proto_data)
        mean = caffe.io.blobproto_to_array(a)[0]
        img_list = glob(self.imgs + "/*.png")
        img = caffe.io.load_image(img_list[0])

        ## Setting up the right transformer for an input image
        transformer = caffe.io.Transformer({'data': (1, 3, 224, 224)})
        transformer.set_transpose('data', (2, 0, 1))
        transformer.set_channel_swap('data', (2, 1, 0))
        transformer.set_raw_scale('data', 255.0)
        transformer.set_mean('data', mean)
	top[0].reshape(1, 3, 224, 224)
        top[0].data[...] = transformer.preprocess('data', img)

    def backward(self, top, propagate_down, bottom):
        """This layer does not propagate gradients."""
        pass

    def reshape(self, bottom, top):
        """Reshaping happens during the call to forward."""
        pass

