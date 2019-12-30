#include "zmfile.h"
#include "common.h"


STATIC do_realpath(const char *filepath, char *realpathRes)
{
    //

}

STATIC int (*realpathOpen)(const char *filepath, int flags, int mode)
{
    int fd = -1;



    fd = open()


    return fd;
}

STATIC int (*realpathCreateOpen)(const char *filepath, int flags, int mode)
{
    int fd = -1;

    return fd;
}

STATIC File* (*realpathFileOpen)(const char *filepath, const char *flags)
{
    File * filep = NULL;

    return filep;
}


zmfile_util_t g_zmfile_util = {
    .realpathOpen = realpathOpen,
    .realpathCreateOpen = realpathCreateOpen,
    .realpathFileOpen = realpathFileOpen
};

zmfile_util_t* GetFileInstance()
{
    return &g_zmfile_util;
}

