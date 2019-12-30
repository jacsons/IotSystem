#include <stdio.h>
#include "zmmem.h"
#include "zmerror.h"

void* zm_zalloc(u32 size)
{
    int ret;
    void *buff = NULL;
    //todo check param
    buff = malloc(size);

    if(buff == NULL) {
        return NULL;
    }

    ret = memset_s(buff, size, 0, size);
    if (ret != EOK) {
        zm_free(buff);
    }

    return buff;
}

void zm_free(void *buff)
{
    free(buff);
}

int main()
{
    printf("Hello world\n");
    return 0;
}

