//
//  AppleFusedStorageBSDClient.cpp
//  AppleFusedKernelRamdisk
//
//  Created by rms on 5/24/13.
//  Copyright (c) 2013 rms. All rights reserved.
//

#include "AppleFusedStorageBSDClient.h"

#define super IOService
OSDefineMetaClassAndStructors(AppleFusedStorageBSDClient, IOService);

static int __frd_close(__unused dev_t dev, __unused int flags, __unused int devtype, __unused struct proc *p);
static int __frd_open(dev_t dev, int flags, __unused int devtype, __unused struct proc *p);
static int __frd_rwio(dev_t dev, struct uio *uio, __unused int ioflag);
static void __frd_strategy(struct buf *bp);
static int __frd_bioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p);
static int __frd_cioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p);
static int __frd_ioctl(dev_t dev, u_long cmd, caddr_t data, __unused int flag, struct proc *p, int is_char);
static int __frd_size(dev_t dev);

uint8_t *fusedData;
uint64_t fusedDataLength;

#define STOR_LOG \
    IOLog("[%s] ", __PRETTY_FUNCTION__), IOLog

static struct bdevsw bsdClientBdevsw = {
    __frd_open, // open
    __frd_close, // close
    __frd_strategy, // strategy
    __frd_bioctl, // ioctl
    eno_dump, // dump
    __frd_size, // psize
    D_DISK     // d_type
};

static struct cdevsw bsdClientCdevsw = {
	/* open */	__frd_open,
	/* close */	__frd_close,
	/* read */	__frd_rwio,
	/* write */	__frd_rwio,
	/* ioctl */	__frd_cioctl,
	/* stop */	eno_stop,
	/* reset */	eno_reset,
	/* ttys */	NULL,
	/* select */	eno_select,
	/* mmap */	eno_mmap,
	/* strategy */	eno_strat,
	/* getc */	eno_getc,
	/* putc */	eno_putc,
	/* flags */	D_DISK,
};

static int __frd_close(__unused dev_t dev, __unused int flags,
                       __unused int devtype, __unused struct proc *p)
{
    STOR_LOG("entering\n");
    return 0;
}

static int __frd_open(dev_t dev, int flags, __unused int devtype, __unused struct proc *p)
{
    STOR_LOG("entering\n");
    if (flags & FWRITE)
        return EACCES;
    return 0;
}

static int __frd_rwio(dev_t dev, struct uio *uio, __unused int ioflag)
{
    addr64_t		mdata;
    int 			status;

    if(!uio)
        return ENOENT;

    STOR_LOG("entering\n");
    
    mdata = uio->uio_offset + (addr64_t)fusedData;	/* Point to the area in "file" */
    
    STOR_LOG("uio_offset: %lld\n", uio->uio_offset);
    
	status = uiomove64(mdata, uio_resid(uio), uio);		/* Move the data */

	return (status);
}

static void __frd_strategy(struct buf *bp) {
	vm_offset_t vaddr, blkoff;
	addr64_t fvaddr;
    
    STOR_LOG("entering\n");
    
	buf_setresid(bp, buf_count(bp));						/* Set byte count */
	
	blkoff = buf_blkno(bp) * DEV_BSIZE;		/* Get offset into file */
    
    /*
     *	Note that reading past end is an error, but reading at end is an EOF.  For these
     *	we just return with resid == count.
     */
    
	if (blkoff >= (fusedDataLength)) {			/* Are they trying to read/write at/after end? */
		if(blkoff != (fusedDataLength)) {		/* Are we trying to read after EOF? */
            buf_seterror(bp, EINVAL);						/* Yeah, this is an error */
		}
		buf_biodone(bp);								/* Return */
		return;
	}
    
	if ((blkoff + buf_count(bp)) > (fusedDataLength)) {		/* Will this read go past end? */
		buf_setcount(bp, ((fusedDataLength << 12) - blkoff));	/* Yes, trim to max */
	}
	/*
	 * make sure the buffer's data area is
	 * accessible
	 */
	if (buf_map(bp, (caddr_t *)&vaddr))
        panic("ramstrategy: buf_map failed\n");
    
	fvaddr = (addr64_t)(fusedData) + blkoff;		/* Point to offset into ram disk */
    
	if (buf_flags(bp) & B_READ) {					/* Is this a read? */
        bcopy((void *)((uintptr_t)fvaddr),
              (void *)vaddr, (size_t)buf_count(bp));	 /* This is virtual, just get the data */
	}
	else {												/* This is a write */
		bcopy((void *)vaddr, (void *)((uintptr_t)fvaddr),
                  (size_t)buf_count(bp));
	}
    
    /*
	 * buf_unmap takes care of all the cases
	 * it will unmap the buffer from kernel
	 * virtual space if that was the state
	 * when we mapped it.
	 */
	buf_unmap(bp);
    
	buf_setresid(bp, 0);									/* Nothing more to do */
	buf_biodone(bp);									/* Say we've finished */
}

