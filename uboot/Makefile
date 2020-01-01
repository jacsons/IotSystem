CC      = arm-linux-gcc
LD      = arm-linux-ld
AR      = arm-linux-ar
OBJCOPY = arm-linux-objcopy
OBJDUMP = arm-linux-objdump

CFLAGS 		:= -Wall -O2
CPPFLAGS   	:= -nostdinc -nostdlib -fno-builtin

INCLUDE := -I ./flash -I ./flash/nand \
	-I ./uart/

SRCS := ./flash/flash.c ./flash/nand/nand.c \
	./uart/uart.c ./main.c

objs := start.o
objs += $(SRCS:.c=.o)

boot.bin: $(objs)
	${LD} -Tboot.lds -o boot.elf $^
	${OBJCOPY} -O binary -S boot.elf $@
	${OBJDUMP} -D -m arm boot.elf > boot.dis
	
%.o:%.c
	${CC} $(CPPFLAGS) $(CFLAGS) $(INCLUDE) -c -o $@ $< 
%.o:%.S
	${CC} $(CPPFLAGS) $(CFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	find -type f -name "*.o" -print | xargs rm -f
	rm -f *.bin *.elf *.dis