
#ifndef _LITH_UTILITY_H_
#define _LITH_UTILITY_H_

#include <windows.h>
#include <tchar.h>

#include <memory.h>
#include <malloc.h>

#include "stdtypes.h"

inline void MemSetByte(u8 *target,u8 data,int n)
{
	while(n--) {
		*target++=data;
	}
}

inline void MemSetWord(u16 *target,u16 data,int n)
{
	while(n--) {
		*target++=data;
	}
}

inline void MemSetDWord(u32 *target,u32 data,int n)
{
	while(n--) {
		*target++=data;
	}
}

inline void MemCopyWord(u16 *target,const u16 *source,int n)
{
	while(n--) {
		*target++=*source++;
	}
}

inline void MemCopyDWord(u32 *target,const u32 *source,int n)
{
	while(n--) {
		*target++=*source++;
	}
}

inline void MemCopy2DWord(u64 *target,const u64 *source,int n)
{
	while(n--) {
		*target++=*source++;
	}
}

size_t FullPathName( LPCTSTR filename, TCHAR pathname[MAX_PATH] );

#endif // _LITH_UTILITY_H_