# ------------------------------------------
# SSH: Single Stage Headless Face Detector
# Demo
# by Mahyar Najibi
# ------------------------------------------

from __future__ import print_function
#from SSH.test import detect
import os, sys
cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, 'lib'))
from argparse import ArgumentParser
from utils.get_config import cfg_from_file, cfg, cfg_print
from datasets.factory import get_imdb
from SSH.train import train_net, get_training_roidb
import numpy as np

cur_dir = os.path.dirname(os.path.realpath(__file__))
sys.path.append(os.path.join(cur_dir, '../../caffe/python'))

import caffe

def parser():
    parser = ArgumentParser('SSH Loss Test!')
    parser.add_argument('--db', dest='db_name', help='Path to the image',
                        default='wider_val', type=str)
    parser.add_argument('--gpu',dest='gpu_id',help='The GPU ide to be used',
                        default=0,type=int)
    parser.add_argument('--proto',dest='prototxt',help='SSH caffe test prototxt',
                        #default='SSH/models/loss_tiny_ssh.prototxt',type=str)
                        default=os.path.join(cur_dir,'SSH/models/bmnet_loss.prototxt'),type=str)
    parser.add_argument('--model',dest='model',help='SSH trained caffemodel',
                        default='/data/release/bmnet_models/tiny_ssh/TinySSH_iter_210000.caffemodel',type=str)
    parser.add_argument('--out_path',dest='out_path',help='Output path for saving the figure',
                        default='data/demo',type=str)
    parser.add_argument('--cfg',dest='cfg',help='Config file to overwrite the default configs',
                        default=os.path.join(cur_dir,'SSH/configs/tiny.yml'),type=str)
    return parser.parse_args()

def SSH_Net(proto, model):
    net = caffe.Net(proto, model, caffe.TEST)

    # Prepare the data layer
    imdb= get_imdb('wider_val')
    roidb = get_training_roidb(imdb)
    net.layers[0].set_roidb(roidb, 0)
    
    return net

if __name__ == "__main__":

    # Parse arguments
    args = parser()

    # Load the external config
    if args.cfg is not None:
        cfg_from_file(args.cfg)
    # Print config file
    cfg_print(cfg)

    # Loading the network
    #cfg.GPU_ID = args.gpu_id
    caffe.set_mode_cpu()
    #caffe.set_device(args.gpu_id)
    print(args.model)
    assert os.path.isfile(args.prototxt),'Please provide a valid path for the prototxt!'
    assert os.path.isfile(args.model),'Please provide a valid path for the caffemodel!'

    print('Loading the network...', end="")
    net = caffe.Net(args.prototxt, args.model, caffe.TEST)
    net.name = 'SSH'
    print('Done!')

    # Set the random seed for numpy
    print(cfg.RNG_SEED)
    np.random.seed(cfg.RNG_SEED)
    #print("seed", cfg.RNG_SEED)

    # Prepare the training roidb
    #imdb= get_imdb(args.db_name)
    #roidb = get_training_roidb(imdb)
    #net.layers[0].set_roidb(roidb, 0)

    # Forward
    for i in range(5):
        blobs_out = net.forward()
        print(blobs_out['m1@ssh_cls_loss'], blobs_out['m2@ssh_cls_loss'], blobs_out['m3@ssh_cls_loss'])





