// https://github.com/MoongStory/WindowsOperatingSystem

#if _MSC_VER > 1000
#pragma once
#endif

#ifndef _WINDOWS_OPERATING_SYSTEM_H_
#define _WINDOWS_OPERATING_SYSTEM_H_

#include <iostream>
#include <functional>
#include <atlbase.h>

#include "../../CommandPrompt/CommandPrompt/CommandPrompt.h"

namespace MOONG
{
	class WindowsOperatingSystem
	{
	public:
		static CommandPrompt command_prompt;
	protected:
	private:
		static PVOID old_value_;

	public:
		static const std::string GetWindowsProductName();

		// Version Helper functions.
		// https://learn.microsoft.com/en-us/windows/win32/sysinfo/version-helper-apis

		// Windows ���� ����.
		// https://learn.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoa

		static const bool Enable_WOW64_Redirection(const BOOLEAN enable);
		static const bool Disable_WOW64_Redirection();
		static const bool Revert_WOW64_Redirection();
	protected:
	private:
	};
}
#endif	// _WINDOWS_OPERATING_SYSTEM_H_