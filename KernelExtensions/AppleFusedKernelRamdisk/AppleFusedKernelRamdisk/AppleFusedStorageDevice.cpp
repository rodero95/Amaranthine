//
//  AppleFusedStorageDevice.cpp
//  AppleFusedKernelRamdisk
//
//  Created by rms on 5/24/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#include "AppleFusedStorageDevice.h"
#include "AppleFusedKernelRamdiskBlockDevice.h"

#define super IOService
OSDefineMetaClassAndStructors(AppleFusedStorageDevice, IOService);

#define STOR_LOG \
    IOLog("[%s] ", __PRETTY_FUNCTION__), IOLog

IOService* AppleFusedStorageDevice::probe(IOService *provider, SInt32 *score) {
    return this;
}

bool AppleFusedStorageDevice::start(IOService* provider) {
    if(!super::start(provider))
        return false;
    
    STOR_LOG("Starting fused kernel storage ramdisk service\n");
    
    _memoryDesc = IOBufferMemoryDescriptor::withCapacity(kDiskByteSize, kIODirectionOutIn);
	if (_memoryDesc == NULL)
		return false;
	_buffer = _memoryDesc->getBytesNoCopy();
	
    {
        AppleFusedKernelRamdiskBlockDevice* nub = NULL;
        bool res;
        
        nub = new AppleFusedKernelRamdiskBlockDevice;
        if(!nub) {
            panic("failed to create block device nub");
        }
        
        res = nub->init(kDiskByteSize);
        if(res == false) {
            panic("failed to initialize block device nub");
        }
        
        res = nub->attach(this);
        if(res == false) {
            panic("failed to attach block nub to root");
        }
        
        nub->registerService();
    }
    
    registerService();
    // @TODO
    return true;
}

IOByteCount AppleFusedStorageDevice::performRead (IOMemoryDescriptor* dstDesc, UInt64 byteOffset, UInt64 byteCount)
{
	return dstDesc->writeBytes(0, (void*)((uintptr_t)_buffer + byteOffset), byteCount);
}

IOByteCount AppleFusedStorageDevice::performWrite (IOMemoryDescriptor* srcDesc, UInt64 byteOffset, UInt64 byteCount)
{
	return srcDesc->readBytes(0, (void*)((uintptr_t)_buffer + byteOffset), byteCount);
}