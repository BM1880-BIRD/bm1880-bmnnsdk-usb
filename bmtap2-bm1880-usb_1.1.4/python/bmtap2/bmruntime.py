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

    def set_input_shapes(self, input_shapes):
        shape_arr = []
        for i in range(len(input_shapes)):
            shape = ffi.new('shape_t *')
            shape.dim = input_shapes[i].shape[0]
            if shape.dim == 1:
                shape.n = input_shapes[i][0]
            elif shape.dim == 2:
                shape.n = input_shapes[i][0]
                shape.c = input_shapes[i][1]
            elif shape.dim == 3:
                shape.n = input_shapes[i][0]
                shape.c = input_shapes[i][1]
                shape.h = input_shapes[i][2]
            elif shape.dim == 4:
                shape.n = input_shapes[i][0]
                shape.c = input_shapes[i][1]
                shape.h = input_shapes[i][2]
                shape.w = input_shapes[i][3]
            shape_arr.append(shape[0])

        lib.bmnet_set_input_shape2(self.net[0], shape_arr, len(input_shapes))

    def get_output_size(self):
        output_info = ffi.new('bmnet_output_info_t *')
        lib.bmnet_get_output_info(self.net[0], output_info)
        return output_info.output_size

    def get_output_shape(self):
        output_info = ffi.new('bmnet_output_info_t *')
        lib.bmnet_get_output_info(self.net[0], output_info)
        output_shape = []
        for i in range(output_info.output_num):
            shape = output_info.shape_array[i]
            if shape.dim == 1:
                output_shape.append([shape.n])
            elif shape.dim == 2:
                output_shape.append([shape.n, shape.c])
            elif shape.dim == 3:
                output_shape.append([shape.n, shape.c, shape.h])
            elif shape.dim == 4:
                output_shape.append([shape.n, shape.c, shape.h, shape.w])
        return output_shape

    def get_output_threshold(self):
        output_info = ffi.new('bmnet_output_info_t *')
        lib.bmnet_get_output_info(self.net[0], output_info)
        output_threshold = []
        for i in range(output_info.output_num):
            output_threshold.append(output_info.threshold_array[i])
        return output_threshold

    def get_output_fmt(self):
        output_info = ffi.new('bmnet_output_info_t *')
        lib.bmnet_get_output_info(self.net[0], output_info)
        output_fmt = []
        for i in range(output_info.output_num):
            output_fmt.append(output_info.fmt_array[i])
        return output_fmt

    def get_input_shape():
        input_info = lib.bmnet_get_input_info(self.net[0])
        input_shape = []
        for i in range(input_info.input_num):
            shape = input_info.shape_array[i]
            if shape.dim == 1:
                input_shape.append([shape.n])
            elif shape.dim == 2:
                input_shape.append([shape.n, shape.c])
            elif shape.dim == 3:
                input_shape.append([shape.n, shape.c, shape.h])
            elif shape.dim == 4:
                input_shape.append([shape.n, shape.c, shape.h, shape.w])
        return input_shape

    def get_input_threshold(self):
        input_info = lib.bmnet_get_input_info(self.net[0])
        input_threshold = []
        for i in range(input_info.input_num):
            input_threshold.append(input_info.threshold_array[i])
        return input_threshold

    def get_input_size(self):
        input_info = lib.bmnet_get_input_info(self.net[0])
        return input_info.input_size

    def get_input_fmt(self):
        input_info = lib.bmnet_get_input_info(self.net[0])
        input_fmt = []
        for i in range(input_info.input_num):
            input_fmt.append(input_info.fmt_array[i])
        return input_fmt
