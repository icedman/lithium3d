#ifndef _LITH_STDINT_H_
#define _LITH_STDINT_H_

typedef __int8           s8;
typedef __int16          s16;
typedef __int32          s32;
typedef __int64          s64;
typedef unsigned __int8  u8;
typedef unsigned __int16 u16;
typedef unsigned __int32 u32;
typedef unsigned __int64 u64;

typedef unsigned char byte;

#ifndef NULL
#define NULL 0
#endif // NULL

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

typedef struct tagPOINT point_t;
typedef struct tagRECT  rect_t;

#endif // _LITH_STDINT_H_

