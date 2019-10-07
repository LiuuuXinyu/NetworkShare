# Microsoft Developer Studio Generated NMAKE File, Based on SockListener.dsp
!IF "$(CFG)" == ""
CFG=SockListener - Win32 Debug
!MESSAGE No configuration specified. Defaulting to SockListener - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "SockListener - Win32 Release" && "$(CFG)" != "SockListener - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SockListener.mak" CFG="SockListener - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SockListener - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SockListener - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SockListener - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

ALL : "$(OUTDIR)\SockListener.exe"


CLEAN :
	-@erase "$(INTDIR)\MySocket.obj"
	-@erase "$(INTDIR)\SockListener.obj"
	-@erase "$(INTDIR)\SockListener.pch"
	-@erase "$(INTDIR)\SockListener.res"
	-@erase "$(INTDIR)\SockListenerDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(OUTDIR)\SockListener.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\SockListener.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SockListener.res" /d "NDEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SockListener.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\SockListener.pdb" /machine:I386 /out:"$(OUTDIR)\SockListener.exe" 
LINK32_OBJS= \
	"$(INTDIR)\SockListener.obj" \
	"$(INTDIR)\SockListenerDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SockListener.res" \
	"$(INTDIR)\MySocket.obj"

"$(OUTDIR)\SockListener.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "SockListener - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

ALL : "$(OUTDIR)\SockListener.exe"


CLEAN :
	-@erase "$(INTDIR)\MySocket.obj"
	-@erase "$(INTDIR)\SockListener.obj"
	-@erase "$(INTDIR)\SockListener.pch"
	-@erase "$(INTDIR)\SockListener.res"
	-@erase "$(INTDIR)\SockListenerDlg.obj"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(OUTDIR)\SockListener.exe"
	-@erase "$(OUTDIR)\SockListener.ilk"
	-@erase "$(OUTDIR)\SockListener.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP_PROJ=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\SockListener.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ   /c 
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /win32 
RSC_PROJ=/l 0x409 /fo"$(INTDIR)\SockListener.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\SockListener.bsc" 
BSC32_SBRS= \
	
LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\SockListener.pdb" /debug /machine:I386 /out:"$(OUTDIR)\SockListener.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\SockListener.obj" \
	"$(INTDIR)\SockListenerDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\SockListener.res" \
	"$(INTDIR)\MySocket.obj"

"$(OUTDIR)\SockListener.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("SockListener.dep")
!INCLUDE "SockListener.dep"
!ELSE 
!MESSAGE Warning: cannot find "SockListener.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "SockListener - Win32 Release" || "$(CFG)" == "SockListener - Win32 Debug"
SOURCE=.\MySocket.cpp

"$(INTDIR)\MySocket.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SockListener.pch"


SOURCE=.\SockListener.cpp

"$(INTDIR)\SockListener.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SockListener.pch"


SOURCE=.\SockListener.rc

"$(INTDIR)\SockListener.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\SockListenerDlg.cpp

"$(INTDIR)\SockListenerDlg.obj" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\SockListener.pch"


SOURCE=.\StdAfx.cpp

!IF  "$(CFG)" == "SockListener - Win32 Release"

CPP_SWITCHES=/nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\SockListener.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SockListener.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "SockListener - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Fp"$(INTDIR)\SockListener.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /GZ   /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\SockListener.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 


!ENDIF 

