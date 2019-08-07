#ifndef __IOT_UART_H__
#define __IOT_UART_H__

void uart0_init();
int  put_char(int c);
char get_char();
int put_chars(const char *s);

#endif
