cmake_minimum_required(VERSION 3.15)

#Cross compiling toolchain:
set(CMAKE_TOOLCHAIN_FILE "toolchain.armclang" CACHE PATH "")

#top project:
project(ARMv8Spinlock VERSION 1.0
			LANGUAGES C CXX ASM)

#Options:
include(CMakeDependentOption)
option(USE_ARM_LIB_STARTUP "Use ARM Library's __main for scatter loading"  ON)

#Generate configuration header file:
configure_file(config.h.in  config.h)

#the top app target:
add_executable(ARMv8Spinlock 
						asm/basehw.S
						asm/reset.S
						asm/vectors.S
						my__main.c
						uart.c
						appmain.c
						spinlock/spinlock_asm.S
						spinlock/spinlock.c
				)


target_include_directories(ARMv8Spinlock PRIVATE ${CMAKE_CURRENT_BINARY_DIR} spinlock)
target_compile_options(ARMv8Spinlock PRIVATE -g -O0)
target_link_options(ARMv8Spinlock PRIVATE --scatter=${CMAKE_CURRENT_SOURCE_DIR}/v8A.scat --entry reset_handler --map)
set_target_properties(ARMv8Spinlock PROPERTIES SUFFIX .axf)

