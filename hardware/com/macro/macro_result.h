#ifndef __RESULT_MACRO__
#define __RESULT_MACRO__


#define ASSERT_RRT(value, ret)  \
    do{                         \
        if (!(value)){          \
            return ret;         \
        }                       \
    }while(0)

#define ASSERT_GOTO(value, token)   \
    do{                             \
        if (!(value)){              \
            goto ret;               \
        }                           \
    }while(0)

#define ASSERT_DO_SOMETHIN(vlaue, something, ret)  \
    do{                             \
        if(!(value)){               \
            (something);            \
            return (ret);           \
        }                           \
    }while(0)

#endif
