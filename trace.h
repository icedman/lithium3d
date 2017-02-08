
#ifndef _TRACE_H_
#define _TRACE_H_

#include "stdtypes.h"

// #include <windows.h>
// #include <tchar.h>
#include <stdio.h> // _vsntprintf

// inline void _cdecl DbgTrace(LPCTSTR lpszFormat, ...)
void DbgTrace(LPCTSTR lpszFormat, ...);


#define TRACE(i)	DbgTrace(_T("%d\n"),i)
#define TRACEF(f)	DbgTrace(_T("%f\n"),f)
#define TRACES(s)	DbgTrace(_T("%s\n"),s)

inline unsigned long GetTick() { 
    // return ::GetTickCount();
    return 0;
}

void ProfileBegin();
void ProfileEnd();
unsigned long ProfileAverage();

#define PROFILE_BEGIN(loop) \
	ProfileBegin(); \
	for(int pr=0;pr<loop;pr++) {
#define PROFILE_END() \
	} \
	ProfileEnd();

#endif // _TRACE_H_
