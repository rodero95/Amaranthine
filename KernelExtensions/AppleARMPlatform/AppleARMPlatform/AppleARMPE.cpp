//
//  AppleARMPE.cpp
//  AppleARMPlatform
//
//  Created by rms on 5/21/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#include "AppleARMPE.h"

#define HIGH_SCORE  100000
#define super IOPlatformExpert
OSDefineMetaClassAndStructors(ARMPlatformExpert, IOPlatformExpert);

bool ARMPlatformExpert::init(OSDictionary *propTable) {
    IOLog("Hello PlatformExpert for S5L!\n");
    if (!super::init(propTable)) {
        return false;
    }
    return true;
}

bool ARMPlatformExpert::start(IOService *provider) {
    if(!super::start(provider)) {
        return false;
    }

    IOLog("\n\n\n === HELLO FROM THE FUCKING WORLD OF KERNEL LAND === \n\n\n");
    while(1);
    
    registerService();
    return true;
}

IOService* ARMPlatformExpert::probe(IOService *provider, SInt32* score) {
    *score = HIGH_SCORE;
    return this;
}

bool ARMPlatformExpert::getMachineName(char *name, int maxLength) {
    if(name != NULL) {
        strncpy(name, "N90AP", sizeof("N90AP"));
    }
    return true;
}