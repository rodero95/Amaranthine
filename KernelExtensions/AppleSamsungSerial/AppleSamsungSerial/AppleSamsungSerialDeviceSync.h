//
//  AppleSamsungSerialDeviceSync.h
//  AppleSamsungSerial
//
//  Created by rms on 5/23/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#ifndef __AppleSamsungSerial__AppleSamsungSerialDeviceSync__
#define __AppleSamsungSerial__AppleSamsungSerialDeviceSync__

#include <mach/mach_types.h>
#include <IOKit/IOLib.h>

#include <IOKit/serial/IOSerialDriverSync.h>
#include <IOKit/serial/IOSerialKeys.h>
#include <IOKit/serial/IORS232SerialStreamSync.h>
#include <IOKit/serial/IOSerialKeys.h>

#include "AppleARMIO.h"

class  AppleSamsungSerialDeviceSync : public ARMIODevice {
    OSDeclareDefaultStructors(AppleSamsungSerialDeviceSync);
public:
    virtual IOService *probe (IOService *provider, SInt32 *score);
    virtual bool start (IOService *provider);
    
    virtual IOReturn message(UInt32 type, IOService *provider, void *argument = 0);
    
    virtual IOReturn acquirePort (bool sleep, void *refCon);
    virtual IOReturn releasePort (void *refCon);
    
    virtual UInt32 getState (void *refCon);
    virtual IOReturn setState (UInt32 state, UInt32 mask, void *refCon);
    virtual IOReturn watchState (UInt32 *state, UInt32 mask, void *refCon);
    
    virtual UInt32 nextEvent (void *refCon);
    virtual IOReturn executeEvent (UInt32 event, UInt32 data, void *refCon);
    virtual IOReturn requestEvent (UInt32 event, UInt32 *data, void *refCon);
    virtual IOReturn enqueueEvent (UInt32 event, UInt32 data, bool sleep, void *refCon);
    virtual IOReturn dequeueEvent (UInt32 *event, UInt32 *data, bool sleep, void *refCon);
    
    virtual IOReturn enqueueData (UInt8 *buffer, UInt32 size, UInt32 * count, bool sleep, void *refCon);
    virtual IOReturn dequeueData (UInt8 *buffer, UInt32 size, UInt32 *count, UInt32 min, void *refCon);
};

#endif /* defined(__AppleSamsungSerial__AppleSamsungSerialDeviceSync__) */
