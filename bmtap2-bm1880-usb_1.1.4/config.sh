#!/bin/bash

if [ `id -u` -ne 0 ];then
    echo "ERROR: must be run as root"
    exit 1
fi

if [ ! -d /opt/bmtap2/bm1880-usb_1.1.4 ]; then
    exit 0
fi

function print_mode()
{
    mode=$(echo $(readlink /opt/bmtap2/bm1880-usb_1.1.4/library) | grep -E [a-zA-Z]+$ -o)
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

rm -f /opt/bmtap2/bm1880-usb_1.1.4/library
ln -sf /opt/bmtap2/bm1880-usb_1.1.4/lib/$1 /opt/bmtap2/bm1880-usb_1.1.4/library
print_mode

