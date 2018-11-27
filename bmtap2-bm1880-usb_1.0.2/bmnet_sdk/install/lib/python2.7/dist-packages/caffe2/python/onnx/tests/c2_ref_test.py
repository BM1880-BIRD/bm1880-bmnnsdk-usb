# @package onnx
# Module caffe2.python.onnx.tests.c2_ref_test

from __future__ import absolute_import
from __future__ import division
from __future__ import print_function
from __future__ import unicode_literals

import json
import os
import unittest

from caffe2.python import core
from caffe2.proto import caffe2_pb2

import onnx
from onnx.helper import make_node, make_graph, make_tensor, make_tensor_value_info, make_model
from caffe2.python.onnx.helper import c2_native_run_net, c2_native_run_op

from onnx import defs, mapping
import caffe2.python.onnx.frontend as c2_onnx
import caffe2.python.onnx.backend as c2

import numpy as np
from caffe2.python.models.download import downloadFromURLToFile, getURLFromName, deleteDirectory

from caffe2.python.onnx.tests.test_utils import TestCase

import caffe2.python._import_c_extension as C


class TestCaffe2Basic(TestCase):
    def test_dummy_name(self):
        g = C.DummyName()
        n1 = g.new_dummy_name()
        n2 = g.new_dummy_name()
        assert n1 != n2, "Got same names in different calls: {}".format(n1)

    def test_check_arguments(self):
        b2 = C.Caffe2Backend()

        node_def = make_node("Add", inputs=["X", "Y"], outputs=["Z"])
        b2.convert_node(node_def.SerializeToString())

        bad_node_def = make_node("Add", inputs=["X", "Y"], outputs=["Z"], foo=42, bar=56)
        with self.assertRaisesRegexp(
                RuntimeError,
                ".*?Don't know how to map unexpected argument (foo|bar) \(from operator .*?\).*$"):
            b2.convert_node(bad_node_def.SerializeToString())

    def test_relu_graph(self):
        X = np.random.randn(3, 2).astype(np.float32)
        Y_ref = np.clip(X, 0, np.inf)

        node_def = make_node(
            "Relu", ["X"], ["Y"])
        output = c2.run_node(
            node_def, {"X": X})
        np.testing.assert_almost_equal(output.Y, Y_ref)

        graph_def = make_graph(
            [node_def],
            name="test",
            inputs=[make_tensor_value_info("X", onnx.TensorProto.FLOAT, [3, 2])],
            outputs=[make_tensor_value_info("Y", onnx.TensorProto.FLOAT, [3, 2])])
        c2_rep = c2.prepare(make_model(graph_def, producer_name='caffe2-ref-test'))
        output = c2_rep.run(X)
        np.testing.assert_almost_equal(output.Y, Y_ref)

    def test_initializer(self):
        X = np.array([[1, 2], [3, 4]]).astype(np.float32)
        Y = np.array([[1, 2], [3, 4]]).astype(np.float32)
        weight = np.array([[1, 0], [0, 1]])
        graph_def = make_graph(
            [make_node("Add", ["X", "Y"], ["Z0"]),
             make_node("Cast", ["Z0"], ["Z"], to=onnx.TensorProto.FLOAT),
             make_node("Mul", ["Z", "weight"], ["W0"]),
             make_node("Tanh", ["W0"], ["W1"]),
             make_node("Sigmoid", ["W1"], ["W2"]),
             make_node("Scale", ["W2"], ["W3"], scale=-1.0)],
            name="test_initializer",
            inputs=[
                make_tensor_value_info("X", onnx.TensorProto.FLOAT, (2, 2)),
                make_tensor_value_info("Y", onnx.TensorProto.FLOAT, (2, 2)),
                make_tensor_value_info("weight", onnx.TensorProto.FLOAT, (2, 2)),
            ],
            outputs=[
                make_tensor_value_info("W3", onnx.TensorProto.FLOAT, (2, 2))
            ],
            initializer=[make_tensor("weight",
                                     onnx.TensorProto.FLOAT,
                                     [2, 2],
                                     weight.flatten().astype(float))]
        )

        def sigmoid(x):
            return 1 / (1 + np.exp(-x))

        W_ref = -sigmoid(np.tanh((X + Y) * weight))
        c2_rep = c2.prepare(make_model(graph_def, producer_name='caffe2-ref-test'))
        output = c2_rep.run({"X": X, "Y": Y})
        np.testing.assert_almost_equal(output["W3"], W_ref)

    def test_upsample(self):
        X = np.random.randn(1, 1, 2, 2).astype(np.float32)
        width_scale = 2.0
        height_scale = 2.0

        predict_net = caffe2_pb2.NetDef()
        predict_net.name = 'test-upsample-net'
        predict_net.external_input[:] = ['X']
        predict_net.external_output[:] = ['Y']
        predict_net.op.extend([
            core.CreateOperator(
                'ResizeNearest',
                inputs=['X'],
                outputs=['Y'],
                width_scale=width_scale,
                height_scale=height_scale,
            ),
        ])
        ws, c2_outputs = c2_native_run_net(
            init_net=None,
            predict_net=predict_net,
            inputs=[X])

        onnx_model = c2_onnx.caffe2_net_to_onnx_model(
            predict_net=predict_net,
            value_info={
                'X': (onnx.mapping.NP_TYPE_TO_TENSOR_TYPE[X.dtype], X.shape)
            })
        onnx_outputs = c2.run_model(onnx_model, inputs=[X])
        self.assertSameOutputs(c2_outputs, onnx_outputs)

    def test_gemm(self):
        # simple
        A = np.random.randn(3, 2).astype(np.float32)
        B = np.random.randn(2, 4).astype(np.float32)
        C = np.random.randn(3, 4).astype(np.float32)
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"])
        output = c2.run_node(node_def, [A, B, C])
        np.testing.assert_almost_equal(output["Y"], np.dot(A, B) + C)

        # transA
        A = np.transpose(A)
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            transA=1)
        output = c2.run_node(node_def, [A, B, C])
        np.testing.assert_almost_equal(
            output["Y"],
            np.dot(np.transpose(A), B) + C)
        # revert A
        A = np.transpose(A)

        # transB
        B = np.transpose(B)
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            transB=1)
        output = c2.run_node(node_def, [A, B, C])
        np.testing.assert_almost_equal(
            output["Y"],
            np.dot(A, np.transpose(B)) + C)
        # revert B
        B = np.transpose(B)

        # scale
        alpha = np.random.random()
        beta = np.random.random()
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=alpha,
            beta=beta)
        output = c2.run_node(node_def, [A, B, C])
        np.testing.assert_almost_equal(
            output["Y"],
            alpha * np.dot(A, B) + beta * C)

        # setup broadcastable C
        C = np.random.randn(4).astype(np.float32)

        # broadcast for opset7
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=alpha,
            beta=beta)
        output = c2.run_node(node_def, [A, B, C], opset_version=7)
        np.testing.assert_almost_equal(
            output["Y"],
            alpha * np.dot(A, B) + beta * C)
        # broadcast for opset3 and 6
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=alpha,
            beta=beta,
            broadcast=1)
        output = c2.run_node(node_def, [A, B, C], opset_version=6)
        np.testing.assert_almost_equal(
            output["Y"],
            alpha * np.dot(A, B) + beta * C)

        # transB
        B = np.transpose(B)

        # transB and broadcast for opset7
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=alpha,
            beta=beta,
            transB=1)
        output = c2.run_node(node_def, [A, B, C], opset_version=7)
        np.testing.assert_almost_equal(
            output["Y"],
            alpha * np.dot(A, np.transpose(B)) + beta * C)
        # transB and broadcast for opset3 and 6
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=alpha,
            beta=beta,
            broadcast=1,
            transB=1)
        output = c2.run_node(node_def, [A, B, C], opset_version=6)
        np.testing.assert_almost_equal(
            output["Y"],
            alpha * np.dot(A, np.transpose(B)) + beta * C)

        # revert B
        B = np.transpose(B)
        # set a scalar to C
        C = np.random.randn(1).astype(np.float32)

        # scalar broadcast for opset7
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=alpha,
            beta=beta)
        output = c2.run_node(node_def, [A, B, C], opset_version=7)
        np.testing.assert_almost_equal(
            output["Y"],
            alpha * np.dot(A, B) + beta * C)
        # scalar broadcast for opset3 and 6
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=alpha,
            beta=beta,
            broadcast=1)
        output = c2.run_node(node_def, [A, B, C], opset_version=6)
        np.testing.assert_almost_equal(
            output["Y"],
            alpha * np.dot(A, B) + beta * C)

    def test_gemm_conversion(self):
        node_def = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=2.,
            beta=3.)
        node_def_broadcast = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=2.,
            beta=3.,
            broadcast=1)
        node_def_transpose_b = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=2.,
            beta=3.,
            transB=1)

        node_def_transpose_b_broadcast = make_node(
            'Gemm',
            ['A', 'B', 'C'],
            ["Y"],
            alpha=2.,
            beta=3.,
            transB=1,
            broadcast=1)

        backend = C.Caffe2Backend()

        # without broadcast and without shape info, gemm will be
        # converted to matmul + add
        _, op_strs = backend.convert_node(node_def.SerializeToString())
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'MatMul', 'Add'])

        # opset7
        # If C is a 1d tensor, gemm will be converted to FC/FCTransposed
        _, op_strs = backend.convert_node(node_def_transpose_b.SerializeToString(
        ), [make_tensor_value_info("C", onnx.TensorProto.FLOAT, (3,)).SerializeToString()],
        7)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'FC'])

        _, op_strs = backend.convert_node(node_def.SerializeToString(
        ), [make_tensor_value_info("C", onnx.TensorProto.FLOAT, (3,)).SerializeToString()],
        7)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'FCTransposed'])

        # opset6 without broadcast(C should match A*B's dim)
        # The gemm will be converted to matmul + add, since the FC requires c
        # to be 1d tensor.
        _, op_strs = backend.convert_node(node_def.SerializeToString(
        ), [make_tensor_value_info("A", onnx.TensorProto.FLOAT, (3,2)).SerializeToString(),
            make_tensor_value_info("B", onnx.TensorProto.FLOAT, (2,3)).SerializeToString(),
            make_tensor_value_info("C", onnx.TensorProto.FLOAT, (3,3)).SerializeToString()],
        6)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'MatMul', 'Add'])

        # opset6 with broadcast
        # If C is a 1d tensor, gemm will be converted to FC/FCTransposed
        _, op_strs = backend.convert_node(node_def_transpose_b_broadcast.SerializeToString(
        ), [make_tensor_value_info("C", onnx.TensorProto.FLOAT, (3,)).SerializeToString()],
        6)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'FC'])

        _, op_strs = backend.convert_node(node_def_broadcast.SerializeToString(
        ), [make_tensor_value_info("C", onnx.TensorProto.FLOAT, (3,)).SerializeToString()],
        6)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'FCTransposed'])

        # opset7
        # If C is a scalar and B's last dim is 1, gemm will be converted to FC/FCTransposed
        _, op_strs = backend.convert_node(node_def_transpose_b.SerializeToString(
        ), [make_tensor_value_info("B", onnx.TensorProto.FLOAT, (1,2)).SerializeToString(),
            make_tensor_value_info("C", onnx.TensorProto.FLOAT, (1,)).SerializeToString()],
        7)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'FC'])

        _, op_strs = backend.convert_node(node_def.SerializeToString(
        ), [make_tensor_value_info("B", onnx.TensorProto.FLOAT, (2,1)).SerializeToString(),
            make_tensor_value_info("C", onnx.TensorProto.FLOAT, (1,)).SerializeToString()],
        7)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'FCTransposed'])
        # If C is a scalar and B's last dim is not 1, gemm will be converted
        # to matmul + add.
        _, op_strs = backend.convert_node(node_def_transpose_b.SerializeToString(
        ), [make_tensor_value_info("B", onnx.TensorProto.FLOAT, (2,2)).SerializeToString(),
            make_tensor_value_info("C", onnx.TensorProto.FLOAT, (1,)).SerializeToString()],
        7)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'MatMul', 'Add'])
        # If C is a scalar and B's shape info is not available,
        # gemm will be converted to matmul + add.
        _, op_strs = backend.convert_node(node_def_transpose_b.SerializeToString(
        ), [make_tensor_value_info("C", onnx.TensorProto.FLOAT, (1,)).SerializeToString()],
        7)
        op_names = []
        for s in op_strs:
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(s)
            op_names.append(op.type)
        self.assertEqual(op_names, ['Scale', 'Scale', 'MatMul', 'Add'])

    def test_tensor_filling_ops(self):
        for dtype in [
                onnx.TensorProto.FLOAT,
                onnx.TensorProto.DOUBLE,
                onnx.TensorProto.BOOL,
                onnx.TensorProto.INT8,
                onnx.TensorProto.INT16,
                onnx.TensorProto.INT32,
                onnx.TensorProto.INT64,
                onnx.TensorProto.UINT8,
                onnx.TensorProto.UINT16,
                onnx.TensorProto.UINT32,
        ]:
            shape = (1, 2, 3)
            vals = np.random.randn(*shape)
            if dtype != onnx.TensorProto.BOOL:
                vals *= 5
            vals = vals.astype(
                mapping.TENSOR_TYPE_TO_NP_TYPE[dtype])
            tensor = make_tensor(
                name='test-tensor-{}'.format(dtype),
                data_type=dtype,
                dims=[1, 2, 3],
                vals=vals.flatten().tolist(),
            )
            op = c2.Caffe2Backend._create_tensor_filling_op(tensor)
            self.assertEqual(len(op.input), 0)
            self.assertEqual(op.output, [tensor.name])
            ws, output = c2_native_run_op(op, inputs=[])
            self.assertEqual(len(output), 1)
            np.testing.assert_almost_equal(output[0], vals)
            np.testing.assert_almost_equal(ws.FetchBlob(op.output[0]), vals)

    def test_tensor_filling_ops_c_backend(self):
        for dtype in [
                onnx.TensorProto.FLOAT,
                onnx.TensorProto.DOUBLE,
                onnx.TensorProto.BOOL,
                onnx.TensorProto.INT8,
                onnx.TensorProto.INT16,
                onnx.TensorProto.INT32,
                onnx.TensorProto.INT64,
                onnx.TensorProto.UINT8,
                onnx.TensorProto.UINT16,
                onnx.TensorProto.UINT32,
        ]:
            shape = (1, 2, 3)
            vals = np.random.randn(*shape)
            if dtype != onnx.TensorProto.BOOL:
                vals *= 5
            vals = vals.astype(
                mapping.TENSOR_TYPE_TO_NP_TYPE[dtype])
            tensor = make_tensor(
                name='test-tensor-{}'.format(dtype),
                data_type=dtype,
                dims=[1, 2, 3],
                vals=vals.flatten().tolist(),
            )
            b = C.Caffe2Backend()
            op = caffe2_pb2.OperatorDef()
            op.ParseFromString(b._build_tensor_filling_op(tensor.SerializeToString(), ''))
            self.assertEqual(len(op.input), 0)
            self.assertEqual(op.output, [tensor.name])
            ws, output = c2_native_run_op(op, inputs=[])
            self.assertEqual(len(output), 1)
            np.testing.assert_almost_equal(output[0], vals)
            np.testing.assert_almost_equal(ws.FetchBlob(op.output[0]), vals)

    def test_slice(self):
        X = np.random.randn(1, 2, 3).astype(np.float32)
        starts = np.array([0, 1, 0], dtype=np.int32)
        ends = np.array([-1, 2, 3], dtype=np.int32)

        predict_net = caffe2_pb2.NetDef()
        predict_net.name = 'test-slice-net'
        predict_net.external_input[:] = ['X']
        predict_net.external_output[:] = ['Y']
        predict_net.op.extend([
            core.CreateOperator(
                'Slice',
                inputs=['X'],
                outputs=['Y'],
                starts=starts,
                ends=ends,
            ),
        ])
        ws, c2_outputs = c2_native_run_net(
            init_net=None,
            predict_net=predict_net,
            inputs=[X])

        onnx_model = c2_onnx.caffe2_net_to_onnx_model(
            predict_net=predict_net,
            value_info={
                'X': (onnx.mapping.NP_TYPE_TO_TENSOR_TYPE[X.dtype], X.shape)
            })
        onnx_outputs = c2.run_model(onnx_model, inputs=[X])
        self.assertSameOutputs(c2_outputs, onnx_outputs)

    def test_cast(self):
        X = np.random.randn(1, 2, 3).astype(np.float32)

        for to_type in ['INT8', caffe2_pb2.TensorProto.INT8,
                        'DOUBLE', caffe2_pb2.TensorProto.DOUBLE]:
            predict_net = caffe2_pb2.NetDef()
            predict_net.name = 'test-cast-net'
            predict_net.external_input[:] = ['X']
            predict_net.external_output[:] = ['Y']
            predict_net.op.extend([
                core.CreateOperator(
                    'Cast',
                    inputs=['X'],
                    outputs=['Y'],
                    to=to_type,
                ),
            ])
            ws, c2_outputs = c2_native_run_net(
                init_net=None,
                predict_net=predict_net,
                inputs=[X])

            onnx_model = c2_onnx.caffe2_net_to_onnx_model(
                predict_net=predict_net,
                value_info={
                    'X': (onnx.mapping.NP_TYPE_TO_TENSOR_TYPE[X.dtype], X.shape)
                })
            onnx_outputs = c2.run_model(onnx_model, inputs=[X])
            self.assertSameOutputs(c2_outputs, onnx_outputs)


