import onnx
import numpy as np
from caffe2.proto import caffe2_legacy_pb2
import lmdb
import py_onnx_cal

LMDB_PATH = '/data/dataset/imagenet/ilsvrc12_val_lmdb/'
ONNX_PATH = '/data/release/onnx_models2/resnet50/model.onnx'
ITERATION = 10
BATCH = 4

####### image process
# the image should be in [:,C,H,W]
class ImageProcessBase(object):
    def __init__(self):
        pass

class CropCenterOP(ImageProcessBase):
    def __init__(self,width,height):
        self.width=width
        self.height=height
    def __call__(self,images):
        image_num,c,y,x=images.shape
        start_x=x//2-(self.width//2)
        start_y=y//2-(self.height//2)
        return images[:,:,start_y:start_y+self.height,start_x:start_x+self.width]

class NormalizeOP(ImageProcessBase):
    def __init__(self,mean,std):
        self.mean=mean=np.array(mean).reshape(1,3,1,1).astype(np.float32)
        self.std=mean=np.array(std).reshape(1,3,1,1).astype(np.float32)
    def __call__(self,images):
        return (images-self.mean)/self.std

class NormalizeMNIST(ImageProcessBase):
    def __init__(self,mean,std):
        self.mean=mean=np.array(mean).reshape(1,1,1,1).astype(np.float32)
        self.std=mean=np.array(std).reshape(1,1,1,1).astype(np.float32)
    def __call__(self,images):
        return (images-self.mean)/self.std

class MeanOP(ImageProcessBase):
    def __init__(self,mean):
        self.mean=mean=np.array(mean).reshape(1,3,1,1).astype(np.float32)
    def __call__(self,images):
        return images-self.mean

def run_calibration():
    onnx_model = onnx.load(ONNX_PATH)
    if not onnx_model:
        print("load onnx file failed. path:",onnx_file)
        return
    print("load onnx model end")

    lmdb_env = lmdb.open(LMDB_PATH)
    if not lmdb_env:
        print("lmdb from %s is not valid"%(LMDB_PATH))
        return

    lmdb_txn = lmdb_env.begin()
    lmdb_cursor = lmdb_txn.cursor()
    datum = caffe2_legacy_pb2.CaffeDatum()
    lmdb_cursor.first()
    cal = py_onnx_cal.Calibration()
    for loop_count in range(0, ITERATION):
        for batch in range(0, BATCH):
            value = lmdb_cursor.value()
            datum.ParseFromString(value)
            label = datum.label
            float_image = np.frombuffer(datum.data,dtype=np.uint8).reshape(1,datum.channels,datum.height,datum.width).astype(np.float32)
            # Image pre-process
            print(float_image)
            crop = CropCenterOP(224, 224)
            float_image = crop(float_image)
            mean = MeanOP([104,117,123])
            float_data = mean(float_image)
            print("shape = ", float_data.shape)
            if (batch == 0):
                input_data = float_data
            else:
                input_data = np.append(input_data, float_data, axis=0)
            lmdb_cursor.next()
        # Feed inputs for calibration
        cal.feed('data_0', input_data)

    onnx_cal_str = cal.profile(onnx_model.SerializeToString(), ITERATION)
    onnx.save(onnx.load_from_string(onnx_cal_str), './resnet50.cal.onnx')

    # Extract outputs
    for iter in range(0, ITERATION):
      out = cal.fetch('prob_1', iter)
      if (iter == 0):
          total_outs = out
      else:
          total_outs = np.append(total_outs, out, axis=0)
    print("prob_1 = ", total_outs)

def main():
    run_calibration()

if __name__ == '__main__':
    main()
