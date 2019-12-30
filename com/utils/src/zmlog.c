#include "zmlog.h"
#include "common.h"

STATIC void logUtil(unsigned int lev,const char *msg,...);

#define LOG_EMERG_INFO(format,moduleName, ...)  logUtil(LOG_EMERG, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_ALERT_INFO(format,...)  logUtil(LOG_ALERT, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_CRIT_INFO(format,...)  logUtil(LOG_CRIT, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_ERR_INFO(format,...)  logUtil(LOG_ERR, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_WARNING_INFO(format,...)  logUtil(LOG_WARNING, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_NOTICE_INFO(format,...)  logUtil(LOG_NOTICE, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_INFO_INFO(format,...)  logUtil(LOG_INFO, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_DEBUG_INFO(format,...)  logUtil(LOG_DEBUG, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)

STATIC void logUtil(unsigned int lev,const char *msg,...)
{


}

int log(logType_t logType, const char *format,const char*moduleName, ...)
{

    return 0;
}

int logEmerg(const char *format,const char*moduleName, ...)
{

    return 0;
}

int logAlert(const char *format,const char*moduleName, ...)
{
    return 0;
}

int logCrit(const char *format,const char*moduleName, ...)
{
    return 0;
}

int logErr(const char *format,const char*moduleName, ...)
{
    return 0;
}

int logWarning(const char *format,const char*moduleName, ...)
{
    return 0;
}

int logNotice(const char *format,const char*moduleName, ...)
{

    return 0;
}

int logInfo(const char *format,const char*moduleName, ...)
{

    return 0;
}

int logDebug(const char *format,const char*moduleName, ...)
{

    return 0;
}

zmlog_t g_zmlog = {
    .log = log,
    .logEmerg = logEmerg,
    .logAlert = logAlert,
    .logCrit = logCrit,
    .logErr = logErr,
    .logWarning = logWarning,
    .logNotice = logNotice,
    .logInfo = logInfo,
    .logDebug = logDebug
};

zmlog_t* GetLogInstance()
{
    return &g_zmlog;
}
