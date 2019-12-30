#ifndef __ZM_LOG_H__
#define __ZM_LOG_H__
#include "stdlib.h"

typedef enum logType {
    LOG_EMERG =  0, 	//紧急状态
    LOG_ALERT =  1, 	//必须立即修复状态
    LOG_CRIT =   2, 	//严重状态
    LOG_ERR =    3, 	//出错状态
    LOG_WARNING = 4, 	//警告状态
    LOG_NOTICE = 5, 	//正常，但重要的状态
    LOG_INFO =   6, 	//信息性消息
    LOG_DEBUG =  7 	//调试消息
}logType_t;

typedef struct zmlog {
    int (*log)(logType_t logType, const char *format,const char*moduleName, ...);
    int (*logEmerg)(const char *format,const char*moduleName, ...);
    int (*logAlert)(const char *format,const char*moduleName, ...);
    int (*logCrit)(const char *format,const char*moduleName, ...);
    int (*logErr)(const char *format,const char*moduleName, ...);
    int (*logWarning)(const char *format,const char*moduleName, ...);
    int (*logNotice)(const char *format,const char*moduleName, ...);
    int (*logInfo)(const char *format,const char*moduleName, ...);
    int (*logDebug)(const char *format,const char*moduleName, ...);
} zmlog_t;

zmlog_t* GetLogInstance();

#endif
