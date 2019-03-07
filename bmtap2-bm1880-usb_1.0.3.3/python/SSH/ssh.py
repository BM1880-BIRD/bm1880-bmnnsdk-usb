# ------------------------------------------
# SSH: Single Stage Headless Face Detector
# Demo
# by Mahyar Najibi
# ------------------------------------------

from __future__ import print_function
import os, sys
cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, '/lib'))
from argparse import ArgumentParser
from datasets.factory import get_imdb
from SSH.train import train_net, get_training_roidb
import numpy as np

cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, '../../caffe/python'))

import caffe

def SSH_Net(proto, model):
    net = caffe.Net(proto, model, caffe.TEST)

    # Prepare the data layer
    #imdb= get_imdb('wider_val')
    #roidb = get_training_roidb(imdb)
    #net.layers[0].set_roidb(roidb, 0)

    return net





