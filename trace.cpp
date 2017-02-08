
#include "trace.h"

#include <stdarg.h>
#include <stdlib.h>

unsigned long g_tickStart=0;
unsigned long g_tickEnd=0;
unsigned long g_tickCount=0;
unsigned long g_tickAverage=0;

void ProfileBegin()
{
	g_tickStart=GetTick();
}

void ProfileEnd()
{
	g_tickEnd=GetTick();
	g_tickCount++;

	g_tickAverage+=(g_tickEnd-g_tickStart);
}

unsigned long ProfileAverage()
{
	if (g_tickCount==0)
		return 0;
	return g_tickAverage=(g_tickAverage + (g_tickEnd-g_tickStart))/g_tickCount;
}

void DbgTrace(LPCTSTR lpszFormat, ...)
{
    va_list args;
    va_start(args, lpszFormat);
    int nBuf;
    TCHAR szBuffer[512];
    nBuf = vsprintf(szBuffer, lpszFormat, args);
    
    fprintf(stdout, "%s", szBuffer);
    // OutputDebugString(szBuffer);

    va_end(args);
}