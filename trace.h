
#ifndef _TRACE_H_
#define _TRACE_H_

#include <windows.h>
#include <tchar.h>
#include <stdio.h> // _vsntprintf

inline void _cdecl DbgTrace(LPCTSTR lpszFormat, ...)
{
	va_list args;
	va_start(args, lpszFormat);
	int nBuf;
	TCHAR szBuffer[512];
	nBuf = _vsntprintf(szBuffer, sizeof(szBuffer), lpszFormat, args);
	OutputDebugString(szBuffer);
	va_end(args);
}

#define TRACE(i)	DbgTrace(_T("%d\n"),i)
#define TRACEF(f)	DbgTrace(_T("%f\n"),f)
#define TRACES(s)	DbgTrace(_T("%s\n"),s)

inline unsigned long GetTick() { 
    return ::GetTickCount();
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
