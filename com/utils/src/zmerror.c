#include "zmerror.h"



#define DECRIPTION_LENGTH  100

static char g_error_description[ERR_MAX_NO][DECRIPTION_LENGTH] = {
  [ERR_NONE] = {"ok"},
  [ERR_INVALID_PARAM] = {"param is invalid"},
  [ERR_INVALID_HANDLE] = {"invalid handle"},
  [ERR_INVALID_IOCTL] = {"ioctl error"},
};



char* get_error_description(errorno errno)
{
  if (errno < ERR_MAX_NO) {
    return g_error_description[errno]
  }


  LOG_ERR_INFO("errno error, errno = %d \n", errno);
  return NULL;
}
