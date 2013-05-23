.PHONY: all clean
all:
	sudo kextcache -K ../mach --prelinked-kernel mach_prelinked ../Objects/Kernel-LinkObjects/System/Library/Extensions/System.kext -arch armv7 ../KernelExtensions/Root/System/Library/Extensions -v 6 -z
	dd if=mach_prelinked of=mach_prelinked.stripped bs=1 skip=28
	./xpwntool mach_prelinked.stripped mach_kernel.img3 -t Template.img3
clean:
	rm -f mach_prelinked mach_prelinked.stripped mach_kernel.img3
