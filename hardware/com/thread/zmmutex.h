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

#ifndef __ZM_MUTEX_H__
#define __ZM_MUTEX_H__

#define ZM_MUTEX(var)     pthread_mutex_lock(&var ## _mutex);
#define ZM_UNMUTEX(var)   pthread_mutex_unlock(&var ## _mutex);


#endif

