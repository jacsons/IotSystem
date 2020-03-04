/*****************************************************************************
* Copyright: 2020-2030, ***oak***
* file name: 
* Description: 
* Author: oak
* Version: v-0.0.1
* Date: 2020-03-01 10:50:41
* History: 
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <string.h>
#include <pthread.h>
#include "zmatomic.h"
#include "zmmalloc.h"

#define update_zmmalloc_stat_alloc(__n)                     \
    do                                                      \
    {                                                       \
        size_t _n = (__n);                                  \
        if (_n & (sizeof(long) - 1))                        \
            _n += sizeof(long) - (_n & (sizeof(long) - 1)); \
        atomicIncr(used_memory, __n);                       \
    } while (0)

#define update_zmmalloc_stat_free(__n)                      \
    do                                                      \
    {                                                       \
        size_t _n = (__n);                                  \
        if (_n & (sizeof(long) - 1))                        \
            _n += sizeof(long) - (_n & (sizeof(long) - 1)); \
        atomicDecr(used_memory, __n);                       \
    } while (0)

static size_t used_memory = 0;
pthread_mutex_t used_memory_mutex = PTHREAD_MUTEX_INITIALIZER;

#define PREFIX_SIZE (sizeof(size_t))

static void zmmalloc_default_oom(size_t size)
{
    fprintf(stderr, "zmmalloc: Out of memory trying to allocate %zu bytes\n",
            size);
    fflush(stderr);
}

static void zmmalloc_default_set(size_t size, int defaultValue)
{
    fprintf(stderr, "zmmalloc: trying to set %zu bytes defaultValue = %d\n",
            size, defaultValue);
    fflush(stderr);
}

#define zmmalloc_oom_handler(size) zmmalloc_default_oom(size)
#define zmmalloc_set_handler(size, defaultValue) zmmalloc_default_set(size, defaultValue)

static void (*zmalloc_oom_handler)(size_t) = zmmalloc_default_oom;
static void (*zmalloc_set_handler)(size_t, int) = zmmalloc_default_set;

void *zmmalloc(size_t size)
{
    void *ptr = malloc(size + PREFIX_SIZE);

    if (!ptr)
    {
        zmalloc_oom_handler(size);
        return NULL;
    }

    *((size_t *)ptr) = size;
    update_zmalloc_stat_alloc(size + PREFIX_SIZE);

    return (char *)ptr + PREFIX_SIZE;
}

void *zmcalloc(size_t numElements, size_t elementSize)
{
    void *ptr = calloc(numElements, elementSize + PREFIX_SIZE);

    if (!ptr)
    {
        zmmalloc_oom_handler(elementSize);
        return NULL;
    }

    *((size_t *)ptr) = elementSize;
    update_zmalloc_stat_alloc(elementSize + PREFIX_SIZE);
    return (char *)ptr + PREFIX_SIZE;
}

void *zmrealloc(void *ptr, size_t size)
{

    size_t oldsize;
    void *newptr = NULL;
    void *realptr = NULL;

    if (ptr == NULL)
    {
        return zmmalloc(size);
    }

    realptr = (char *)ptr - PREFIX_SIZE;
    oldsize = *((size_t *)realptr);
    newptr = realloc(realptr, size + PREFIX_SIZE);
    if (!newptr)
    {
        zmalloc_oom_handler(size);
        return NULL;
    }

    *((size_t *)newptr) = size;
    update_zmalloc_stat_free(oldsize + PREFIX_SIZE);
    update_zmalloc_stat_alloc(size + PREFIX_SIZE);

    return (char *)newptr + PREFIX_SIZE;
}

void zmfree(void *ptr)
{
    void *realptr = NULL;
    size_t oldsize;

    if (ptr == NULL)
    {
        return;
    }

    realptr = (char *)ptr - PREFIX_SIZE;
    oldsize = *((size_t *)realptr);
    update_zmalloc_stat_free(oldsize + PREFIX_SIZE);

    free(realptr);
}

void *zmsmalloc(size_t size, int defaultValue)
{
    int ret;
    void *ptr = NULL;
    ptr = zmmalloc(size);
    if (!ptr)
    {
        zmalloc_oom_handler(size);
        return NULL;
    }

    ptr = memset(ptr, defaultValue, size);
    if (!ptr)
    {
        zmfree(ptr);
        ptr = NULL;
        zmmalloc_default_set(size, defaultValue);
    }

    return ptr;
}

char *zmstrdup(const char *s)
{
    size_t l = strlen(s) + 1;
    char *p = zmmalloc(l);

    memcpy(p, s, l);
    return p;
}

size_t zmmalloc_size(void *ptr)
{
    if (!ptr)
    {
        return 0;
    }

    void *realptr = NULL;
    realptr = (char *)ptr - PREFIX_SIZE;

    return *((size_t *)realptr);
}

size_t zmmalloc_used_memory(void)
{
    size_t um;
    atomicGet(used_memory, um);
    return um;
}

void zmmalloc_set_oom_handler(void (*oom_handler)(size_t), void (*set_handler)(size_t, int))
{
    zmalloc_oom_handler = oom_handler;
    zmalloc_set_handler = set_handler;
}
