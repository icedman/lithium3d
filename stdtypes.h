#ifndef _LITH_STDINT_H_
#define _LITH_STDINT_H_

typedef char            s8;
typedef int             s16;
typedef long            s32;
typedef long long            s64;
typedef unsigned char   u8;
typedef unsigned int    u16;
typedef unsigned long   u32;
typedef unsigned long long   u64;

typedef unsigned char byte;

#if !defined(WIN32)
typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef unsigned long LONG;
typedef unsigned int UNINT32;
#endif

#ifndef NULL
#define NULL 0
#endif // NULL

#ifndef TRUE
#define TRUE 1
#endif // TRUE

#ifndef FALSE
#define FALSE 0
#endif // FALSE

typedef struct {
    int x;
    int y;
} point_t;

typedef struct {
    int left;
    int right;
    int top;
    int bottom;
} rect_t;

typedef char TCHAR;
typedef const char* LPCTSTR;
#define MAX_PATH 1024

#define _T(a) a

#endif // _LITH_STDINT_H_

