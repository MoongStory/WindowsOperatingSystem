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

		// Windows ���� ������ �Ʒ� ��ũ ����.
		// 
		// Windows üũ�ϴ� �Լ���.
		// ���� - https://docs.microsoft.com/en-us/windows/win32/sysinfo/version-helper-apis
		// 
		// ���� �������� Windows�� ������ �䱸 ������ �����ϴ��� üũ.
		// ���� - https://docs.microsoft.com/en-us/windows/win32/api/Winbase/nf-winbase-verifyversioninfoa
		// 
		// ���� - https://docs.microsoft.com/en-us/windows/win32/api/winnt/ns-winnt-osversioninfoexa
	protected:
	private:
	};
}
#endif	// _WINDOWS_OPERATING_SYSTEM_H_