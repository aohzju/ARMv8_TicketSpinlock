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


/*
 * basehw.h
 */

#ifndef BASEHW_H_
#define BASEHW_H_

#include <stdint.h>

//Generic timer related:
void setGenTimerFreq(int freq);
uint64_t getPhyCount();
void setEL3PhyTimerCV(uint64_t cv);
void setEL3PhyTimerCtrl(uint32_t ctl);

static inline uint32_t getCoreId(void)
{
    uint64_t coreId;
    uint32_t clstrId, cpuId;
    __asm
    (
        "MRS %[result], mpidr_el1"
        : [result] "=r" (coreId)
        :
    );
    coreId >>= 8;
    clstrId = (uint32_t)coreId;
    cpuId = clstrId & 0x3;
    clstrId >>= 6;
    return (clstrId | cpuId) & 0xF;
}


#endif /* BASEHW_H_ */