class TestCaffe2End2End(TestCase):
    def _model_dir(self, model):
        caffe2_home = os.path.expanduser(os.getenv('CAFFE2_HOME', '~/.caffe2'))
        models_dir = os.getenv('ONNX_MODELS', os.path.join(caffe2_home, 'models'))
        return os.path.join(models_dir, model)

    def _test_net(self,
                  net_name,
                  input_blob_dims=(1, 3, 224, 224),
                  decimal=7):
        np.random.seed(seed=0)
        model_dir = self._model_dir(net_name)
        if not os.path.exists(model_dir):
            self._download(net_name)
        c2_predict_pb = os.path.join(model_dir, 'predict_net.pb')
        c2_predict_net = caffe2_pb2.NetDef()
        with open(c2_predict_pb, 'rb') as f:
            c2_predict_net.ParseFromString(f.read())
        c2_predict_net.name = net_name

        c2_init_pb = os.path.join(model_dir, 'init_net.pb')
        c2_init_net = caffe2_pb2.NetDef()
        with open(c2_init_pb, 'rb') as f:
            c2_init_net.ParseFromString(f.read())
        c2_init_net.name = net_name + '_init'

        n, c, h, w = input_blob_dims
        data = np.random.randn(n, c, h, w).astype(np.float32)
        inputs = [data]
        _, c2_outputs = c2_native_run_net(c2_init_net, c2_predict_net, inputs)
        del _

        model = c2_onnx.caffe2_net_to_onnx_model(
            predict_net=c2_predict_net,
            init_net=c2_init_net,
            value_info=json.load(open(os.path.join(model_dir, 'value_info.json'))))
        c2_ir = c2.prepare(model)
        onnx_outputs = c2_ir.run(inputs)
        self.assertSameOutputs(c2_outputs, onnx_outputs, decimal=decimal)

    def _download(self, model):
        model_dir = self._model_dir(model)
        assert not os.path.exists(model_dir)
        os.makedirs(model_dir)
        for f in ['predict_net.pb', 'init_net.pb', 'value_info.json']:
            url = getURLFromName(model, f)
            dest = os.path.join(model_dir, f)
            try:
                try:
                    downloadFromURLToFile(url, dest,
                                          show_progress=False)
                except TypeError:
                    # show_progress not supported prior to
                    # Caffe2 78c014e752a374d905ecfb465d44fa16e02a28f1
                    # (Sep 17, 2017)
                    downloadFromURLToFile(url, dest)
            except Exception as e:
                print("Abort: {reason}".format(reason=e))
                print("Cleaning up...")
                deleteDirectory(model_dir)
                exit(1)

    def test_alexnet(self):
        self._test_net('bvlc_alexnet', decimal=4)

    def test_resnet50(self):
        self._test_net('resnet50')

    @unittest.skipIf(
        os.environ.get('JENKINS_URL'),
        'Taking too long to download!')
    def test_vgg16(self):
        self._test_net('vgg16')

    @unittest.skipIf(
        os.environ.get('JENKINS_URL'),
        'Taking too long to download!')
    def test_zfnet(self):
        self._test_net('zfnet')

    def test_inception_v1(self):
        self._test_net('inception_v1', decimal=2)

    def test_inception_v2(self):
        self._test_net('inception_v2')

    def test_squeezenet(self):
        self._test_net('squeezenet')

    def test_densenet121(self):
        self._test_net('densenet121')

    def test_bvlc_googlenet(self):
        self._test_net('bvlc_googlenet')

    def test_bvlc_reference_caffenet(self):
        self._test_net('bvlc_reference_caffenet')

    def test_bvlc_reference_rcnn_ilsvrc13(self):
        self._test_net('bvlc_reference_rcnn_ilsvrc13')


if __name__ == '__main__':
    unittest.main()
