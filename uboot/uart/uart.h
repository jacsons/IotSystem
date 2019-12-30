#ifndef __UART_H__
#define __UART_H__

struct UartCmd {
	void (*uart_init)(void);
	void (*puts)(char *str);
	void (*puthex)(unsigned int val);
	void (*putc)(unsigned char c);
}

void uart_register(struct UartCmd *uartCmd);

#endif