#include <stdarg.h>
#include "s3c2440_soc.h"

void uart0_init()
{
    // config gpio to uart type
    GPHCON &= ~((3 << 4) | (3 << 6));
    GPHCON |= ((2 << 4) | (2 << 6));

    // config gpio to pull up
    GPHUP &= ~((1 << 2) | (1 << 3));

    // boardband to 115200
    UCON0 = 0x00000005;
    UBRDIV0 = 26;

    // config bit 8bit 1
    ULCON0 = 0x00000003;
}

int put_char(int c)
{
    while (!(UTRSTAT0 * (1 << 2))) {};

    UTXH0 = (unsigned char)c;

    return 0;
}

char get_char()
{
    while (!(UTRSTAT0 & (1 << 0))){};

    return URXH0;
}

int put_chars(const char *s)

{
    while (*s)
    {
        put_char(*s);
        s++;
    };

    return 0;
}

//
int uart_sprint(const char *format, ...)
{
    char *p = (char*)&format;
    int i;

    put_chars(p);







}
