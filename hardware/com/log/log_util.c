// IOT LOG FILE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <syslog.h>
#include <stdarg.h>

#include "log_util.h"
#include "ComMacro.h"

#define DEFAULT_LOG_LEVEL 5

void logUtil(unsigned int lev,const char *msg,...);


FILE *fp = NULL;
STATIC int init_file_point(void)
{
	if(NULL==fp) {
		fp = fopen("/var/test.log","a+");
	}

	return fp != NULL ? 0 : 1;
}

STATIC void add_time_tag(char *dst,int bufsize,const char *format,...)
{
	time_t now;
	time(&now);
	struct tm *local;
	local = localtime(&now);
	strftime(dst,bufsize,"%m-%d %T ",local);
    strcat(dst,format);
}

void logUtil(unsigned int lev,const char *msg,...)
{
	int len = 0,mal_flag = 0, bufsize = 0;
	char *ptr = NULL;
	char buf[512] = {0};

	if (lev <= DEFAULT_LOG_LEVEL) {
		va_list ap;
		openlog("tag",LOG_PID,LOG_USER);
		va_start(ap,msg);

		if( (flag_pf) || (lev==LOG_ERR) )
		{
			len = strlen(msg);
			if(len<(512-40))
			{
				ptr = buf;
				bufsize = 512;
			}
			else
			{
				mal_flag = 1;
				bufsize = len + 40;
				ptr = (char *)malloc(bufsize);
				bzero(ptr,bufsize);
			}
			add_time_tag(ptr,bufsize,msg);
		}

		if(flag_pf) {
			vprintf(ptr,ap);
		}

		if( (NULL != fp) && (lev==LOG_ERR)) { //如果级别是错误，同时打印到File流文件
			vfprintf(fp,ptr,ap); // 在嵌入式平台中只需要这行就行
		}

		if(1 == mal_flag) {
			free(ptr);
		}

		vsyslog(lev,msg,ap);   //syslog有时间前缀，所有不使用增加前缀的ptr指针

		va_end(ap);
		closelog();
	}
}


#ifdef UT_TEST
#define PROGRAM "[process name] "
#define my_debug(format,...)  logUtil(LOG_DEBUG, PROGRAM  "[%s:%d] " format,__FILE__,__LINE__,##__VA_ARGS__)
int main(int argc, const char *argv[])
{

	init_file_point();

	int i = 8, j = 5;
	my_debug("i+j = %d\n",i+j);

	return 0;
}
#endif
