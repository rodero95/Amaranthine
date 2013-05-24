//
//  AppleSamsungSerialBSDClient.h
//  AppleSamsungSerial
//
//  Created by rms on 5/23/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#ifndef __AppleSamsungSerial__AppleSamsungSerialBSDClient__
#define __AppleSamsungSerial__AppleSamsungSerialBSDClient__

#include <mach/mach_types.h>
#include <IOKit/IOLib.h>

#include <IOKit/serial/IOSerialDriverSync.h>
#include <IOKit/serial/IOSerialKeys.h>
#include <IOKit/serial/IORS232SerialStreamSync.h>
#include <IOKit/serial/IOSerialKeys.h>

#include "AppleARMIO.h"
#include "AppleSamsungSerialDeviceSync.h"

#include <sys/uio.h>

class AppleSamsungSerialBSDClient : public IOService {
    OSDeclareDefaultStructors(AppleSamsungSerialBSDClient);
private:
    dev_t _device;
	void* _node;
public:
    bool start(IOService *provider);
};

#endif /* defined(__AppleSamsungSerial__AppleSamsungSerialBSDClient__) */
