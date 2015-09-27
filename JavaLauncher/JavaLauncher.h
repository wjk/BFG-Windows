#pragma once

#ifndef __cplusplus
#error C++ is required to use this library.
#endif

#include <atlbase.h>
#include <atlstr.h>
#include <atlcoll.h>

class CJavaLauncher
{
private:
	CString m_JavaHome = "";
	CAtlArray<CString> m_ClassPath;
	CAtlArray<CString> m_ExtraArgv;

	bool _LaunchJava(const CString& path, bool isPathJar, bool windowedMode, long& pid);

public:
	CJavaLauncher() {}
	virtual ~CJavaLauncher() {}

	void SetClassPath(const CAtlArray<CString>& classPath)
	{
		m_ClassPath.Copy(classPath);
	}

	void GetClassPath(CAtlArray<CString>& classPath)
	{
		classPath.Copy(m_ClassPath);
	}

	void SetExtraArguments(CAtlArray<CString>& argv)
	{
		m_ExtraArgv.Copy(argv);
	}

	void GetExtraArguments(CAtlArray<CString>& argv)
	{
		argv.Copy(m_ExtraArgv);
	}

	bool FindJava(const CString& requiredVersion);
	bool LaunchJar(const CString& jarPath, bool windowedMode, long& pid);
	bool LaunchClassFile(const CString& classFilePath, bool windowedMode, long& pid);
	bool Wait(long pid, long& exitCode);
};
