#include "JavaLauncher.h"

static inline CString GetJavaExeName(bool windowedMode)
{
	return windowedMode ? "javaw.exe" : "java.exe";
}

bool CJavaLauncher::FindJava(const CString& requiredVersion) {
	bool success = true;
	
	HKEY javaRootKey = nullptr;
	LONG result = RegOpenKey(HKEY_LOCAL_MACHINE, _T("SOFTWARE\\JavaSoft\\Java Runtime Environment"), &javaRootKey);
	if (result != ERROR_SUCCESS) { success = false; goto cleanup; }

	HKEY versionKey = nullptr;
	result = RegOpenKey(javaRootKey, requiredVersion.GetString(), &versionKey);
	if (result != ERROR_SUCCESS) { success = false; goto cleanup; }

	DWORD valueLength = 0;
	LPTSTR buffer = m_JavaHome.GetBuffer(0);
	result = RegGetValue(versionKey, _T(""), _T("JavaHome"), RRF_RT_REG_SZ | RRF_RT_REG_EXPAND_SZ, nullptr, buffer, &valueLength);
	m_JavaHome.ReleaseBuffer();

	if (result == ERROR_MORE_DATA) {
		buffer = m_JavaHome.GetBuffer(valueLength);
		result = RegGetValue(versionKey, _T(""), _T("JavaHome"), RRF_RT_REG_SZ | RRF_RT_REG_EXPAND_SZ, nullptr, buffer, &valueLength);
		
		if (result != ERROR_SUCCESS) { success = false; goto cleanup; }
		m_JavaHome.ReleaseBuffer();
	} else {
		// If the value contains a zero-length string, then _LaunchJava() will fail.
		// While this could technically happen, in the context of CJavaLauncher it
		// is still an error.
		success = false;
	}

cleanup:
	if (javaRootKey != nullptr) RegCloseKey(javaRootKey);
	if (versionKey != nullptr) RegCloseKey(versionKey);
	return success;
}

bool CJavaLauncher::_LaunchJava(const CString& path, bool isPathJar, bool windowedMode, long& pid)
{
	// You must call FindJava() before calling this method.
	if (m_JavaHome.IsEmpty()) return false;

	CAtlArray<CString> javaArgv;
	CString javaExeName = GetJavaExeName(windowedMode);
	CString argv0; argv0.AppendFormat(_T("%S\\bin\\%S"), m_JavaHome.GetString(), javaExeName.GetString());
	javaArgv.Add(argv0);

	// Classpath
	CString classpath;
	bool firstTime = true;
	size_t limit = m_ClassPath.GetCount();
	for (size_t idx = 0; idx < limit; idx++)
	{
		if (!firstTime) classpath.Append(_T(";"));
		firstTime = false;

		classpath.Append(m_ClassPath.GetAt(idx));
	}

	javaArgv.Add(_T("-cp"));
	javaArgv.Add(classpath);
	javaArgv.Append(m_ExtraArgv);

	if (isPathJar) javaArgv.Add(_T("-jar"));
	javaArgv.Add(path);

	CString commandLine;
	limit = javaArgv.GetCount();
	for (size_t idx = 0; idx < limit; idx++)
	{
		commandLine.AppendFormat(_T("\"%S\""), javaArgv.GetAt(idx).GetString());
	}

	PROCESS_INFORMATION process;

	LPWSTR buffer = commandLine.GetBuffer();
	BOOL success = CreateProcess(NULL, buffer, NULL, NULL, FALSE, 0, NULL, NULL, NULL, &process);
	commandLine.ReleaseBuffer();
	if (!success) return false;

	CloseHandle(process.hProcess);
	CloseHandle(process.hThread);

	pid = process.dwProcessId;
	return true;
}

bool CJavaLauncher::LaunchJar(const CString& jarPath, bool windowedMode, long& pid)
{
	return _LaunchJava(jarPath, true, windowedMode, pid);
}

bool CJavaLauncher::LaunchClassFile(const CString& classFilePath, bool windowedMode, long& pid)
{
	return _LaunchJava(classFilePath, true, windowedMode, pid);
}

bool CJavaLauncher::Wait(long pid, long& exitCode)
{
	bool retval = true;

	HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pid);
	if (hProcess == INVALID_HANDLE_VALUE) {
		retval = false;
		goto cleanup;
	}

	DWORD win32Code = STILL_ACTIVE;
	do {
		WaitForSingleObject(hProcess, INFINITE);

		DWORD win32Code;
		BOOL success = GetExitCodeProcess(hProcess, &win32Code);
		if (!success) {
			retval = false;
			goto cleanup;
		}
	} while (win32Code == STILL_ACTIVE);

	exitCode = win32Code;
cleanup:
	CloseHandle(hProcess);
	return retval;
}
