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

struct FlashCmd *flash_cmd_init(struct FlashCmd *cmd)
{
	if (cmd == NULL) {
		return;
	}
	
	if (isBootFromNorFlash()) {
			cmd->flash_init = nand_init;
			cmd->flash_read = nand_read;
			cmd->flash_write = NULL;
			cmd->flash_clean = NULL;
	}
	
	return;
}