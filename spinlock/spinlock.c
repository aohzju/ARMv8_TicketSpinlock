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


#include "spinlock.h"

uint32_t spin_lock_irqsave(spinlock_t *locker)
{
	uint64_t coreId;
	uint32_t mask;

	__asm
	(
		"MRS %[result], mpidr_el1"
	    : [result] "=r" (coreId)
	    :
	); //The bit 31 of the affinitity register mpidr_el1 is RES1, so mpidr_el1 is guaranteed nonzero
	
	if((uint32_t)coreId == (uint32_t)locker->lock_core_count){ //already owned by this core, nesting call to this function
		locker->lock_core_count += 0x100000000ULL;
		return 0;	//because it is nesting call, the returned flag won't be used anyway.
	}

	mask = raw_spin_lock_irqsave(&locker->ticket);

	locker->lock_core_count = ((coreId & 0xFFFFFFFF) + 0x100000000ULL);

	return mask;
}


void spin_unlock_irqrestore(spinlock_t *locker, uint32_t irq_mask)
{
	uint64_t coreId, lcc;
	uint32_t count;

	__asm
	(
		"MRS %[result], mpidr_el1"
	    : [result] "=r" (coreId)
	    :
	); //The bit 31 of the affinitity register mpidr_el1 is RES1, so mpidr_el1 is guaranteed nonzero

	lcc = locker->lock_core_count;
	if(coreId != (uint32_t)lcc)	//not owned by the current core
		return;
	
	count = (uint32_t)(lcc>>32) - 1;
	if(count == 0){
		locker->lock_core_count = 0;
		raw_spin_unlock_irqrestore(&locker->ticket, irq_mask);
	}
	else
		locker->lock_core_count -= 0x100000000ULL; //decrease lock count by 1
}

void spin_lock(spinlock_t *locker)
{
	raw_spin_lock(&locker->ticket);
}
 void spin_unlock(spinlock_t *locker)
 {
	 raw_spin_unlock(&locker->ticket);
 }


