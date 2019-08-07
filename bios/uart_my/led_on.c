void delay(volatile unsigned int delay_time)
{
    while(delay_time--){};
}


void led_on(unsigned int i)
{
    unsigned int *pGPFCON = (unsigned int *)0x56000050;
    unsigned int *pGPF0 = (unsigned int *)0x56000054;

    if (i == 4) {
        *pGPFCON = 0x100;
        *pGPF0 = 0;
    }

    if (i == 5) {
        *pGPFCON = 0x400;
        *pGPF0 = 0;
    }
}

#if 0
int main()
{
    unsigned int *pGPFCON = (unsigned int *)0x56000050;
    unsigned int *pGPF0 = (unsigned int *)0x56000054;

    *pGPFCON = 0x100;
    *pGPF0 = 0;

    return 0;

}
#endif
