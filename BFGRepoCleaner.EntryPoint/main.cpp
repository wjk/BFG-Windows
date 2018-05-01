#include <stdio.h>
#include <tchar.h>
#include <JavaLauncher.h>

// Change this when upgrading bfg-repo-cleaner
static CString JarName = _T("bfg-1.13.0.jar");

int _tmain(int argc, const TCHAR *argv[])
{
	CJavaLauncher java;
	bool success;

	// Prefer Java 1.8, as it's newer. Fall back to 1.7 if necessary.
	// Note: Java before 1.7 is not supported.
	success = java.FindJava(_T("1.8"));
	if (!success) {
		success = java.FindJava(_T("1.7"));
		if (!success) {
			_ftprintf(stderr, _T("ERROR: Could not find Java (1.7 required, 1.8 preferred)\n"));
			return -1;
		}
	}

	CString MyPath;
	
	LPTSTR buffer = MyPath.GetBuffer(MAX_PATH);
	DWORD errorCode = GetModuleFileName(NULL, buffer, MAX_PATH);
	MyPath.ReleaseBuffer();

	if (errorCode == 0) {
		_ftprintf(stderr, _T("ERROR: GetModuleFileName() failed with code %d\n"), GetLastError());
		return -1;
	}

	CString JarPath;
	CString MyDir = MyPath.Left(MyPath.ReverseFind('\\'));
	JarPath.AppendFormat(_T("%lS\\%lS"), MyDir.GetString(), JarName.GetString());

	CAtlArray<CString> programArgv;
	for (int i = 1; i < argc; i++) {
		CString arg(argv[i]);
		programArgv.Add(arg);
	}

	java.SetProgramArguments(programArgv);

	long pid;
	success = java.LaunchJar(JarPath, false, pid);
	if (!success) {
		_ftprintf(stderr, _T("ERROR: Could not launch java.exe\n"));
		return -1;
	}

	long exitCode;
	success = java.Wait(pid, exitCode);
	if (!success) {
		_ftprintf(stderr, _T("ERROR: CJavaLauncher::Wait() returned false\n"));
		return -1;
	}

	return exitCode;
}
