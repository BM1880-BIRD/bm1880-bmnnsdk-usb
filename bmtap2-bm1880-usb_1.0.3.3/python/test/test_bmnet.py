#!/usr/bin/python2

import sys
import os
import numpy as np

cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, '../'))
from bmtap2 import *

def test_bmnet_bmodel():
    if len(sys.argv) < 8:
        print "Usage: test_bmnet input.bin bmodel.bin output.bin N C H W"
        exit(1)

    if not os.path.isfile(sys.argv[1]):
        print "input file not exist: %s" % sys.argv[1]
        exit(1)

    if not os.path.isfile(sys.argv[2]):
        print "bmodel file not exist: %s" % sys.argv[2]
        exit(1)

    f_input = sys.argv[1]
    f_bmodel = sys.argv[2]
    f_output = sys.argv[3]

    n = int(sys.argv[4])
    c = int(sys.argv[5])
    h = int(sys.argv[6])
    w = int(sys.argv[7])

    with BMContex(0) as bmctx, BMNet(bmctx, f_bmodel) as bmnet:
        input_shape = np.array([n, c, h, w])
        input_array = np.fromfile(f_input, dtype=np.float32)

        output_size = bmnet.get_output_size()
        output_array = np.empty(output_size / 4, dtype=np.float32)

        bmnet.set_input_shape(input_shape)

        bmnet.inference(input_array, output_array)

        output_array.tofile(f_output)

if __name__ == "__main__":
    test_bmnet_bmodel()
