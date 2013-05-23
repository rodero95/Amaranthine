//
//  AppleARMPE.h
//  AppleARMPlatform
//
//  Created by rms on 5/21/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#ifndef __AppleARMPlatform__AppleARMPE__
#define __AppleARMPlatform__AppleARMPE__

#include <mach/mach_types.h>
#include <IOKit/IOPlatformExpert.h>
#include "IOCPU.h"

class ARMPlatformExpert : public IOPlatformExpert {
    OSDeclareDefaultStructors(ARMPlatformExpert);
public:
    bool init(OSDictionary *propTable);
    IOService * probe(IOService *provider, SInt32 *score);
    bool start(IOService * provider);
    bool getMachineName(char *name, int maxLength);
    bool configure(IOService * provider);
};

#define PE_LOG \
    IOLog("[%s]: ", __PRETTY_FUNCTION__), IOLog

#endif /* defined(__AppleARMPlatform__AppleARMPE__) */
