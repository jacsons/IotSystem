#ifndef __RESULT_MACRO_H__
#define __RESULT_MACRO_H__


typedef enum {
  // common error no
  ERR_NONE = 0,
  ERR_INVALID_PARAM = 1,
  ERR_INVALID_HANDLE = 2,
  ERR_INVALID_IOCTL = 3,


  ERR_MAX_NO
}errorno;

char* get_error_description(errorno errno);

#endif
