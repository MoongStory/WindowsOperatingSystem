// https://github.com/MoongStory/WindowsOperatingSystem

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _WINDOWS_OPERATING_SYSTEM_H_
#define _WINDOWS_OPERATING_SYSTEM_H_

#include <iostream>
#include <functional>
#include <atlbase.h>

namespace MOONG
{
	class WindowsOperatingSystem
	{
	public:
	protected:
	private:
		static PVOID old_value_;

	public:
		static const std::string GetSidString();
		static const bool GetUserName(std::string& user_name);
		static const std::string GetWindowsProductName();

		// Version Helper functions.
		// https://learn.microsoft.com/en-us/windows/win32/sysinfo/version-helper-apis

		// Windows 버전 정보.
		// https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoa

		static const bool Enable_WOW64_Redirection(const BOOLEAN enable);
		static const bool Disable_WOW64_Redirection();
		static const bool Revert_WOW64_Redirection();

		static const int MessageBoxShowMostTop(const std::string text, const std::string caption, const unsigned int type);
	protected:
	private:
	};
}
#endif	// _WINDOWS_OPERATING_SYSTEM_H_