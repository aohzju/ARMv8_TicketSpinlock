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
	
	
	.global setGenTimerFreq
	.type	setGenTimerFreq	@function

setGenTimerFreq:
	MSR		CNTFRQ_EL0, X0
	RET

	.global getPhyCount
	.type	getPhyCount @function
getPhyCount:
	MRS		X0, CNTPCT_EL0
	RET

	.global setEL3PhyTimerCV
	.type	setEL3PhyTimerCV @function
setEL3PhyTimerCV:
	MSR		CNTPS_CVAL_EL1, X0
	RET

	.global setEL3PhyTimerCtrl
	.type	setEL3PhyTimerCtrl @function
setEL3PhyTimerCtrl:
	MSR CNTPS_CTL_EL1, X0
	RET

	.end
