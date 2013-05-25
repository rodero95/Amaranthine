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
#include <IOKit/IOBufferMemoryDescriptor.h>

class AppleFusedStorageDevice : public IOService {
    OSDeclareDefaultStructors(AppleFusedStorageDevice);
    
private:
	IOBufferMemoryDescriptor* _memoryDesc;
	void* _buffer;
	
public:
    virtual IOService *probe (IOService *provider, SInt32 *score);
    virtual bool start (IOService *provider);
    virtual IOByteCount performRead (IOMemoryDescriptor* dstDesc, UInt64 byteOffset, UInt64 byteCount);
    virtual IOByteCount performWrite (IOMemoryDescriptor* srcDesc, UInt64 byteOffset, UInt64 byteCount);

};

#define kDiskByteSize		(16*1024*1024)

#endif /* defined(__AppleFusedKernelRamdisk__AppleFusedStorageDevice__) */
