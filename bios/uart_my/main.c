#include "s3c2440_soc.h"
#include "uart.h"


int main()
{
    unsigned char c;
    uart0_init();
    put_chars("hello, world!\n");


    while(1)
    {
        c = get_char();
        put_char(c);
    };

    return 0;
}
