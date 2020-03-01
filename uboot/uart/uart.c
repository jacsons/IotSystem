/*****************************************************************************
* Copyright: 2020-2030, ***oak***
* file name: 
* Description: 
* Author: oak
* Version: v-0.0.1
* Date: 2020-03-01 10:45:47
* History: 
***************************************************************************/
#include "uart.h"

/* GPIO */
#define GPHCON              (*(volatile unsigned long *)0x56000070)
#define GPHUP               (*(volatile unsigned long *)0x56000078)

/* UART registers*/
#define ULCON0              (*(volatile unsigned long *)0x50000000)
#define UCON0               (*(volatile unsigned long *)0x50000004)
#define UFCON0              (*(volatile unsigned long *)0x50000008)
#define UMCON0              (*(volatile unsigned long *)0x5000000c)
#define UTRSTAT0            (*(volatile unsigned long *)0x50000010)
#define UTXH0               (*(volatile unsigned char *)0x50000020)
#define URXH0               (*(volatile unsigned char *)0x50000024)
#define UBRDIV0             (*(volatile unsigned long *)0x50000028)

#define PCLK            50000000    
#define UART_CLK        PCLK       
#define UART_BAUD_RATE  115200     
#define UART_BRD        ((UART_CLK  / (UART_BAUD_RATE * 16)) - 1)

#define TXD0READY   (1<<2)
/*
 * ��ʼ��UART0
 * 115200,8N1,������
 */
void uart0_init(void)
{
    GPHCON  |= 0xa0;    // GPH2,GPH3����TXD0,RXD0
    GPHUP   = 0x0c;     // GPH2,GPH3�ڲ�����
    
    ULCON0  = 0x03;     // 8N1(8������λ���޽��飬1��ֹͣλ)
    UCON0   = 0x05;     // ��ѯ��ʽ��UARTʱ��ԴΪPCLK
    UFCON0  = 0x00;     // ��ʹ��FIFO
    UMCON0  = 0x00;     // ��ʹ������
    UBRDIV0 = UART_BRD; // ������Ϊ115200
}

/*
 * ����һ���ַ�
 */
void putc(unsigned char c)
{
    while (!(UTRSTAT0 & TXD0READY));
    UTXH0 = c;
}

void puts(char *str)
{
	int i = 0;
	while (str[i]) {
		putc(str[i]);
		i++;
	}
}

void puthex(unsigned int val)
{
	/* 0x1234abcd */
	int i;
	int j;
	
	puts("0x");

	for (i = 0; i < 8; i++) {
		j = (val >> ((7 - i) * 4)) & 0xf;
		if ((j >= 0) && (j <= 9)) {
			putc('0' + j);
		} else {
			putc('A' + j - 0xa);
		}
	}
}

void uart_register(struct UartCmd *uartCmd)
{
	if (uartCmd == (void *)0) {
		return;
	}
	
	uartCmd->uart_init = uart0_init;
	uartCmd->puts = puts;
	uartCmd->puthex = puthex;
	uartCmd->putc = putc;
}
