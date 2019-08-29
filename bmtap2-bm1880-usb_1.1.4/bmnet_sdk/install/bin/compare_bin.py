#!/usr/bin/env python2
##
## Copyright (C) Bitmain Technologies Inc.
## All Rights Reserved.
##
import os
import sys
import numpy as np

def compare(f0, f1, data_type, epsilon):
    d0 = np.fromfile(f0, dtype = data_type)
    d1 = np.fromfile(f1, dtype = data_type)
    l0 = len(d0)
    l1 = len(d1)

    if l0 < l1:
        d2 = d1[(l0+1):]
        d1 = d1[:l0]

    if l0 > l1:
        d2 = d0[(l1+1):]
        d0 = d0[:l1]

    if l0 != l1:
	print("WARNING:")
        raise Exception("  The sizes of the two binaries are not same (", l0, "vs", l1, ")!")      

    diff = np.abs(d0 - d1)
    print diff
    '''
    for i in range(len(diff)):
        if diff[i] > 0:
           print("d0/d1 = %d,%d" %(d0[i],d1[i]))
    '''
    num_diff = np.sum(diff > epsilon)

    if num_diff > 0:
        msg = "Result %d/%d mismatch @ epsilon = %f." %(num_diff, len(d0), epsilon)
        raise Exception(msg)

    print("Result matched @ epsilon = %f" %(epsilon))

def faster_rcnn_compare(f0, f1, epsilon):
    d0 = np.fromfile(f0, np.int8)
    d1 = np.fromfile(f1, np.int8)
    l0 = len(d0)
    l1 = len(d1)
    if l0 != l1:
	print("WARNING:")
        raise Exception("  The sizes of the two binaries are not same (", l0, "vs", l1, ")!")

    #bbox int8
    bbox_pred_d0 = d0[6000:31200]
    bbox_pred_d1 = d1[6000:31200]
    diff = np.abs(bbox_pred_d0 - bbox_pred_d1)
    print diff
    int8_num_diff = np.sum(diff > 0)
    msg_int8=""
    if int8_num_diff > 0:
        msg_int8 = "bbox pred Result %d/%d mismatch @ epsilon = 0." %(int8_num_diff, len(bbox_pred_d0))

    d0 = np.fromfile(f0, np.float32)
    d1 = np.fromfile(f1, np.float32)
    #rois float32
    rois_d0 = d0[0:1500]
    rois_d1 = d1[0:1500]
    diff1 = np.fabs(rois_d0 - rois_d1)
    print diff1
    cls_prob_d0 = d0[7800:]
    cls_prob_d1 = d1[7800:]
    diff2 = np.fabs(cls_prob_d0 - cls_prob_d1)
    print diff2
    float_num_diff = np.sum(diff1 > epsilon) + np.sum(diff2 > epsilon)
    msg_float = ""
    if float_num_diff > 0:
        msg_float = "rois and cls_prob Result %d/%d mismatch @ epsilon = %f." %(float_num_diff, len(rois_d0) + len(cls_prob_d0), epsilon)

    if int8_num_diff > 0 or float_num_diff > 0:
        raise Exception(msg_int8 + msg_float)

    print("Result matched @ epsilon = %f" %(epsilon))

def rfcn_compare(f0, f1, epsilon):
    d0 = np.fromfile(f0, np.int8)
    d1 = np.fromfile(f1, np.int8)
    l0 = len(d0)
    l1 = len(d1)
    if l0 != l1:
	print("WARNING:")
        raise Exception("  The sizes of the two binaries are not same (", l0, "vs", l1, ")!")

    #bbox int8
    bbox_pred_d0 = d0[31200:]
    bbox_pred_d1 = d1[31200:]
    diff = np.abs(bbox_pred_d0 - bbox_pred_d1)
    print diff
    int8_num_diff = np.sum(diff > 0)
    msg_int8=""
    if int8_num_diff > 0:
        msg_int8 = "bbox pred Result %d/%d mismatch @ epsilon = 0." %(int8_num_diff, len(bbox_pred_d0))

    d0 = np.fromfile(f0, np.float32)
    d1 = np.fromfile(f1, np.float32)
    #rois float32
    rois_d0 = d0[0:1500]
    rois_d1 = d1[0:1500]
    diff1 = np.fabs(rois_d0 - rois_d1)
    print diff1
    cls_prob_d0 = d0[1500:7800]
    cls_prob_d1 = d1[1500:7800]
    diff2 = np.fabs(cls_prob_d0 - cls_prob_d1)
    print diff2
    float_num_diff = np.sum(diff1 > epsilon) + np.sum(diff2 > epsilon)
    msg_float = ""
    if float_num_diff > 0:
        msg_float = "rois and cls_prob Result %d/%d mismatch @ epsilon = %f." %(float_num_diff, len(rois_d0) + len(cls_prob_d0), epsilon)

    if int8_num_diff > 0 or float_num_diff > 0:
        raise Exception(msg_int8 + msg_float)

    print("Result matched @ epsilon = %f" %(epsilon))

if __name__ == '__main__':
    if len(sys.argv) < 4:
        print("Usage:  ./compare_bin.py Dtype file0.bin file1.bin [epsilon]")
        exit(1)

    epsilon = 0.00001
    try:
        data_type = sys.argv[1]
        f0 = sys.argv[2]
        f1 = sys.argv[3]
        if len(sys.argv) == 5:
            epsilon = float(sys.argv[4])
        print(f0, ' vs. ', f1)

        faster_rcnn_found = f0.find("faster_rcnn")
        rfcn_found = f0.find("rfcn")
        if faster_rcnn_found == -1:
            faster_rcnn_found = f1.find("faster_rcnn")
        if rfcn_found == -1:
            rfcn_found = f1.find("rfcn")

        if faster_rcnn_found > -1:
            faster_rcnn_compare(f0, f1, epsilon)
        elif rfcn_found > -1:
            rfcn_compare(f0, f1, epsilon)
        else:
            compare(f0, f1, data_type, epsilon)

    except Exception as e:
        print(e.message)
        exit(1)

    exit(0)
