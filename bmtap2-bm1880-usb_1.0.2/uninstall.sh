#!/bin/sh

if [ `id -u` -ne 0 ];then
    echo "ERROR: must be run as root"
    exit 1
fi

if [ ! -d /opt/bmtap2/bm1880-usb_1.0.2 ]; then
    exit 0
fi

# remove symlinks
pwd=`pwd`
cd /opt/bmtap2/bm1880-usb_1.0.2/library/
for file in `ls`
do
    [ -L /usr/lib/${file} ] && rm -f /usr/lib/${file}
    [ -L /usr/lib64/${file} ] && rm -f /usr/lib64/${file}
done

cd /opt/bmtap2/bm1880-usb_1.0.2/bin
for binary in `ls`
do
    [ -L /usr/bin/${binary} ] && rm -f /usr/bin/${binary}
done
cd ${pwd}
[ -L /usr/include/bmtap2 ] && rm -f /usr/include/bmtap2

if test "xusb" = "xpcie"; then
    # remove driver
    os=`awk -F= '$1=="ID" { print $2 ;}' /etc/os-release`
    os=`echo $os | sed 's/\"//g' `
    echo "You are running on $os"

    modprobe -r bmdnn
    if [ x$os = x"ubuntu" ]; then
        dpkg -r bmdnn-dkms
    elif [ x$os = x"fedora" ] || [ x$os = x"centos" ] || [ x$os = x"redhat" ]; then
        rpm -e bmdnn
    else
        echo "Linux distribution $os does not supported!!!"
    fi
    [ -d /var/lib/dkms/bmdnn ] && rm -rf /var/lib/dkms/bmdnn
elif test "xusb" = "xsoc"; then
    modprobe -r bmnpu
    bmnpu_folder="/lib/modules/$(uname -r)/bmnpu"
    [ -d $bmnpu_folder ] && rm -rf $bmnpu_folder
    depmod -a
    rm -f /etc/init.d/S60bmnpu
elif test "xusb" = "xusb"; then
    rm -f /etc/udev/rules.d/51-bm1880-usb-stick.rules
fi

rm /opt/bmtap2/bm1880-usb_1.0.2 -rf

echo "Bitmain Deep Learning SDK (bmtap2) for bm1880-usb removed successfully."
