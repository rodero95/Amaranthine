//
//  AppleFusedStorageBSDClient.h
//  AppleFusedKernelRamdisk
//
//  Created by rms on 5/24/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#ifndef __AppleFusedKernelRamdisk__AppleFusedStorageBSDClient__
#define __AppleFusedKernelRamdisk__AppleFusedStorageBSDClient__

#define KERNEL_PRIVATE 1
#include <mach/mach_types.h>
#include <IOKit/IOLib.h>
#include <IOKit/IOService.h>
#include <sys/types.h>
#include <sys/conf.h>
#include <sys/uio.h>
#include <miscfs/devfs/devfs.h>
#include <IOKit/IOBSD.h>

#include <sys/param.h>
#include <sys/kernel.h>
#include <sys/mount.h>
#include <sys/namei.h>
#include <sys/proc.h>
#include <sys/buf.h>
#include <sys/malloc.h>
#include <sys/mount.h>
#include <sys/fcntl.h>
#include <sys/conf.h>
#include <sys/disk.h>
#include <sys/stat.h>
#include <sys/vm.h>
#include <sys/uio_internal.h>


class AppleFusedStorageBSDClient : IOService {
    OSDeclareDefaultStructors(AppleFusedStorageBSDClient);
private:
    dev_t deviceNumber;
    void* _bdevNode, *_cdevNode;
public:
    virtual IOService *probe (IOService *provider, SInt32 *score);
    virtual bool start (IOService *provider);
};

#endif /* defined(__AppleFusedKernelRamdisk__AppleFusedStorageBSDClient__) */
