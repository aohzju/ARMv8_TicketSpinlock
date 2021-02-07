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
 * uart.h
 *
 */

#ifndef UART_H_
#define UART_H_

typedef enum {
	UART0 = 0x001C090000,
	UART1 = 0x001C0A0000,
	UART2 = 0x001C0B0000,
	UART3 = 0x001C0C0000} UART_PL011; //Start address of UARTs

//printf dependency:
struct __FILE {
	UART_PL011 	fuart;
};

void enable_uart(UART_PL011 uart);
void write_uart_buf(UART_PL011 uart, const char *buf, int n);
void write_uart_string(UART_PL011 uart, const char *str);
void write_uart_char(UART_PL011 uart, char ch);
void open__stdout();

#endif /* UART_H_ */
