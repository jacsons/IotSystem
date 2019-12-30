#ifndef __FLASH_H__
#define __FLASH_H__


struct FlashCmd {
	void (*flash_init)(void);
	void (*flash_read)(unsigned int addr, unsigned char buff, unsigned int len);
	void (*flash_write)(unsigned int addr, unsigned char buff, unsigned int len);
	void (*flash_clean)(unsigned int addr);
};

void flash_cmd_init(struct FlashCmd *cmd);

#endif