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
		static const std::string find_execute_program(IN const std::string extension);

		static const std::string get_active_directory_account();
		static const std::string get_domain();
		static const std::string get_primary_domain();

		static const std::string get_sid_string();
		static const bool get_user_name(OUT std::string& user_name);
		static const std::string get_windows_product_name();

		// Version Helper functions.
		// https://learn.microsoft.com/en-us/windows/win32/sysinfo/version-helper-apis

		// Windows 버전 정보.
		// https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoa

		static const bool enable_wow64_redirection(IN const BOOLEAN enable);
		static const bool disable_wow64_redirection();
		static const bool revert_wow64_redirection();

		static const int messagebox_show_most_top(IN const std::string text, IN const std::string caption, IN const unsigned int type);
	protected:
	private:
	};
}
#endif	// _WINDOWS_OPERATING_SYSTEM_H_