//
//  AppleFusedStorageDevice.cpp
//  AppleFusedKernelRamdisk
//
//  Created by rms on 5/24/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#include "AppleFusedStorageDevice.h"

#define super IOService
OSDefineMetaClassAndStructors(AppleFusedStorageDevice, IOService);

#define STOR_LOG \
    IOLog("[%s] ", __PRETTY_FUNCTION__), IOLog

IOService* AppleFusedStorageDevice::probe(IOService *provider, SInt32 *score) {
    return this;
}

bool AppleFusedStorageDevice::start(IOService* provider) {
    STOR_LOG("Starting fused kernel storage ramdisk service\n");
    registerService();
    // @TODO
    return true;
}
