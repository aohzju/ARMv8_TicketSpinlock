/*
MIT License

Copyright (c) 2021 Oscar Huang

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
*/


//Reset handler:

	.global	 reset_handler
	.section .reset,"ax"

//To guarantee no semihosting library functions are called:
 	.global __use_no_semihosting

//Override ARM library's __rt_entry:
	.global __rt_entry
	.type	__rt_entry @function
__rt_entry:		//called by __main
	SEV		//wake up all cores
	B  appmain

reset_handler:
	// Initialize the register bank:
	.irp	reg, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10
	MOV		X\reg, XZR
	.endr
	.irp	reg, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20
	MOV		X\reg, XZR
	.endr
	.irp	reg, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30
	MOV		X\reg, XZR
	.endr

	//Initialize stack pointers:
	//Uncomment this line if you'd like to use SP_EL0 as stack pointer
	//MSR		SPSel, #0		//Use SP_EL0 as SP
	//AARCH64 stack is full descending, so set the initial value of SP to Image$$ARM_LIB_STACK$$ZI$$Limit
	LDR		X2, =Image$$ARM_LIB_STACK$$ZI$$Limit  //ARM_LIB_STACK: to be defined in the scatter loading file
	LDR     X3, =Image$$ARM_LIB_STACK$$ZI$$Length

	MRS		X0, MPIDR_EL1	//On FVP, the affinity ID is cluster.core.thread, where thread is always 0
	LSR		W0, W0, #8
	LSR		W1, W0, #6
	AND		W1, W1, #0x0C
	AND		W0, W0, #0x3
	ORR		W1, W1, W0		//core ID in W1

	LSR		W3, W3, #3		//8 cores
	MUL		W3, W3, W1
	SUB		X2, X2, X3
	MOV		SP, X2  //SP is SP_EL3 on reset

	//Initialize system control registers:

	//SCTLR_EL3

	//SCR_EL3
	MRS		X0, SCR_EL3
	ORR		X0, X0, #(1<<3)		//EA
	ORR		X0, X0, #(1<<2)		//FIQ
	ORR		X0, X0, #(1<<1)		//IRQ
	ORR		X0, X0, #(1<<8)		//HCE
	AND		X0, X0, #~(1<<7)	//Enable SMC instruction, which is used for task yield
	MSR		SCR_EL3, X0

	//Check core ID:
	CMP		W1, #0
	B.EQ	__main	 //do startup initialization (copy ZW regions, zero ZI regions, etc. And then call __rt_entry, which calls application's main function
					 //do this only on core 0
	SEVL
	WFE
	WFE		//all other cores enter low power state for now
	B		appmain

	.end
