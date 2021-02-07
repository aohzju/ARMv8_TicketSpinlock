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
 * uart.c
 *
 */

#include <stdio.h>
#include <stdint.h>
#include "uart.h"

//static int uartdr_offset = 0;
static int uartctl_offset = 0x0030;

void enable_uart(UART_PL011 uart)
{
	short *ctrl = (short*)((int64_t)uart + uartctl_offset);

	*ctrl = 0x0B01;
}

void write_uart_buf(UART_PL011 uart, const char *buf, int n)
{
	int i;
	char *uartdr = (char*)uart;
	for(i=0; i<n; i++)
		*uartdr = buf[i];
}

void write_uart_string(UART_PL011 uart, const char *str)
{
	char ch;
	char *uartdr = (char*)uart;
	while(1){
		ch = *str++;
		if(ch)
			*uartdr = ch;
		else
			break;
	}
}

void write_uart_char(UART_PL011 uart, char ch)
{
	char *uartdr = (char*)uart;
	*uartdr = ch;
}

//printf's dependencies:
FILE  __stdout={UART0};  //Use UART0 as stdout

int fputc(int c, FILE* stream)
{
	uint8_t chr = (uint8_t)c;
	write_uart_char(stream->fuart, chr);
	return chr;
}

int ferror(FILE *stream)
{
	(void)stream;
	return 0;
}

//__stdout must be opened before printf can be called:
void open__stdout()
{
	enable_uart(__stdout.fuart);
}

