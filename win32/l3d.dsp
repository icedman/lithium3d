# Microsoft Developer Studio Project File - Name="l3d" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=l3d - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "l3d.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "l3d.mak" CFG="l3d - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "l3d - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "l3d - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "l3d - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "../../.." /I "../../common/win32" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "NDEBUG"
# ADD RSC /l 0x1009 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows /machine:I386 /libpath:"../../../lib/win32"

!ELSEIF  "$(CFG)" == "l3d - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I "../../.." /I "../../common/win32" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x1009 /d "_DEBUG"
# ADD RSC /l 0x1009 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../../../lib/win32"

!ENDIF 

# Begin Target

# Name "l3d - Win32 Release"
# Name "l3d - Win32 Debug"
# Begin Group "Framework"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\..\common\game.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\game.h
# End Source File
# Begin Source File

SOURCE=..\..\common\win32\GameBase.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\win32\GameBase.h
# End Source File
# Begin Source File

SOURCE=..\..\common\utility.cpp
# End Source File
# Begin Source File

SOURCE=..\..\common\utility.h
# End Source File
# End Group
# Begin Group "engine"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\bucket.cpp
# End Source File
# Begin Source File

SOURCE=..\bucket.h
# End Source File
# Begin Source File

SOURCE=..\camera.cpp
# End Source File
# Begin Source File

SOURCE=..\camera.h
# End Source File
# Begin Source File

SOURCE=..\fixed.h
# End Source File
# Begin Source File

SOURCE=..\fonttiles.cpp
# End Source File
# Begin Source File

SOURCE=..\fonttiles.h
# End Source File
# Begin Source File

SOURCE=..\framebuffer.h
# End Source File
# Begin Source File

SOURCE=..\image.cpp
# End Source File
# Begin Source File

SOURCE=..\image.h
# End Source File
# Begin Source File

SOURCE=..\list.cpp
# End Source File
# Begin Source File

SOURCE=..\list.h
# End Source File
# Begin Source File

SOURCE=..\lithium3d.cpp
# End Source File
# Begin Source File

SOURCE=..\lithium3d.h
# End Source File
# Begin Source File

SOURCE=..\maths.cpp
# End Source File
# Begin Source File

SOURCE=..\maths.h
# End Source File
# Begin Source File

SOURCE=..\matrix.cpp
# End Source File
# Begin Source File

SOURCE=..\matrix.h
# End Source File
# Begin Source File

SOURCE=..\md2.cpp
# End Source File
# Begin Source File

SOURCE=..\md2.h
# End Source File
# Begin Source File

SOURCE=..\palette.cpp
# End Source File
# Begin Source File

SOURCE=..\palette.h
# End Source File
# Begin Source File

SOURCE=..\pixel.h
# End Source File
# Begin Source File

SOURCE=..\polygon.cpp
# End Source File
# Begin Source File

SOURCE=..\polygon.h
# End Source File
# Begin Source File

SOURCE=..\rasterizer.cpp
# End Source File
# Begin Source File

SOURCE=..\rasterizer.h
# End Source File
# Begin Source File

SOURCE=..\renderbasic.cpp
# End Source File
# Begin Source File

SOURCE=..\renderbasic.h
# End Source File
# Begin Source File

SOURCE=..\renderlist.cpp
# End Source File
# Begin Source File

SOURCE=..\renderlist.h
# End Source File
# Begin Source File

SOURCE=..\renderpolyimp.h
# End Source File
# Begin Source File

SOURCE=..\sample.cpp
# End Source File
# Begin Source File

SOURCE=..\sample.h
# End Source File
# Begin Source File

SOURCE=..\stdtypes.h
# End Source File
# Begin Source File

SOURCE=..\surface.cpp
# End Source File
# Begin Source File

SOURCE=..\surface.h
# End Source File
# Begin Source File

SOURCE=..\textures.cpp
# End Source File
# Begin Source File

SOURCE=..\textures.h
# End Source File
# Begin Source File

SOURCE=..\tiles.cpp
# End Source File
# Begin Source File

SOURCE=..\tiles.h
# End Source File
# Begin Source File

SOURCE=..\trace.cpp
# End Source File
# Begin Source File

SOURCE=..\trace.h
# End Source File
# Begin Source File

SOURCE=..\utils.cpp
# End Source File
# Begin Source File

SOURCE=..\utils.h
# End Source File
# Begin Source File

SOURCE=..\vector.cpp
# End Source File
# Begin Source File

SOURCE=..\vector.h
# End Source File
# Begin Source File

SOURCE=..\vertex.cpp
# End Source File
# Begin Source File

SOURCE=..\vertex.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\l3d.cpp
# End Source File
# Begin Source File

SOURCE=..\l3d.h
# End Source File
# End Target
# End Project
