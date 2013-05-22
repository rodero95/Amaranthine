export SRCROOT=$(shell /bin/pwd)
export VERSDIR=$(shell /bin/pwd)
export DSTROOT=$(SRCROOT)/DSTROOT
export OBJROOT=$(SRCROOT)/OBJROOT

.PHONY: extras all

DIRS = \
	tools

all:	$(DIRS) extras
	for i in $(DIRS); \
		do make -C $$i; \
	done;
	make -C config COMPONENT=config TARGET_CONFIGS="RELEASE ARM S5L8930X" ARCH_CONFIGS=ARM

extras:
	make -C extras/libkmod
	make -C libkern/kxld