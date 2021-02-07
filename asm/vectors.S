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


//Exception handler table:

	.global vector_table_el3
	//.global vector_table_el2
	//.global vector_table_el1

	.balign 0x800

vector_table_el3:

//Group 1: Current EL with SP0
curr_el_sp0_sync:
	b	.

	.balign 0x80
curr_el_sp0_irq:
	b	.

	.balign 0x80
curr_el_sp0_fiq:
	b	.

	.balign 0x80
curr_el_sp0_serr:
	b	.

//Group 2: Current EL with SPx:
	.balign 0x80
curr_el_spx_sync:
	b	.

	.balign 0x80
curr_el_spx_irq:
	b	.

	.balign 0x80
curr_el_spx_fiq:
	b	.

	.balign 0x80
curr_el_spx_serr:
	b	.

//Group 3: Lower EL using AArch64:
	.balign 0x80
lower_el_a64_sync:
	b	.

	.balign 0x80
lower_el_a64_irq:
	b	.

	.balign 0x80
lower_el_a64_fiq:
	b	.

	.balign 0x80
lower_el_a64_serr:
	b	.

//Group4: Lower EL using AArch32:
	.balign 0x80
lower_el_a32_sync:
	b	.

	.balign 0x80
lower_el_a32_irq:
	b	.

	.balign 0x80
lower_el_a32_fiq:
	b	.

	.balign 0x80
lower_el_a32_serr:
	b	.
