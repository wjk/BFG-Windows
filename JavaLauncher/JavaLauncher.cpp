#include "JavaLauncher.h"

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
	} else if (result == ERROR_SUCCESS) {
		// The value contains a zero-length string. This should never happen, but whatever.
		m_JavaHome.Empty();
	} else {
		success = false;
	}

cleanup:
	if (javaRootKey != nullptr) RegCloseKey(javaRootKey);
	if (versionKey != nullptr) RegCloseKey(versionKey);
	return success;
}
