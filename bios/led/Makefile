all:
	arm-linux-gcc -c -o start.o start.S
	arm-linux-gcc -c -o led_on.o led_on.c
	arm-linux-ld -Ttext 0 start.o  led_on.o -o led_on.elf
	arm-linux-objcopy -O binary -S led_on.elf led_on.bin

dump:
	arm-linux-objdump -D led_on.elf > led_on.diss

clean:
	rm -f *.bin *.o *.elf *.diss
