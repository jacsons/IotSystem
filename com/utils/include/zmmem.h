#ifdef  __ZM_MEME_H__
#define __ZM_MEME_H__
#include <linux/errno.h>
#include <linux/types.h>


void* zm_zalloc(u32 size);
void zm_free(void *buff);

#endif
