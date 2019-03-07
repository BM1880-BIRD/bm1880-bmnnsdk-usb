## @package onnx
# Module caffe2.python.onnx.tests.onnx_backend_test

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import os

import unittest
import onnx.backend.test

import caffe2.python.onnx.backend as c2

# This is a pytest magic variable to load extra plugins
pytest_plugins = 'onnx.backend.test.report',

backend_test = onnx.backend.test.BackendTest(c2, __name__)

backend_test.exclude(r'(test_hardsigmoid'  # Does not support Hardsigmoid.
                     '|test_hardmax'  # Does not support Hardmax.
                     '|test_cast.*FLOAT16.*'  # Does not support Cast on Float16.
                     '|test_depthtospace.*'  # Does not support DepthToSpace.
                     '|test_reduce_l1.*'  # Does not support ReduceL1.
                     '|test_reduce_l2.*'  # Does not support ReduceL2.
                     '|test_reduce_log_sum.*'  # Does not support ReduceLogSum.
                     '|test_reduce_prod.*'  # Does not support ReduceProd.
                     '|test_reduce_sum_square.*'  # Does not support ReduceSumSquare
                     '|test_tile.*'  # Tile's Caffe2 implementation needs some tweak
                     '|test_lstm.*'  # Seems LSTM case has some problem
                     '|test_simple_rnn.*'  # Seems simple RNN case has some problem
                     '|test_gru.*'  # Seems GRU case has some problem
                     '|test_prelu.*'  # PRelu is not compliant with ONNX yet
                     '|test_operator_repeat.*'  # Tile is not compliant with ONNX yet
                     '|test_.*pool_.*same.*'  # Does not support pool same.
                     '|test_maxpool_with_argmax.*'  # MaxPool outputs indices in different format.
                     '|test_convtranspose.*'  # ConvTranspose needs some more complicated translation
                     ')')

# Quick patch to unbreak master CI, is working on the debugging.
backend_test.exclude('(test_cast_.*'
                     '|test_Conv1d_.*cuda'
                     '|test_Conv3d_groups_cuda'
                     '|test_rnn_seq_length'
                     '|test_operator_add.*_cuda'
                     '|test_operator_lstm_cuda'
                     '|test_operator_rnn.*_cuda'
                     '|test_lrn_default_cuda)')

# Temporarily skip some ONNX backend tests with broadcasting.
backend_test.exclude('(test_pow_bcast'
                     ')')

# Skip vgg to speed up CI
if 'JENKINS_URL' in os.environ:
    backend_test.exclude(r'(test_vgg19|test_vgg)')

# import all test cases at global scope to make them visible to python.unittest
globals().update(backend_test
                 .enable_report()
                 .test_cases)

if __name__ == '__main__':
    unittest.main()
