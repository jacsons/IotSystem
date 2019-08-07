all:
	arm-linux-gcc -c -o led.o led_on.c
	arm-linux-gcc -c -o uart.o uart.c
	arm-linux-gcc -c -o main.o main.c
	arm-linux-gcc -c -o start.o start.S
	arm-linux-ld -Ttext 0 start.o led.o uart.o main.o -o uart.elf
	arm-linux-objcopy -O binary -S uart.elf uart.bin

dump:
	arm-linux-objdump -D uart.elf > uart.diss
clean:
	rm *.bin *.o *.elf
