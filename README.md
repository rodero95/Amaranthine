Amaranthine
===========

Generic reimplementations of Apple drivers for S5L and also extra build utilities to allow kernel extensions
to be compiled for armv7. A hacked up SDK is required to work with this to create working kernel extensions
and other binaries.

I'll eventually upload a copy of my SDK somewhere else so that people can use it. I used the OS X 10.8 SDK
with the xnu-1699 source tree for generating export lists, these were used to form the System.kext plugins
used to build for ARM. I don't imagine this being so hard to generate if you have a kernel for your device
already.

The OS X xcspec builds for armv7 or x86_64. Very bad, I know, but it worked for building a lot of the projects
from opensource.apple.com. It's amazing what can be done with the resources Apple gives you for everything.

Fixing kxld to work with ARM is relatively simple, add support for ARM binaries in the kxld_object.c file
in the xnu source tree. Kextsymboltool requires an -arch armv7 parameter too. The System.kext should be
fully compatible with Darwin 11 from iOS 4.3/5.0. (I think.)

