//
//  AppleSamsungSerialDevice.h
//  AppleSamsungSerial
//
//  Created by rms on 5/23/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#ifndef __AppleSamsungSerial__AppleSamsungSerialDevice__
#define __AppleSamsungSerial__AppleSamsungSerialDevice__

#include <mach/mach_types.h>
#include <IOKit/IOLib.h>

#include <IOKit/serial/IORS232SerialStreamSync.h>
#include <IOKit/serial/IOSerialKeys.h>

#include "AppleARMIO.h"

class AppleSamsungSerialDevice : ARMIODevice {
    OSDeclareDefaultStructors(AppleSamsungSerialDevice);
private:
    IOSerialStreamSync* _sync;
public:
    IOService *probe (IOService *provider, SInt32 *score);
    bool start (IOService *provider);
};

#endif /* defined(__AppleSamsungSerial__AppleSamsungSerialDevice__) */
