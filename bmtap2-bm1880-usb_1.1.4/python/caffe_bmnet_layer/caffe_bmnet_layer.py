import numpy as np
import os

import caffe
import bmtap2.bmruntime
from bmtap2.bmruntime import BMContex, BMNet
import yaml
import struct

class BMNetLayer(caffe.Layer):

    def setup(self, bottom, top):
        """Setup the DataLayer."""
        # No inplace_computation check?
        # parse the layer parameter string, which must be valid YAML
        layer_params = yaml.load(self.param_str)
        print(layer_params)

        bmodel_path = layer_params['bmodel_path']
        self.input_sz = 0
        self.input_shape = []
        for i in range(len(bottom)):
            tmp = np.array([], dtype=np.int32)
            for j in range(len(bottom[i].shape)):
                tmp = np.append(tmp, bottom[i].shape[j])
            self.input_shape.append(tmp)

        self.ctx = BMContex(0)
        self.bmnet = BMNet(self.ctx, bmodel_path)
        self.bmnet.set_input_shapes(self.input_shape)
        self.input_sz = self.bmnet.get_input_size()
        self.output_sz = self.bmnet.get_output_size()
        self.output_shape = self.bmnet.get_output_shape()
        self.input_threshold = self.bmnet.get_input_threshold()
        self.output_threshold = self.bmnet.get_output_threshold()
        self.input_fmt = self.bmnet.get_input_fmt()
        self.output_fmt = self.bmnet.get_output_fmt()
        if len(top) != len(self.output_shape):
            assert(0)

    def forward(self, bottom, top):
        data_i = np.zeros(self.input_sz, dtype=np.int8)
        idx_i = 0
        for i in range(len(bottom)):
            bottom_length = 1
            for j in range(len(bottom[i].shape)):
                bottom_length *= bottom[i].shape[j]

            input_data = np.reshape(bottom[i].data, -1)
            if self.input_fmt[i] != 0:
                input_data = np.floor(input_data * 128. / self.input_threshold[i] + 0.5)
                data_i[idx_i : idx_i + bottom_length] = np.array(input_data, dtype=np.int8)
            else:
                bottom_length *= 4
                temp = []
                for i in range(len(input_data)):
                    packed_data = struct.pack('1f', *[input_data[i]])
                    temp.append(struct.unpack('>4b', packed_data))

                data_i[idx_i : idx_i + bottom_length] = np.reshape(temp, (bottom_length))

            idx_i += bottom_length

        data_o = np.zeros(self.output_sz, dtype=np.int8)
        self.bmnet.inference(data_i, data_o)

        idx = self.output_offset
        for i in range(len(top)):
            top_length = 1
            for j in range(len(top[i].shape)):
                top_length *= top[i].shape[j]

            if self.output_fmt[i] != 0:
                output_data = data_o[idx : idx + top_length] * self.output_threshold[i] / 128.
                top[i].data[...] = np.reshape(output_data, top[i].data.shape)
            else:
                j = 0
                temp = []
                top_length *= 4
                while j < top_length:
                    packed_data = struct.pack('4b', *[data_o[idx + j + 3], data_o[idx + j + 2], data_o[idx + j + 1], data_o[idx + j]])
                    temp.append(struct.unpack('>f', packed_data))
                    j += 4
                top[i].data[...] = np.reshape(temp, top[i].data.shape)

            idx += top_length

    def backward(self, top, propagate_down, bottom):
        """This layer does not propagate gradients."""
        pass

    def reshape(self, bottom, top):
        last_total_output = 0
        for i in range(len(self.output_shape)):
            shape = [1, 1, 1, 1]
            for j in range(len(self.output_shape[i])):
                shape[j] = self.output_shape[i][j]
            top[i].reshape(shape[0], shape[1], shape[2], shape[3])
            if self.output_fmt[i] == 0:
                last_total_output += shape[0] * shape[1] * shape[2] * shape[3] * 4
            else:
                last_total_output += shape[0] * shape[1] * shape[2] * shape[3]
        self.output_offset = self.output_sz - last_total_output
