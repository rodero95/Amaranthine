#!/bin/sh

KEXTS="AppleARMPlatform IOSerialFamily"
CURDIR=$(pwd)

for i in $KEXTS; 
	do cd $i; xcodebuild install -arch armv7 DSTROOT=$CURDIR/Root; cd ..;
done;


























