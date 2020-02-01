/*****************************************************************************
* Copyright: 2020-2030, ***oak***
* file name: 
* Description: 
* Author: oak
* Version: v-0.0.1
* Date: 2020-02-01 16:20:12
* History: 
***************************************************************************/
#include "flash.h"
#include "nand.h"

static int isBootFromNorFlash(void)
{
	volatile int *p = (volatile int *)0;
	int val;

	val = *p;
	*p = 0x12345678;
	if (*p == 0x12345678) {
		*p = val;
		return 0;
	} else {
		return 1;
	}
}

void copy_code_to_sdram(unsigned char *src, unsigned char *dest, unsigned int len)
{	
	int i = 0;
	
	if (isBootFromNorFlash()) {
		while (i < len) {
			dest[i] = src[i];
			i++;
		}
	} else {
		nand_read((unsigned int)src, dest, len);
	}
}

void clear_bss(void)
{
	extern int __bss_start, __bss_end;
	int *p = &__bss_start;
	
	for (; p < &__bss_end; p++) {
		*p = 0;
	}
}

struct FlashCmd *flash_cmd_init(struct FlashCmd *cmd)
{
	if (cmd == (void *)0) {
		return cmd;
	}

	cmd->flash_init = nand_init;
	cmd->flash_read = nand_read;
	cmd->flash_write = (void *)0;
	cmd->flash_clean = (void *)0;

	return cmd;
}
