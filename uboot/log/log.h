/*****************************************************************************
* Copyright: 2020-2030, ***oak***
* file name: log.h
* Description: uboot log file
* Author: oak
* Version: v-0.0.1
* Date: 2020-02-01 12:07:36
* History: 
***************************************************************************/
#ifndef __LOG_H__
#define __LOG_H__

// log level 
enum LogLevel {
    LOG_EMERG = 0, 	//emerger
    LOG_ALERT = 1, 	//必须立即修复状态
    LOG_CRIT = 2, 	//严重状态
    LOG_ERR = 3, 	//出错状态
    LOG_WARNING = 4, 	//警告状态
    LOG_NOTICE = 5, 	//正常，但重要的状态
    LOG_INFO = 6, 	//信息性消息
    LOG_DEBUG = 7, 	//调试消息
};

/*****************************************************************************
* Function: logUtil
* Description: log common function
* Param {enum LogLevel}: log level
* Param {modelName}: model name
* Output: None
* Return: void
***************************************************************************/
void logUtil(enum LogLevel level,const char *format, ...);

#define LOG_EMERG(format, ...)  logUtil(LOG_EMERG, "[EMERG][%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_ALERT(format, ...)  logUtil(LOG_ALERT, "[ALERT][%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_CRIT(format,...)  logUtil(LOG_CRIT, "[CRIT][%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_ERR(format,...)  logUtil(LOG_ERR, "[ERROR][%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_WARNING(format, ...)  logUtil(LOG_WARNING, "[WARNING][%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_NOTICE(format, ...)  logUtil(LOG_NOTICE, "[NOTICE][%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_INFO(format,...)  logUtil(LOG_INFO, "[INFO][%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
#define LOG_DEBUG(format,...)  logUtil(LOG_DEBUG, "[DEBUG][%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)


#endif
