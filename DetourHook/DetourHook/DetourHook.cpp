// APIHook.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <detours.h>

#pragma comment(lib, "detours.lib")

LPSTR GetLastErrorAsString()
{
    DWORD err = GetLastError();
    if(err == 0)
        return NULL;

    LPSTR msgBuf = NULL;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 NULL, err, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msgBuf, 0, NULL);
    return msgBuf;
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc < 3) {
		printf("usage: DetourHook <cmd> <dll>\n");
		return 0;
	}

	LPTSTR cmdLine = argv[1];
	LPSTR dllPath = NULL;

#ifdef UNICODE
	DWORD num = WideCharToMultiByte(CP_OEMCP, NULL, argv[2], -1, NULL, 0, NULL, FALSE);
	dllPath = new CHAR[num];
	WideCharToMultiByte(CP_OEMCP, NULL, argv[2], -1, dllPath, num, NULL, FALSE);
#else
	dllPath = argv[2];
#endif

	STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);

	DWORD flags = CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED;
    if (!DetourCreateProcessWithDll(NULL, cmdLine,
									NULL, NULL, FALSE, flags, NULL, NULL, &si, &pi,
									dllPath, NULL)) {
		LPSTR errMsg = GetLastErrorAsString();
		printf("failed to create process, error: %s", errMsg);
		LocalFree(errMsg);
	}

	ResumeThread(pi.hThread);
	WaitForSingleObject(pi.hProcess, INFINITE);
	
#ifdef UNICODE
    delete [] dllPath;
#endif

    return 0;
}
