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


#ifndef __SPINLOCK_H__
#define __SPINLOCK_H__

#include <stdint.h>

#define ERG		8		//Exclusive Reservation Granule in 8-byte qwords
typedef struct
{
    uint64_t	lock_core_count;	//Low word: the core ID that owns the lock, 0 if the lock is free
    								//High word: the lock count
    uint64_t	ticket;				//Low word: the current ticket number that can own the lock (a.k.a owner)
    								//High word: the ticket number for the next lock requester  (a.k.a next)
    uint64_t	rsvd[ERG-2];     //Make it 64-byte long. The ERG of A53 is 64 bytes (1 cache line).

} spinlock_t  __attribute__((__aligned__(64)));

#define SPIN_LOCK_UNLOCKED	{0}

//ticketed spinlock, allow nesting
uint32_t spin_lock_irqsave(spinlock_t *locker); //lock and disable interrupts at the same time, allow nesting
void     spin_unlock_irqrestore(spinlock_t *locker, uint32_t irq_msk);  //unlock and restore the original interrupt mask

//ticketed spinlock, not supporting nesting:
uint32_t raw_spin_lock_irqsave(uint64_t *locker); //lock and disable interrupts at the same time
void     raw_spin_unlock_irqrestore(uint64_t *locker, uint32_t irq_msk);  //unlock and restore the original interrupt mask


#endif /* _SPINLOCK_H_ */


