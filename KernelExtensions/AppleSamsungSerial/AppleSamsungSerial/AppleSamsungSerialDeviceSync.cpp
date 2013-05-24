//
//  AppleSamsungSerialDeviceSync.cpp
//  AppleSamsungSerial
//
//  Created by rms on 5/23/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#include "AppleSamsungSerialDeviceSync.h"

#define SERIAL_LOG \
    IOLog("[%s] ", __PRETTY_FUNCTION__), IOLog

#define super ARMIODevice
OSDefineMetaClassAndStructors(AppleSamsungSerialDeviceSync, ARMIODevice)

bool AppleSamsungSerialDeviceSync::start(IOService *provider) {
    IOMemoryMap* memoryMap;
    uint32_t uartBase;
    
    if(!provider) {
        panic("provider should not be null");
    }
    
    memoryMap = provider->mapDeviceMemoryWithIndex(0);
    if(!memoryMap) {
        panic("failed to get physical device memory map");
    }
    
    uartBase = memoryMap->getPhysicalAddress();
    
    SERIAL_LOG("Detected uart at PA:0x%08x\n",  uartBase);
    
    memoryMap->release();
    
    registerService();

    return true;
}

IOService* AppleSamsungSerialDeviceSync::probe(IOService *provider, SInt32* score) {
    return super::probe(provider, score);
}

IOReturn AppleSamsungSerialDeviceSync::message(UInt32 type, IOService *provider, void *argument) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::acquirePort(bool sleep, void *refCon) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::releasePort(void *refCon) {
    return kIOReturnOffline;
}

UInt32 AppleSamsungSerialDeviceSync::getState(void *refCon) {
    return 0;
}

IOReturn AppleSamsungSerialDeviceSync::setState(UInt32 state, UInt32 mask, void *refCon) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::watchState(UInt32 *state, UInt32 mask, void *refCon) {
    return kIOReturnOffline;
}

UInt32 AppleSamsungSerialDeviceSync::nextEvent(void *refCon) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::executeEvent(UInt32 event, UInt32 data, void *refCon) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::requestEvent(UInt32 event, UInt32 *data, void *refCon) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::enqueueEvent(UInt32 event, UInt32 data, bool sleep, void *refCon) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::dequeueEvent(UInt32 *event, UInt32 *data, bool sleep, void *refCon) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::enqueueData(UInt8 *buffer, UInt32 size, UInt32 * count, bool sleep, void *refCon) {
    return kIOReturnOffline;
}

IOReturn AppleSamsungSerialDeviceSync::dequeueData(UInt8 *buffer, UInt32 size, UInt32 *count, UInt32 min, void *refCon) {
    return kIOReturnOffline;
}