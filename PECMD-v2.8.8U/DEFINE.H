

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Header
#pragma once
#include <Windows.h>
#define AFX_TARG_CHS
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Program information
#define STR_AppName			TEXT("PECMD")
#define STR_AppDesc			TEXT("WinPE Commander (Modified By Lxl1638)")
#define STR_FileName			STR_AppName TEXT(".EXE")
#define STR_Company			TEXT("Yonsm.NET")
#define STR_Copyright			TEXT("CopyLeft (L) 2006-2007 ") STR_Company TEXT(" All rights reserved.")
#define STR_Comments			TEXT("Modified By Lxl1638\r\n茂名市第二中学 老九")
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Version information
#define _MakeStr(v)			#v
#define _MakeVer(a, b, c, d)		_MakeStr(a.b.c.d)
#define VER_Major			2
#define VER_Minor			8
#define VER_Release			802  
#define VER_Build			0162
#define VER_Version			MAKELONG(MAKEWORD(VER_Major, VER_Minor), VER_Release)
#define STR_Version			TEXT(_MakeVer(VER_Major, VER_Minor, VER_Release, VER_Build))
#define STR_BuildStamp			TEXT(__DATE__) TEXT(" ") TEXT(__TIME__)
#if defined(_M_X64)
#define STR_Architecture		"amd64"
#define STR_VersionStamp		STR_Version TEXT(" X64")
#elif defined(_M_IA64)
#define STR_Architecture		"ia64"
#define STR_VersionStamp		STR_Version TEXT(" IA64")
#elif defined(WIN32_PLATFORM_WFSP)
#define STR_VersionStamp		STR_Version //TEXT(" SP")
#elif defined(WIN32_PLATFORM_PSPC)
#define STR_VersionStamp		STR_Version
#else
#define STR_Architecture		"x86"
#ifdef _UNICODE
#define STR_VersionStamp		STR_Version TEXT(" X86U")
#else
#define STR_VersionStamp		STR_Version TEXT(" X86")
#endif
#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
