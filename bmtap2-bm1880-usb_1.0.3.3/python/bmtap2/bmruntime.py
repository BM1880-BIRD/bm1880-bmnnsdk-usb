from pybmruntime import ffi,lib
from array import array

class BMContex():
    def __init__(self, index):
        self.ctx = ffi.new('bmctx_t *')
        lib.bm_init(index, self.ctx)

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        lib.bm_exit(self.ctx[0])

class BMNet():
    def __init__(self, bmctx, bmodel_path):
        self.net = ffi.new('bmnet_t *')
        bmodel = ffi.new('char[]', bmodel_path)
        lib.bmnet_register_bmodel(bmctx.ctx[0], bmodel, self.net)

    def __enter__(self):
        return self

    def __exit__(self, exc_type, exc_val, exc_tb):
        lib.bmnet_cleanup(self.net[0])

    def inference(self, input, output):
        output_info = ffi.new('bmnet_output_info_t *')
        lib.bmnet_get_output_info(self.net[0], output_info)
        lib.bmnet_inference(self.net[0], ffi.from_buffer(input), ffi.from_buffer(output))

    def set_input_shape(self, input_shape):
        shape = ffi.new('shape_t *')
        shape.dim = input_shape.shape[0]
        shape.n = input_shape[0]
        shape.c = input_shape[1]
        shape.h = input_shape[2]
        shape.w = input_shape[3]
        lib.bmnet_set_input_shape(self.net[0], shape[0])

    def get_output_size(self):
        output_info = ffi.new('bmnet_output_info_t *')
        lib.bmnet_get_output_info(self.net[0], output_info)
        return output_info.output_size

    def get_input_threshold(self):
        return lib.bmnet_get_input_threshold(self.net[0])
