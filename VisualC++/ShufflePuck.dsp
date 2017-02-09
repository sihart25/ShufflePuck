# Microsoft Developer Studio Project File - Name="ShufflePuck" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=ShufflePuck - Win32 DebugWithoutSound
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ShufflePuck.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ShufflePuck.mak" CFG="ShufflePuck - Win32 DebugWithoutSound"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ShufflePuck - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "ShufflePuck - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE "ShufflePuck - Win32 ReleaseWithoutSound" (based on "Win32 (x86) Console Application")
!MESSAGE "ShufflePuck - Win32 DebugWithoutSound" (based on "Win32 (x86) Console Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "ShufflePuck"
# PROP Scc_LocalPath "."
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ShufflePuck - Win32 Release"

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
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_OPENAL" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib openal32.lib alut.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "ShufflePuck - Win32 Debug"

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
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_OPENAL" /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib openal32.lib alut.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ELSEIF  "$(CFG)" == "ShufflePuck - Win32 ReleaseWithoutSound"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "ShufflePuck___Win32_ReleaseWithoutSound"
# PROP BASE Intermediate_Dir "ShufflePuck___Win32_ReleaseWithoutSound"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "ReleaseWithoutSound"
# PROP Intermediate_Dir "ReleaseWithoutSound"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_OPENAL" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD BASE RSC /l 0x809 /d "NDEBUG"
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib openal32.lib alut.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

!ELSEIF  "$(CFG)" == "ShufflePuck - Win32 DebugWithoutSound"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "ShufflePuck___Win32_DebugWithoutSound"
# PROP BASE Intermediate_Dir "ShufflePuck___Win32_DebugWithoutSound"
# PROP BASE Ignore_Export_Lib 0
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "DebugWithoutSound"
# PROP Intermediate_Dir "DebugWithoutSound"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /D "_OPENAL" /YX /FD /GZ /c
# ADD CPP /nologo /W3 /Gm /GX /ZI /Od /D "_DEBUG" /D "WIN32" /D "_CONSOLE" /D "_MBCS" /YX /FD /GZ /c
# ADD BASE RSC /l 0x809 /d "_DEBUG"
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib openal32.lib alut.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "ShufflePuck - Win32 Release"
# Name "ShufflePuck - Win32 Debug"
# Name "ShufflePuck - Win32 ReleaseWithoutSound"
# Name "ShufflePuck - Win32 DebugWithoutSound"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Source\Bitmap.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Block.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Camera.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Collision.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Colour.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Control.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Cylinder.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Disc.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Display.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Font.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Game.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Group.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Label.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Light.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Line.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Main.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Material.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Node.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Physical.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Plane.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Player.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Post.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Puck.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Reader.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Reference.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Screen.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Shape.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Sound.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Texture.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Transform.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Vectors.cpp
# End Source File
# Begin Source File

SOURCE=..\Source\Wall.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Source\Bitmap.h
# End Source File
# Begin Source File

SOURCE=..\Source\Block.h
# End Source File
# Begin Source File

SOURCE=..\Source\Camera.h
# End Source File
# Begin Source File

SOURCE=..\Source\Collision.h
# End Source File
# Begin Source File

SOURCE=..\Source\Colour.h
# End Source File
# Begin Source File

SOURCE=..\Source\Constants.h
# End Source File
# Begin Source File

SOURCE=..\Source\Control.h
# End Source File
# Begin Source File

SOURCE=..\Source\Cylinder.h
# End Source File
# Begin Source File

SOURCE=..\Source\Disc.h
# End Source File
# Begin Source File

SOURCE=..\Source\Display.h
# End Source File
# Begin Source File

SOURCE=..\Source\Font.h
# End Source File
# Begin Source File

SOURCE=..\Source\Game.h
# End Source File
# Begin Source File

SOURCE=..\Source\Group.h
# End Source File
# Begin Source File

SOURCE=..\Source\Label.h
# End Source File
# Begin Source File

SOURCE=..\Source\Light.h
# End Source File
# Begin Source File

SOURCE=..\Source\Line.h
# End Source File
# Begin Source File

SOURCE=..\Source\Material.h
# End Source File
# Begin Source File

SOURCE=..\Source\Node.h
# End Source File
# Begin Source File

SOURCE=..\Source\Physical.h
# End Source File
# Begin Source File

SOURCE=..\Source\Plane.h
# End Source File
# Begin Source File

SOURCE=..\Source\Player.h
# End Source File
# Begin Source File

SOURCE=..\Source\Post.h
# End Source File
# Begin Source File

SOURCE=..\Source\Puck.h
# End Source File
# Begin Source File

SOURCE=..\Source\Reader.h
# End Source File
# Begin Source File

SOURCE=..\Source\Reference.h
# End Source File
# Begin Source File

SOURCE=..\Source\Screen.h
# End Source File
# Begin Source File

SOURCE=..\Source\Shape.h
# End Source File
# Begin Source File

SOURCE=..\Source\Sound.h
# End Source File
# Begin Source File

SOURCE=..\Source\Texture.h
# End Source File
# Begin Source File

SOURCE=..\Source\Transform.h
# End Source File
# Begin Source File

SOURCE=..\Source\Vectors.h
# End Source File
# Begin Source File

SOURCE=..\Source\Wall.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Source File

SOURCE=..\Data\Game.txt
# End Source File
# End Target
# End Project
