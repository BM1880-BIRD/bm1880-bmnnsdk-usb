#!/bin/bash

if [ `id -u` -ne 0 ];then
    echo "ERROR: must be run as root"
    exit 1
fi

if [ ! -d /opt/bmtap2/bm1880-usb_1.0.3.1 ]; then
    exit 0
fi

function print_mode()
{
    mode=$(echo $(readlink /opt/bmtap2/bm1880-usb_1.0.3.1/library) | grep -E [a-zA-Z]+$ -o)
    echo "current mode: ${mode}"
}


if [ x$1 = x ]; then
    echo "Usage: $0 cmodel/usb"
    print_mode
    exit 0
fi

if [ x$1 != x"usb" ] && [ x$1 != x"cmodel" ]; then
    echo "$0 cmodel/usb"
    print_mode
    exit 1
fi

rm -f /opt/bmtap2/bm1880-usb_1.0.3.1/library
ln -sf /opt/bmtap2/bm1880-usb_1.0.3.1/lib/$1 /opt/bmtap2/bm1880-usb_1.0.3.1/library
print_mode

