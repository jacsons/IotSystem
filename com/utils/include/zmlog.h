#ifndef __ZM_LOG_H__
#define __ZM_LOG_H__



#define	LOG_EMERG   0 	//紧急状态
#define	LOG_ALERT   1 	//必须立即修复状态
#define	LOG_CRIT    2 	//严重状态
#define LOG_ERR     3 	//出错状态
#define	LOG_WARNING 4 	//警告状态
#define	LOG_NOTICE  5 	//正常，但重要的状态
#define	LOG_INFO    6 	//信息性消息
#define	LOG_DEBUG   7 	//调试消息


void logUtil(unsigned int lev,const char *msg,...);

#define LOG_EMERG_INFO(format,moduleName, ...)  logUtil(LOG_EMERG, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_ALERT_INFO(format,...)  logUtil(LOG_ALERT, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_CRIT_INFO(format,...)  logUtil(LOG_CRIT, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_ERR_INFO(format,...)  logUtil(LOG_ERR, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_WARNING_INFO(format,...)  logUtil(LOG_WARNING, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_NOTICE_INFO(format,...)  logUtil(LOG_NOTICE, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_INFO_INFO(format,...)  logUtil(LOG_INFO, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_DEBUG_INFO(format,...)  logUtil(LOG_DEBUG, moduleName  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)

#endif
