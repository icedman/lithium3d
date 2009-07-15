
#include "utils.h"

size_t FullPathName( LPCTSTR filename, TCHAR pathname[MAX_PATH] )
{
    if (filename[0] == '\\')
    {
        // Absolute path was specified
        _tcscpy( pathname, filename );
        return _tcslen( pathname );
    }

#if defined(_WIN32_WCE)

    ::GetModuleFileName( 0, pathname, MAX_PATH );
  
    TCHAR* p = _tcsrchr( pathname, '\\' );
    if (p == 0) return 0;

    _tcscpy( p + 1, filename );

	return _tcslen( pathname );

#else

    TCHAR* p;
    return ::GetFullPathName( filename, MAX_PATH, pathname, &p );

#endif
}