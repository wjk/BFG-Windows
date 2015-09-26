#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

EXTERN_C HINSTANCE JavaLauncherModule;
HINSTANCE JavaLauncherModule = (HINSTANCE)INVALID_HANDLE_VALUE;
INT_PTR WINAPI DllMain(HINSTANCE hDll, DWORD reason, PVOID reserved)
{
	if (reason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hDll);
		JavaLauncherModule = hDll;
	}

	return (INT_PTR)TRUE;
}
