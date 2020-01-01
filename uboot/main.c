#include "uart.h"
#include "flash.h"
#include "setup.h"

static struct tag *params;

void setup_start_tag(void)
{
	params = (struct tag *)0x30000100;

	params->hdr.tag = ATAG_CORE;
	params->hdr.size = tag_size (tag_core);

	params->u.core.flags = 0;
	params->u.core.pagesize = 0;
	params->u.core.rootdev = 0;

	params = tag_next (params);
}

void setup_memory_tags(void)
{
	params->hdr.tag = ATAG_MEM;
	params->hdr.size = tag_size (tag_mem32);
	
	params->u.mem.start = 0x30000000;
	params->u.mem.size  = 64*1024*1024;
	
	params = tag_next (params);
}

int strlen(char *str)
{
	int i = 0;
	
	while (str[i]) {
		i++;
	}
	
	return i;
}

void strcpy(char *dest, char *src)
{
	while ((*dest++ = *src++) != '\0');
}

void setup_commandline_tag(char *cmdline)
{
	int len = strlen(cmdline) + 1;
	
	params->hdr.tag  = ATAG_CMDLINE;
	params->hdr.size = (sizeof (struct tag_header) + len + 3) >> 2;

	strcpy (params->u.cmdline.cmdline, cmdline);

	params = tag_next (params);
}

void setup_end_tag(void)
{
	params->hdr.tag = ATAG_NONE;
	params->hdr.size = 0;
}


int main(void)
{
	struct UartCmd uartCmd;
	struct FlashCmd flashCmd;
	void (*theKernel)(int zero, int arch, unsigned int params);
	volatile unsigned int *p = (volatile unsigned int *)0x30008000;

	uart_register(&uartCmd);
	uartCmd.uart_init();
	uartCmd.puts("Copy kernel from nand\n\r");
	
	flash_cmd_init(&flashCmd);
	uartCmd.puts("flash_cmd_init\n\r");
	flashCmd.flash_init();
	uartCmd.puts("flash_init\n\r");
	flashCmd.flash_read(0x60000+64, (unsigned char *)0x30008000, 0x200000);
	uartCmd.puts("flash_read\n\r");
	uartCmd.puthex(0x1234ABCD);
	uartCmd.puts("\n\r");
	uartCmd.puthex(*p);
	uartCmd.puts("\n\r");

	uartCmd.puts("Set boot params\n\r");
	setup_start_tag();
	setup_memory_tags();
	setup_commandline_tag("noinitrd root=/dev/mtdblock3 init=/linuxrc console=ttySAC0");
	setup_end_tag();

	uartCmd.puts("Boot kernel\n\r");
	theKernel = (void (*)(int, int, unsigned int))0x30008000;
	theKernel(0, 362, 0x30000100);  

	uartCmd.puts("Error!\n\r");

	return -1;
}