static int __frd_bioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p) {
    STOR_LOG("entering\n");
	return (__frd_ioctl(dev, cmd, data, flag, p, 0));
}

static int __frd_cioctl(dev_t dev, u_long cmd, caddr_t data, int flag, struct proc *p) {
    STOR_LOG("entering\n");
	return (__frd_ioctl(dev, cmd, data, flag, p, 1));
}


static int __frd_ioctl(dev_t dev, u_long cmd, caddr_t data, __unused int flag,
					 struct proc *p, int is_char) {
	int error;
	u_int32_t *f;
	u_int64_t *o;
    
    STOR_LOG("entering\n");
    
	error = proc_suser(p);			/* Are we superman? */
	if (error) return (error);							/* Nope... */
    
	f = (u_int32_t*)data;
	o = (u_int64_t *)data;
    
	switch (cmd) {
            
		case DKIOCGETMAXBLOCKCOUNTREAD:
			*o = 32;
			break;
            
		case DKIOCGETMAXBLOCKCOUNTWRITE:
			*o = 32;
			break;
            
		case DKIOCGETMAXSEGMENTCOUNTREAD:
			*o = 32;
			break;
            
		case DKIOCGETMAXSEGMENTCOUNTWRITE:
			*o = 32;
			break;
            
		case DKIOCGETBLOCKSIZE:
			*f = DEV_BSIZE;
			break;
            
		case DKIOCSETBLOCKSIZE:
            return EINVAL;
			break;
			
		case DKIOCISWRITABLE:
			*f = 0;
			break;
			
		case DKIOCGETBLOCKCOUNT32:
			*f = ((fusedDataLength) + DEV_BSIZE - 1) / DEV_BSIZE;
			break;
			
		case DKIOCGETBLOCKCOUNT:
			*o = ((fusedDataLength) + DEV_BSIZE - 1) / DEV_BSIZE;
			break;
			
		default:
			error = ENOTTY;
			break;
	}
	return(error);
}


static int __frd_size(dev_t dev) {
    STOR_LOG("entering\n");
    return DEV_BSIZE;
}

IOService* AppleFusedStorageBSDClient::probe(IOService *provider, SInt32 *score) {
    return this;
}

bool AppleFusedStorageBSDClient::start(IOService* provider) {
    void* node;

    IOLog("Starting fused kernel storage ramdisk bsd provider\n");
    
    // There should really be a check to make sure more than one does not exist.
    int major = bdevsw_add(14, &bsdClientBdevsw);
    node = devfs_make_node(makedev(14, 1), DEVFS_BLOCK, 0, 0, 0644, "frd0");
    _bdevNode = node;
    IOLog("frd0 node at %p, major: %d\n", node, major);
    
    major = cdevsw_add(14, &bsdClientCdevsw);
    node = devfs_make_node(makedev(14, 2), DEVFS_CHAR, 0, 0, 0644, "rfrd0");
    _cdevNode = node;
    IOLog("rfrd0 node at %p, major: %d\n", node, major);
    
    fusedData = (uint8_t*)IOMalloc(1048576);
    if(!fusedData) {
        panic("unable to make fused data");
    }
    fusedDataLength = 1048576;
    bzero(fusedData, (size_t)fusedDataLength);
    
    provider->setProperty(kIOBSDNameKey, "frd0");
    provider->setProperty(kIOBSDMajorKey, 14,   32);           // ("BSD Major")
    provider->setProperty(kIOBSDMinorKey, 1,  32);           // ("BSD Minor")

    registerService();

    // @TODO
    return true;
}
