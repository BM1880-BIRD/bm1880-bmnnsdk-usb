#!/bin/sh

if [ `id -u` -ne 0 ];then
    echo "ERROR: must be run as root"
    exit 1
fi

[ -d /opt/bmtap2/bm1880-usb_1.0.2 ] && rm -rf /opt/bmtap2/bm1880-usb_1.0.2

mkdir -p -m 755 /opt/bmtap2/bm1880-usb_1.0.2
cp * /opt/bmtap2/bm1880-usb_1.0.2 -r

if test "xusb" != "xsoc"; then
    os=`awk -F= '$1=="ID" { print $2 ;}' /etc/os-release`
    os=`echo $os | sed 's/\"//g' `
    echo "You are running on $os"
fi

if [ -f /.dockerenv ]; then
    echo "in Docker environment!"
    ln -sf /opt/bmtap2/bm1880-usb_1.0.2/lib/usb /opt/bmtap2/bm1880-usb_1.0.2/library
elif test "xusb" = "xpcie"; then
    # install driver
    pwd=`pwd`
    cd /opt/bmtap2/bm1880-usb_1.0.2/driver

    if [ x$os = x"ubuntu" ]; then
        dpkg -i bmdnn-dkms_1.0.2_*.deb || return $?
    elif [ x$os = x"fedora" ] || [ x$os = x"centos" ] || [ x$os = x"redhat" ]; then
        rpm -ivh bmdnn-1.0.2-*.rpm || return $?
    else
        echo "Linux distribution $os does not supported!!!"
        exit 1
    fi

    modprobe bmdnn || return $?
    cd ${pwd}

    # link so
    ln -sf /opt/bmtap2/bm1880-usb_1.0.2/lib/usb /opt/bmtap2/bm1880-usb_1.0.2/library
elif test "xusb" = "xsoc"; then
    bmnpu_folder="/lib/modules/$(uname -r)/bmnpu"
    mkdir -p -m 755 $bmnpu_folder
    cp /opt/bmtap2/bm1880-usb_1.0.2/driver/bmnpu.ko $bmnpu_folder -f
    depmod -a
    modprobe bmnpu
    cp /opt/bmtap2/bm1880-usb_1.0.2/driver/S60bmnpu /etc/init.d/ -f
    ln -sf /opt/bmtap2/bm1880-usb_1.0.2/lib/usb /opt/bmtap2/bm1880-usb_1.0.2/library
elif test "xusb" = "xusb"; then
    cp /opt/bmtap2/bm1880-usb_1.0.2/etc/51-bm1880-usb-stick.rules /etc/udev/rules.d/ -f
    /etc/init.d/udev restart
    
    # link so
    ln -sf /opt/bmtap2/bm1880-usb_1.0.2/lib/usb /opt/bmtap2/bm1880-usb_1.0.2/library
fi

#create symlinks to library/binary/include
pwd=`pwd`
cd /opt/bmtap2/bm1880-usb_1.0.2/library
if [ x$os = x"centos" ]; then
    for file in `ls`
    do
        ln -sf /opt/bmtap2/bm1880-usb_1.0.2/library/${file} /usr/lib64/${file}
    done
    ln -sf /opt/bmtap2/bm1880-usb_1.0.2/library/bm1682_bmdnn.bin /usr/lib/bm1682_bmdnn.bin
else
    for file in `ls`
    do
        ln -sf /opt/bmtap2/bm1880-usb_1.0.2/library/${file} /usr/lib/${file}
    done
fi

cd /opt/bmtap2/bm1880-usb_1.0.2/bin
for binary in `ls`
do
    ln -sf /opt/bmtap2/bm1880-usb_1.0.2/bin/${binary} /usr/bin/${binary}
done
cd ${pwd}
[ -d /usr/include ] || mkdir -p /usr/include
ln -sf /opt/bmtap2/bm1880-usb_1.0.2/include /usr/include/bmtap2

rm -f /opt/bmtap2/bm1880-usb_1.0.2/install.sh

echo ""
echo "Bitmain Deep Learning SDK (bmtap2) for bm1880-usb"
echo "Installation successful."
echo "Installation path is /opt/bmtap2/bm1880-usb_1.0.2."
echo "We hope that you enjoy using it."
