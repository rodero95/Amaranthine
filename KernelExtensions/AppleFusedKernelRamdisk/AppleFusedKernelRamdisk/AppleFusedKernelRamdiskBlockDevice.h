//
//  AppleFusedKernelRamdiskBlockDevice.h
//  AppleFusedKernelRamdisk
//
//  Created by rms on 5/25/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#ifndef __AppleFusedKernelRamdisk__AppleFusedKernelRamdiskBlockDevice__
#define __AppleFusedKernelRamdisk__AppleFusedKernelRamdiskBlockDevice__

#define KERNEL_PRIVATE 1
#include <mach/mach_types.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <IOKit/storage/IOStorage.h>
#include <IOKit/storage/IOBlockStorageDevice.h>
#include <IOKit/IOBufferMemoryDescriptor.h>

class AppleFusedStorageDevice;

class AppleFusedKernelRamdiskBlockDevice : public IOBlockStorageDevice {
    OSDeclareDefaultStructors(AppleFusedKernelRamdiskBlockDevice);
private:
    UInt64 _blockCount;
    AppleFusedStorageDevice*	 _provider;
public:
    virtual bool init(UInt64 diskSize, OSDictionary* properties = 0);
    virtual bool attach(IOService* provider);
    virtual void detach(IOService* provider);
    virtual IOReturn doEjectMedia(void);
    virtual IOReturn doFormatMedia(UInt64 byteCapacity);
    virtual UInt32 doGetFormatCapacities(UInt64 * capacities, UInt32 capacitiesMaxCount) const;
    virtual IOReturn doLockUnlockMedia(bool doLock);
    virtual IOReturn doSynchronizeCache(void);
    virtual char* getVendorString(void);
    virtual char* getProductString(void);
    virtual char* getRevisionString(void);
    virtual char* getAdditionalDeviceInfoString(void);
    virtual IOReturn reportBlockSize(UInt64 *blockSize);
    virtual IOReturn reportEjectability(bool *isEjectable);
    virtual IOReturn reportLockability(bool *isLockable);
    virtual IOReturn reportMaxValidBlock(UInt64 *maxBlock);
    virtual IOReturn reportMediaState(bool *mediaPresent,bool *changedState);
    virtual IOReturn reportPollRequirements(bool *pollRequired, bool *pollIsExpensive);
    virtual IOReturn reportRemovability(bool *isRemovable);
    virtual IOReturn reportWriteProtection(bool *isWriteProtected);
    virtual IOReturn getWriteCacheState(bool *enabled);
    virtual IOReturn setWriteCacheState(bool enabled);
    virtual IOReturn doAsyncReadWrite(IOMemoryDescriptor *buffer, UInt64 block, UInt64 nblks, IOStorageAttributes *attributes, IOStorageCompletion *completion);
};

#endif /* defined(__AppleFusedKernelRamdisk__AppleFusedKernelRamdiskBlockDevice__) */
