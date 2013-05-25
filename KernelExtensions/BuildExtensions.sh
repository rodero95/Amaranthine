#!/bin/sh

KEXTS="AppleARMPlatform IOSerialFamily AppleS5L8930XDevice AppleSamsungSerial AppleFusedKernelRamdisk IOStorageFamily msdosfs"
CURDIR=$(pwd)

for i in $KEXTS; 
	do cd $i; xcodebuild install -arch armv7 DSTROOT=$CURDIR/Root; cd ..;
done;


























