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
	CString m_JavaHome;
	CAtlArray<CString> m_JavaExeArgs;
	CAtlArray<CString> m_ClassPath;

public:
	CJavaLauncher() {}
	virtual ~CJavaLauncher() {}

	bool FindJava(const CString& requiredVersion);
};
