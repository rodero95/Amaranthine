DIRS = KernelExtensions KernelBuilder

.PHONY: all clean

all:
	for i in $(DIRS); \
		do make  -C $$i; \
	done
clean:
	for i in $(DIRS); \
		do make -C $$i clean; \
	done


