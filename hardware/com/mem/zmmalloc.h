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

/*****************************************************************************
* Function: zmmalloc 
* Description: malloc memroy
* Param: size memroy size
* Output: None
* Return: void *
***************************************************************************/
void *zmmalloc(size_t size);

/*****************************************************
 * @brief resize memeory
 * 
 * @param numElements number of element
 * @param elementSize element of signgle element
 * @return void*
 ******************************************************/
void *zmcalloc(size_t numElements, size_t elementSize);

/*****************************************************
 * @brief 
 * 
 * @param ptr 
 * @param size 
 * @return void* 
 ******************************************************/
void *zmrealloc(void *ptr, size_t size);
void zmfree(void *ptr);
void *zmsmalloc(size_t size, int defaultValue);
char *zmstrdup(const char *s);
size_t zmmalloc_size(void *ptr);
size_t zmmalloc_used_memory(void);

void zmmalloc_set_oom_handler(void (*oom_handler)(size_t), void (*set_handler)(size_t, int));

#endif // __ZM_MALLOC_H__