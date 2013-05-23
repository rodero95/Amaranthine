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
    PE_LOG("Initializing ARM platform expert.\n");
    if (!super::init(propTable)) {
        panic("IOPlatformExpert failed to initialize");
    }
    return true;
}

extern const IORegistryPlane* gIODTPlane;

bool ARMPlatformExpert::start(IOService *provider) {
    PE_LOG("Starting ARM platform expert, IOService at %p\n", provider);

    if(!super::start(provider)) {
        panic("IOPlatformExpert failed to start");
    }

    IOPrintPlane(gIODTPlane);
    IOLog("===");
    IOPrintPlane(gIOServicePlane);
    
    registerService();

    PE_LOG("Registered device with IOKit\n");

    return true;
}

bool ARMPlatformExpert::configure( IOService * provider )
{
    OSSet *		topLevel;
    OSDictionary *	dict;
    IOService * 	nub;
    
    PE_LOG("Called configure()");
    
    topLevel = OSDynamicCast( OSSet, getProperty("top-level"));

    if(topLevel) {
        while( (dict = OSDynamicCast( OSDictionary,
                                     topLevel->getAnyObject()))) {
            dict->retain();
            topLevel->removeObject( dict );
            nub = createNub( dict );
            if(0 == nub)
                continue;
            dict->release();
            PE_LOG("Nub: %p has name %s", nub, nub->getName());
            nub->attach( this );
            nub->registerService();
        }
    }
    
    return( true );
}

IOService* ARMPlatformExpert::probe(IOService *provider, SInt32* score) {
    return this;
}

bool ARMPlatformExpert::getMachineName(char *name, int maxLength) {
    return false;
}
