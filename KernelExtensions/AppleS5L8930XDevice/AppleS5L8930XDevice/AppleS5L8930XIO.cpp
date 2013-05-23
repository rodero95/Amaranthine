//
//  AppleS5L8930XIO.cpp
//  AppleS5L8930XDevice
//
//  Created by rms on 5/23/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#include "AppleS5L8930XIO.h"

#define super IOService
OSDefineMetaClassAndStructors(AppleS5L8930XIO, ARMIO);

#define S5L_LOG \
    IOLog("[%s] ", __PRETTY_FUNCTION__), IOLog

bool AppleS5L8930XIO::init(OSDictionary* propTable) {
    if(!super::init(propTable)) {
        panic("failed to initialize super IOService\n");
    }
    S5L_LOG("Initializing AppleS5L8930XIO service\n");
    return true;
}

IOService* AppleS5L8930XIO::probe(IOService* provider, SInt32* score) {
    return this;
}

bool AppleS5L8930XIO::start(IOService* provider) {
    if(!super::start(provider)) {
        panic("failed to start super provider");
    }
    S5L_LOG("Publishing entries to IOService tree plane");
    publishBelow(provider);
    registerService();
    return true;
}
