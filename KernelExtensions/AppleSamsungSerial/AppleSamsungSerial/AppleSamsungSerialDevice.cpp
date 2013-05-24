//
//  AppleSamsungSerialDevice.cpp
//  AppleSamsungSerial
//
//  Created by rms on 5/23/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#include "AppleSamsungSerialDevice.h"

#define super ARMIODevice
OSDefineMetaClassAndStructors(AppleSamsungSerialDevice, ARMIODevice);

IOService* AppleSamsungSerialDevice::probe(IOService *provider, SInt32* score) {
    return super::probe(provider, score);
}

bool AppleSamsungSerialDevice::start(IOService *provider) {
    return true;
}