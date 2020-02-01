/*****************************************************************************
* Copyright: 2020-2030, ***oak***
* file name: log.c
* Description: log realize file
* Author: oak
* Version: v-0.0.1
* Date: 2020-02-01 12:30:34
* History: 

* Attantion: this log.c realize function don't support multi-thread
***************************************************************************/
#include "log.h"
#include "uart.h"

#define DEFAULT_LOG_LEVEL LOG_DEBUG
#define DEFAULT_LOG_BUFF 64

typedef char *va_list;
#define _INTSIZEOF(n) ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
#define va_start(ap, v) (ap = (va_list)&v + _INTSIZEOF(v))
#define va_arg(ap, t) (*(t *)(ap = ap + _INTSIZEOF(t), ap - _INTSIZEOF(t)))
#define va_end(ap) (ap = (va_list)0)

unsigned char hex_tab[] = {'0', '1', '2', '3', '4', '5', '6', '7',
                           '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
/*****************************************************************************
* Function:  getUartCmdInstance
* Description:  get Uart cmd instance
* Param: None
* Output: None
* Return: 
*      struct UartCmd * : Uart struct
* Attantion: first invork not support multi-thread
***************************************************************************/
static struct UartCmd * getUartCmdInstance()
{
    static struct UartCmd uartCmd; 
    static int isInit = 0;

    if (!isInit) {
        isInit = 1;
        uart_register(&uartCmd);
        uartCmd.uart_init();
        uartCmd.puts("log init success \n");
    }

    return &uartCmd;
}

/*****************************************************************************
* Function: logOutPutNum
* Description: out put digital number
* Param: 
*   n : 
*   base :  digital base : 8, 10 16
*   lead :  lead pre character
*   maxwidth :  output num width
* Output: None
* Return: void
***************************************************************************/
static void logOutPutNum(long n, int base,char lead,int maxwidth) 
{
    char buf[DEFAULT_LOG_BUFF];
    char *s = buf + sizeof(buf);
    int count = 0;
    int i = 0;
    unsigned long m = 0;

    struct UartCmd *uartCmd = getUartCmdInstance();

    *--s = '\0';
    m = n < 0 ? -n : n;

    do {
        *--s = hex_tab[m % base];
        count++;
    } while ((m /= base) != 0);

    if (maxwidth && count < maxwidth) {
        for (i = maxwidth - count; i; i--) {
            *--s = lead;
        }
    }

    if (n < 0) {
        *--s = '-';
    }

    uartCmd->puts(s);
}

/*****************************************************************************
* Function: logOutPut
* Description: out put char
* Param: 
* Output: None
* Return: void
***************************************************************************/
static va_list logOutPut(const char c, va_list ap, char lead, int maxwidth)
{
    struct UartCmd *uartCmd = getUartCmdInstance(); 

    switch (c) {
    case 'd':
        logOutPutNum(va_arg(ap, int), 10, lead, maxwidth);
        break;
    case 'o':
        logOutPutNum(va_arg(ap, unsigned int), 8, lead, maxwidth);
        break;
    case 'u':
        logOutPutNum(va_arg(ap, unsigned int), 10, lead, maxwidth);
        break;
    case 'x':
        logOutPutNum(va_arg(ap, unsigned int), 16, lead, maxwidth);
        break;
    case 'c':
        uartCmd->putc(va_arg(ap, int));
        break;
    case 's':
        uartCmd->puts(va_arg(ap, char *));
        break;
    default:
        uartCmd->putc(c);
        break;
    }

    return ap;
}

/*****************************************************************************
* Function: logDecodeFormat
* Description:  decode format
* param: 
*   format : string format
*   ap : start of param
* Output: None
* Return: void
***************************************************************************/
static int logDecodeFormat(const char *format, va_list ap)
{
    struct UartCmd *uartCmd = getUartCmdInstance(); 

    char lead = ' ';
    int maxwidth = 0;

    for (; *format != '\0'; format++) {
        if (*format != '%') {
            uartCmd->putc(*format);
            continue;
        }

        //format : %08d, %8d,%d,%u,%x,%c,%s
        format++;
        if (*format == '0') {
            lead = '0';
            format++;
        }

        lead = ' ';
        maxwidth = 0;

        while (*format >= '0' && *format <= '9') {
            maxwidth *= 10;
            maxwidth += (*format - '0');
            format++;
        }

        // note logOutPut should update ap
        ap = logOutPut(*format, ap, lead, maxwidth);
    }

    return 0;
}

/*****************************************************************************
* Function: logUtil
* Description: log common function
* Param {enum LogLevel}: log level
* Param {modelName}: model name
* Output: None
* Return: void
***************************************************************************/
void logUtil(unsigned int level, const char *format, ...)
{
    va_list ap;

    if (level > DEFAULT_LOG_LEVEL) {
        return;
    }

    va_start(ap, format);
    logDecodeFormat(format, ap);	
    va_end(ap);
}
