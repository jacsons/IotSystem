#ifndef __RESULT_MACRO_H__
#define __RESULT_MACRO_H__

#define ASSERT_RET(a, v) do{    \
    if(!(a) {                   \
            return v;           \
    }                           \
} while(0)

#define ASSERT_RET_DO_SOMETHIN(a, v, something) do{    \
    if(!(a) {                   \
            something;          \
            return v;           \
    }                           \
} while(0)


#define ASSERT_GOTO(a, v) do{    \
    if(!(a) {                   \
            goto v;           \
    }                           \
} while(0)




#endif
