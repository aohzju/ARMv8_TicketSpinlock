# ARMv8_TicketSpinlock
This small project implemented aarch64 ticket spinlock. The call to spinlock is nestable.

The spinlock code is in spinlock subfolder. The API header file is spinlock.h. You can copy the whole folder to your application and use it.

The demo application was developed on ARM FVP (fixed virtual platform) FVP_Base_RevC-2xAEMv8A. The demo activates 8 CPU cores, all run the same application to print a string. As there is only one UART port, a spinlock is used to arbitrate the access to the UART. The ticket spinlock ensure each core to get an even access to the UART.

 # Build and run
 The armclang toolchain is used to build this example. And the build script is CMake script. It's tested on ARM FVP FVP_Base_RevC-2xAEMv8A. Assuming your development environment is correctly set up, this is the steps to build:
 1. Create a build directory: mkdir build
 2. CD to build: cd build.
 3. cmake ../ 
 4. cmake --build . -j8
 
 Hopefully, you'll get ARMv8Spinlock.axf up to this point.
 
 To run the demo on FVP:
```
FVP_Base_RevC-2xAEMv8A -C bp.secure_memory=false -C bp.terminal_0.mode=raw -C bp.refcounter.non_arch_start_at_default=1 -C cluster0.gicv3.FIQEn-RAO=1 -C pctl.startup='0.1.*.*, 0.0.*.*' -a ./ARMv8Spinlock.axf
```
 
# ARM FVP
The virtual platform used in this application is FVP_Base_RevC-2xAEMv8A, which can be downloaded [here](https://developer.arm.com/tools-and-software/simulation-models/fixed-virtual-platforms)
