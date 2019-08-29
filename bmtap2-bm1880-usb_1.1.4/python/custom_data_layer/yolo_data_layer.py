# ------------------------------------------------------------------------------------------------
# This file is a modified version of https://github.com/rbgirshick/py-faster-rcnn by Ross Girshick
# Modified by Mahyar Najibi
# ------------------------------------------------------------------------------------------------
import os, sys

cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, '../../../caffe/python'))

import caffe
import yaml
import cv2
import numpy as np

class Yolov2DataLayer(caffe.Layer):

    def setup(self, bottom, top):
        """Setup the DataLayer."""
        # parse the layer parameter string, which must be valid YAML
        layer_params = yaml.load(self.param_str)
        list_name = layer_params['num_classes']
        self.input_hw = layer_params['hw']
        self.fp = open(list_name)
        # data blob: holds a batch of N images, each with 3 channels
        top[0].reshape(1, 3, self.input_hw, self.input_hw)

    def forward(self, bottom, top):
        pic_name = self.fp.readline()
        if pic_name == "" :
            self.fp.seek(0)
            pic_name = self.fp.readline()
        pic_name = pic_name.strip('\n')
        print(pic_name)
        """
        caffe.set_mode_cpu()
        image = caffe.io.load_image(pic_name)
        transformer = caffe.io.Transformer({'data': (1, 3, 608, 608)})
        transformer.set_transpose('data', (2, 0, 1))  # move image channels to outermost dimension
        transformed_image = transformer.preprocess('data', image)
        """
        img = cv2.imread(pic_name)
        img_w, img_h = img.shape[1], img.shape[0]
        inp_dim = (self.input_hw, self.input_hw)
        w, h = inp_dim
        new_w = int(img_w * min(float(w)/img_w, float(h)/img_h))
        new_h = int(img_h * min(float(w)/img_w, float(h)/img_h))

        resized_image = cv2.resize(img, (new_w,new_h), interpolation = cv2.INTER_CUBIC)

        canvas = np.full((inp_dim[1], inp_dim[0], 3), 128)

        canvas[(h-new_h)//2:(h-new_h)//2 + new_h,(w-new_w)//2:(w-new_w)//2 + new_w,  :] = resized_image

        transformed_image =  canvas[:,:,::-1].transpose([2,0,1]) / 255.0
        # Reshape net's input blobs
        top[0].reshape(1, 3, self.input_hw, self.input_hw)
        # Copy data into net's input blobs
        top[0].data[...] = transformed_image

    def backward(self, top, propagate_down, bottom):
        """This layer does not propagate gradients."""
        pass

    def reshape(self, bottom, top):
        """Reshaping happens during the call to forward."""
        pass

