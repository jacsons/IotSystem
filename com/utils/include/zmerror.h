#ifndef __RESULT_MACRO_H__
#define __RESULT_MACRO_H__
#include <linux/types.h>

#define ERRNO_MODULE_OFFSET 8
#define ERRNO_ERRNO_BIT_LEN (sizeof(u16) - ERRNO_MODULE_OFFSET)

#define  _ZM_ERRORNO_MAKE(module, errno)  \
    (module) << 0xf | (errno & 0xff)


#define ZM_ERRORNO_MAKE(module, errno) _ZM_ERRORNO_MAKE(module, errno)

typedef enum zmerrono{
  // common error no
  ERR_NONE = 0,
  ERR_INVALID_PARAM,
  ERR_INVALID_PARAM_NULL,
  ERR_INVALID_HANDLE,
  ERR_INVALID_IOCTL,

  // memey error no
  ERR_NO_MEMEY = 40,
  ERR_MEMSET,
  ERR_OUT_OF_MEM,

  // file error no
  ERR_FILE_NOT_EXIST = 80,
  ERR_PATH_NOT_EXIST,
  ERR_FILE_DENY,
  ERR_PATH_DENY

} zmerrno_t;

char* get_error_description(zmerrno_t errno);

#endif
