#ifdef __ZM_FILE_H__
#define __ZM_FILE_H__
#include <stdio.h>

typedef struct zmfile_util {
    int (*realpathOpen)(const char *filepath, int flags, int mode);
    int (*realpathCreateOpen)(const char *filepath, int flags, int mode);
    File* (*realpathFileOpen)(const char *filepath, const char *flags);

} zmfile_util_t;


zmfile_util_t* GetFileInstance();


#endif
