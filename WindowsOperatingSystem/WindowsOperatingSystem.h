/*******************************************************************************
MIT License

Copyright (c) 2023 Moong

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*******************************************************************************/

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
		static const std::string FindExecuteProgram(IN const std::string extension);

		static const std::string GetActiveDirectoryAccount();
		static const std::string GetDomain();
		static const std::string GetPrimaryDomain();

		static const std::string GetSidString();
		static const bool GetUserName(OUT std::string& user_name);
		static const std::string GetWindowsProductName();

		// Version Helper functions.
		// https://learn.microsoft.com/en-us/windows/win32/sysinfo/version-helper-apis

		// Windows 버전 정보.
		// https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoa

		static const bool Enable_WOW64_Redirection(IN const BOOLEAN enable);
		static const bool Disable_WOW64_Redirection();
		static const bool Revert_WOW64_Redirection();

		static const int MessageBoxShowMostTop(IN const std::string text, IN const std::string caption, IN const unsigned int type);
	protected:
	private:
	};
}
#endif	// _WINDOWS_OPERATING_SYSTEM_H_