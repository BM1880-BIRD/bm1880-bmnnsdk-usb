#!/usr/bin/python2

import sys
import os
import numpy as np
from compare_bin import compare

cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, '../'))
from bmtap2 import *

f_input = cur_dir+'/../../models/mobilenet/mobilenet_input_1_3_224_224.bin'
f_bmodel = cur_dir+'/../../models/mobilenet/mobilenet_1_3_224_224.bmodel'
f_output_ref = cur_dir+'/../../models/mobilenet/mobilenet_output_1_3_224_224_ref.bin'
f_output = 'output.bin'

def test_mobilenet():
    with BMContex(0) as bmctx, BMNet(bmctx, f_bmodel) as bmnet:
        input_shape = np.array([1, 3, 224, 224])
        input_array = np.fromfile(f_input, dtype=np.int8)

        output_size = bmnet.get_output_size()
        output_array = np.empty(output_size, dtype=np.int8)

        print "input size %d" % input_array.size
        print "output size %d" % output_size

        bmnet.set_input_shape(input_shape)

        bmnet.inference(input_array, output_array)

        output_array.tofile(f_output)

        compare(f_output, f_output_ref, 'int8', 0.00001)

if __name__ == "__main__":
    test_mobilenet()
