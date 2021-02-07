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


	.balign 64  //aligned to cache line size
	.global raw_spin_lock_irqsave
	.type raw_spin_lock_irqsave, %function
//uint32_t raw_spin_lock_irqsave(uint64_t *locker);

raw_spin_lock_irqsave:
    /* save the local core exception mask to X1 */
    MRS     X1, DAIF
    /* mask the local core exceptions */
    MSR     DAIFSET, #0xF
    //DSB     SY //barrier not needed: See armv8a spec C5.1.3: Writes to PSTATE.{PAN, D, A, I, F} occur in program order without the need for additional synchronization
    //ISB     SY

	ORR		X2, XZR, #0x100000000
WaitTicket:
	LDAXR	X3, [X0]			//Hi: next ticket, Lo: owner
	LSR		X4, X3, #32			//W4: hold the ticket# allocated to this core
	ADD		X3, X3, X2			//bump the next ticket
	STXR	W5, X3, [X0]		//If this succeeds, we get the allocated ticket# in W4
	CBNZ 	W5, WaitTicket 		//test if store succeeded and retry if not
	//Got ticket up to this point
	SUB		W5, W3, W4
	CBZ		W5, Done
	SEVL
CheckTicket:
	WFE
	LDAXR	X3, [X0]		//must be exclusive load so that an event is triggered when the exclusive state is cleared by the writing in the unlock function
	SUB		W5, W3, W4
	CBZ		W5, Done
	B		CheckTicket

Done:
	MOV		X0, X1
	RET

//==============================================================================================================

	.global raw_spin_unlock_irqrestore
	.type 	raw_spin_unlock_irqrestore, %function
//void     raw_spin_unlock_irqrestore(uint64_t *locker, uint32_t irq_msk);

raw_spin_unlock_irqrestore:
	LDR		X2, [X0]
	ADD		W3, W2, #1
	LSR		X2, X2, #32
	LSL		X2, X2, #32
	ORR		X2, X2, X3
	STLR	X2, [X0]
	MSR		DAIF, X1
	RET

	.end
