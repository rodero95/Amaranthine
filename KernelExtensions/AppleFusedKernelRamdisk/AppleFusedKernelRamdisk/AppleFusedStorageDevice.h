//
//  AppleFusedStorageDevice.h
//  AppleFusedKernelRamdisk
//
//  Created by rms on 5/24/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#ifndef __AppleFusedKernelRamdisk__AppleFusedStorageDevice__
#define __AppleFusedKernelRamdisk__AppleFusedStorageDevice__

#define KERNEL_PRIVATE 1
#include <mach/mach_types.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/storage/IOStorage.h>

class AppleFusedStorageDevice : IOService {
    OSDeclareDefaultStructors(AppleFusedStorageDevice);
public:
    virtual IOService *probe (IOService *provider, SInt32 *score);
    virtual bool start (IOService *provider);
};

#endif /* defined(__AppleFusedKernelRamdisk__AppleFusedStorageDevice__) */
