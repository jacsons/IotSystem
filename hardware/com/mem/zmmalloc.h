/*****************************************************************************
* Copyright: 2020-2030, ***oak***
* file name: 
* Description: 
* Author: oak
* Version: v-0.0.1
* Date: 2020-03-01 10:49:52
* History: 
***************************************************************************/
#ifndef __ZM_MALLOC_H__
#define __ZM_MALLOC_H__
#include <malloc.h>

#define __xstr(s) __str(s)
#define __str(s) #s

void *zmmalloc(size_t size);
void *zmcalloc(size_t numElements, size_t elementSize);
void *zmrealloc(void *ptr, size_t size);
void zmfree(void *ptr);
void *zmsmalloc(size_t size, int defaultValue);
char *zmstrdup(const char *s);
size_t zmmalloc_size(void *ptr);
size_t zmmalloc_used_memory(void);

void zmmalloc_set_oom_handler(void (*oom_handler)(size_t), void (*set_handler)(size_t, int));

#endif // __ZM_MALLOC_H__