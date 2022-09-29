#pragma once
// https://github.com/MoongStory/WindowsOperatingSystem

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _WINDOWS_OPERATING_SYSTEM_H_
#define _WINDOWS_OPERATING_SYSTEM_H_

#include <iostream>
#include <functional>

namespace MOONG
{
	class WindowsOperatingSystem
	{
	public:
	protected:
	private:

	public:
		static const std::string GetWindowsProductName();

		// Windows 버전 관련은 아래 링크 참고.
		// 
		// Windows 체크하는 함수들.
		// 참고 - https://docs.microsoft.com/en-us/windows/win32/sysinfo/version-helper-apis
		// 
		// 현재 실행중인 Windows가 지정된 요구 사항을 충족하는지 체크.
		// 참고 - https://docs.microsoft.com/en-us/windows/win32/api/Winbase/nf-winbase-verifyversioninfoa
		// 
		// 참고 - https://docs.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoexa
	protected:
	private:
	};
}
#endif	// _WINDOWS_OPERATING_SYSTEM_H_