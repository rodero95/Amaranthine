//
//  AppleSamsungSerialBSDClient.cpp
//  AppleSamsungSerial
//
//  Created by rms on 5/23/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#define KERNEL_PRIVATE 1
#include "AppleSamsungSerialBSDClient.h"
#include <miscfs/devfs/devfs.h>
#include <sys/conf.h>

#define kIOTTYSuffixKey "IOTTYSuffix"

#define super IOService
OSDefineMetaClassAndStructors(AppleSamsungSerialBSDClient, IOService);

static struct cdevsw bsdClientCdevsw = {
	NULL,           /* open */
	NULL,			/* close */
	NULL,			/* read */
	NULL,			/* write */
	NULL,			/* ioctl */
	NULL,           /* stop */
	NULL,           /* reset */
	NULL,			/* tty's */
	NULL,			/* select */
	NULL,			/* mmap */
	NULL,			/* strategy */
	NULL,			/* getc */
	NULL,			/* putc */
	0				/* type */
};

bool AppleSamsungSerialBSDClient::start(IOService *provider)
{
	void* node;
    
    int major = cdevsw_add(-24, &bsdClientCdevsw);
	node = devfs_make_node(makedev(major, 0), 0, 0, 0, 0666, "tty.samsung-%s", provider->getProvider()->getName());
    
	if (!node) {
		return false;
	}
    
	_node = node;
    
	return true;
}
