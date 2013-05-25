//
//  AppleFusedKernelRamdiskBlockDevice.cpp
//  AppleFusedKernelRamdisk
//
//  Created by rms on 5/25/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#include "AppleFusedStorageDevice.h"
#include "AppleFusedKernelRamdiskBlockDevice.h"
#define super IOBlockStorageDevice

OSDefineMetaClassAndStructors(AppleFusedKernelRamdiskBlockDevice, IOBlockStorageDevice)

#define kDiskBlockSize		512

bool AppleFusedKernelRamdiskBlockDevice::init(UInt64 diskSize, OSDictionary* properties)
{
	if (super::init(properties) == false)
		return false;
	
	_blockCount = diskSize / kDiskBlockSize;
	
	return true;
}

bool AppleFusedKernelRamdiskBlockDevice::attach (IOService* provider)
{
	if (super::attach(provider) == false)
		return false;
	
	_provider = OSDynamicCast(AppleFusedStorageDevice, provider);
	if (_provider == NULL)
		return false;
	
	return true;
}

void AppleFusedKernelRamdiskBlockDevice::detach(IOService* provider)
{
	if (_provider == provider)
		_provider = NULL;
	
	super::detach(provider);
}


IOReturn AppleFusedKernelRamdiskBlockDevice::doEjectMedia(void)
{
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::doFormatMedia(UInt64 byteCapacity)
{
	return kIOReturnSuccess;
}

UInt32 AppleFusedKernelRamdiskBlockDevice::doGetFormatCapacities(UInt64* capacities, UInt32 capacitiesMaxCount) const
{
	// Ensure that the array is sufficient to hold all our formats (we require 1 element).
	if ((capacities != NULL) && (capacitiesMaxCount < 1))
		return 0;               // Error, return an array size of 0.
	
	// The caller may provide a NULL array if it wishes to query the number of formats that we support.
	if (capacities != NULL)
		capacities[0] = _blockCount * kDiskBlockSize;
	return 1;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::doLockUnlockMedia(bool doLock)
{
	return kIOReturnUnsupported;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::doSynchronizeCache(void)
{
	return kIOReturnSuccess;
}

char* AppleFusedKernelRamdiskBlockDevice::getVendorString(void)
{
	return NULL;
}

char* AppleFusedKernelRamdiskBlockDevice::getProductString(void)
{
	return (char*)"AppleFusedKernelRamdisk";
}

char* AppleFusedKernelRamdiskBlockDevice::getRevisionString(void)
{
	return (char*)"1.0";
}

char* AppleFusedKernelRamdiskBlockDevice::getAdditionalDeviceInfoString(void)
{
	return NULL;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::reportBlockSize(UInt64 *blockSize)
{
	*blockSize = kDiskBlockSize;
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::reportEjectability(bool *isEjectable)
{
	*isEjectable = false;
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::reportLockability(bool *isLockable)
{
	*isLockable = false;
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::reportMaxValidBlock(UInt64 *maxBlock)
{
	*maxBlock = _blockCount-1;
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::reportMediaState(bool *mediaPresent, bool *changedState)
{
	*mediaPresent = true;
	*changedState = false;
	
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::reportPollRequirements(bool *pollRequired, bool *pollIsExpensive)
{
	*pollRequired = false;
	*pollIsExpensive = false;
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::reportRemovability(bool *isRemovable)
{
	*isRemovable = true;
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::reportWriteProtection(bool *isWriteProtected)
{
	*isWriteProtected = false;
	return kIOReturnSuccess;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::getWriteCacheState(bool *enabled)
{
	return kIOReturnUnsupported;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::setWriteCacheState(bool enabled)
{
	return kIOReturnUnsupported;
}

IOReturn AppleFusedKernelRamdiskBlockDevice::doAsyncReadWrite(IOMemoryDescriptor *buffer, UInt64 block, UInt64 nblks, IOStorageAttributes *attributes, IOStorageCompletion *completion)
{
	IODirection		direction;
	IOByteCount		actualByteCount;
	
	// Return errors for incoming I/O if we have been terminated
	if (isInactive() != false )
		return kIOReturnNotAttached;
	
	direction = buffer->getDirection();
	if ((direction != kIODirectionIn) && (direction != kIODirectionOut))
		return kIOReturnBadArgument;
	
	if ((block + nblks) > _blockCount)
		return kIOReturnBadArgument;
	
	if (direction == kIODirectionIn)
		actualByteCount = _provider->performRead(buffer, (block*kDiskBlockSize), (nblks*kDiskBlockSize));
	else
		actualByteCount = _provider->performWrite(buffer, (block*kDiskBlockSize), (nblks*kDiskBlockSize));
	
	(completion->action)(completion->target, completion->parameter, kIOReturnSuccess, actualByteCount);
	
	return kIOReturnSuccess;
}
