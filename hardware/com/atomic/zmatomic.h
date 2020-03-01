/*****************************************************************************
* Copyright: 2020-2030, ***oak***
* file name: 
* Description: 
* Author: oak
* Version: v-0.0.1
* Date: 2020-03-01 11:00:31
* History: 
***************************************************************************/
#include <pthread.h>

#ifndef __ZM_ATOMIC_H__
#define __ZM_ATOMIC_H__

#define atomicIncr(var,count) do { \
    pthread_mutex_lock(&var ## _mutex); \
    var += (count); \
    pthread_mutex_unlock(&var ## _mutex); \
} while(0)
#define atomicGetIncr(var,oldvalue_var,count) do { \
    pthread_mutex_lock(&var ## _mutex); \
    oldvalue_var = var; \
    var += (count); \
    pthread_mutex_unlock(&var ## _mutex); \
} while(0)
#define atomicDecr(var,count) do { \
    pthread_mutex_lock(&var ## _mutex); \
    var -= (count); \
    pthread_mutex_unlock(&var ## _mutex); \
} while(0)
#define atomicGet(var,dstvar) do { \
    pthread_mutex_lock(&var ## _mutex); \
    dstvar = var; \
    pthread_mutex_unlock(&var ## _mutex); \
} while(0)
#define atomicSet(var,value) do { \
    pthread_mutex_lock(&var ## _mutex); \
    var = value; \
    pthread_mutex_unlock(&var ## _mutex); \
} while(0)
#define REDIS_ATOMIC_API "pthread-mutex"


#endif