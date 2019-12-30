#include "nand.h"

/* NAND FLASH控制器 */
#define NFCONF (*((volatile unsigned long *)0x4E000000))
#define NFCONT (*((volatile unsigned long *)0x4E000004))
#define NFCMMD (*((volatile unsigned char *)0x4E000008))
#define NFADDR (*((volatile unsigned char *)0x4E00000C))
#define NFDATA (*((volatile unsigned char *)0x4E000010))
#define NFSTAT (*((volatile unsigned char *)0x4E000020))

#define TXD0READY   (1<<2)
#define PAGE_WIDTH 2048;

static void nand_mb()
{
	volatile int i;
	for (i = 0; i < 10; i++);
}

static void nand_select(void)
{
	NFCONT &= ~(1<<1);	
}

static void nand_deselect(void)
{
	NFCONT |= (1<<1);	
}

static void nand_cmd(unsigned char cmd)
{
	NFCMMD = cmd;
	nand_mb();
}

static void nand_addr(unsigned int addr)
{
	unsigned int col  = addr % PAGE_WIDTH;
	unsigned int page = addr / PAGE_WIDTH;
	volatile int i;

	NFADDR = col & 0xff;
	nand_mb();
	NFADDR = (col >> 8) & 0xff;
	
	
	NFADDR  = page & 0xff;
	nand_mb();
	NFADDR  = (page >> 8) & 0xff;
	nand_mb();
	NFADDR  = (page >> 16) & 0xff;
	nand_mb();
}

static void nand_wait_ready(void)
{
	while (!(NFSTAT & 1));
}

static unsigned char nand_data(void)
{
	return NFDATA;
}

void nand_init(void)
{
#define TACLS   0
#define TWRPH0  1
#define TWRPH1  0
	/* 设置时序 */
	NFCONF = (TACLS<<12)|(TWRPH0<<8)|(TWRPH1<<4);
	/* 使能NAND Flash控制器, 初始化ECC, 禁止片选 */
	NFCONT = (1<<4)|(1<<1)|(1<<0);	
}

void nand_read(unsigned int addr, unsigned char *buf, unsigned int len)
{
	int col = addr % PAGE_WIDTH;
	int i = 0;
		
	/* 1. 选中 */
	nand_select();

	while (i < len)
	{
		/* 2. 发出读命令00h */
		nand_cmd(0x00);

		/* 3. 发出地址(分5步发出) */
		nand_addr(addr);

		/* 4. 发出读命令30h */
		nand_cmd(0x30);

		/* 5. 判断状态 */
		nand_wait_ready();

		/* 6. 读数据 */
		for (; (col < PAGE_WIDTH) && (i < len); col++)
		{
			buf[i] = nand_data();
			i++;
			addr++;
		}
		
		col = 0;
	}

	/* 7. 取消选中 */		
	nand_deselect();
}