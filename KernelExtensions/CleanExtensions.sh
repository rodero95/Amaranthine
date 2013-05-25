#!/bin/sh

KEXTS="AppleARMPlatform IOSerialFamily AppleS5L8930XDevice AppleSamsungSerial AppleFusedKernelRamdisk msdosfs"
CURDIR=$(pwd)

for i in $KEXTS; 
	do cd $i; xcodebuild clean -arch armv7 DSTROOT=$CURDIR/Root; cd ..;
done;

rm -rf $CURDIR/Root


























