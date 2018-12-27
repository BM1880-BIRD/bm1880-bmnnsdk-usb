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
        print("  The sizes of the two binaries are not same (", l0, "vs", l1, ")!")
        print("  Ignore the data after index", len(d0), "...")
        if d2.any() != 0.0:
            print("  The rest data contains non-zero value.")

    diff = np.abs(d0 - d1)
    num_diff = np.sum(diff > epsilon)

    if num_diff > 0:
        msg = "Result %d/%d mismatch @ epsilon = %f." %(num_diff, len(d0), epsilon)
        raise Exception(msg)

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
        compare(f0, f1, data_type, epsilon)

    except Exception as e:
        print(e.message)
        exit(1)

    exit(0)
