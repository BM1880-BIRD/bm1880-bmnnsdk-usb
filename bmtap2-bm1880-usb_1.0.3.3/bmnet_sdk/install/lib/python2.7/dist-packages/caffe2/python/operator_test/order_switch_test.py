from __future__ import absolute_import, division, print_function, unicode_literals

import caffe2.python.hypothesis_test_util as hu
from caffe2.python import core
from hypothesis import given


class OrderSwitchOpsTest(hu.HypothesisTestCase):
    @given(X=hu.tensor(min_dim=3, max_dim=5, min_value=1, max_value=5), **hu.gcs)
    def test_nchw2nhwc(self, X, gc, dc):
        op = core.CreateOperator("NCHW2NHWC", ["X"], ["Y"], device_option=gc)

        def nchw2nhwc_ref(X):
            X_reshaped = X.transpose((0,) + tuple(range(2, X.ndim)) + (1,))
            return (X_reshaped,)

        self.assertReferenceChecks(gc, op, [X], nchw2nhwc_ref)
        self.assertGradientChecks(gc, op, [X], 0, [0])
        self.assertDeviceChecks(dc, op, [X], [0])

    @given(X=hu.tensor(min_dim=3, max_dim=5, min_value=1, max_value=5), **hu.gcs)
    def test_nhwc2nchw(self, X, gc, dc):
        op = core.CreateOperator("NHWC2NCHW", ["X"], ["Y"], device_option=gc)

        def nhwc2nchw_ref(X):
            X_reshaped = X.transpose((0, X.ndim - 1) + tuple(range(1, X.ndim - 1)))
            return (X_reshaped,)

        self.assertReferenceChecks(gc, op, [X], nhwc2nchw_ref)
        self.assertGradientChecks(gc, op, [X], 0, [0])
        self.assertDeviceChecks(dc, op, [X], [0])
