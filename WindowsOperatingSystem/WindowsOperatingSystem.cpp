#include "WindowsOperatingSystem.h"

// https://github.com/MoongStory/Registry
#include "../../Registry/Registry/Registry.h"

#include <Windows.h>

PVOID MOONG::WindowsOperatingSystem::old_value_ = NULL;

const std::string MOONG::WindowsOperatingSystem::GetWindowsProductName()
{
	std::string windows_version;

	std::string output;
	MOONG::Registry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName", output);

	windows_version = output;

	output.erase();
	MOONG::Registry::Read(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CSDVersion", output);
	if (output.empty() == false)
	{
		windows_version += " ";
		windows_version += output;
	}

	return windows_version;
}

const bool MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(const BOOLEAN enable)
{
	return Wow64EnableWow64FsRedirection(enable);
}

const bool MOONG::WindowsOperatingSystem::Disable_WOW64_Redirection()
{
	return Wow64DisableWow64FsRedirection(&MOONG::WindowsOperatingSystem::old_value_);
}

const bool MOONG::WindowsOperatingSystem::Revert_WOW64_Redirection()
{
	if (MOONG::WindowsOperatingSystem::old_value_ != NULL)
	{
		if (Wow64RevertWow64FsRedirection(MOONG::WindowsOperatingSystem::old_value_) == TRUE)
		{
			MOONG::WindowsOperatingSystem::old_value_ = NULL;

			return true;
		}
	}

	return false;
}

const std::string MOONG::WindowsOperatingSystem::CommandPromptExecute(const std::string command)
{
	std::string output = "";

	HANDLE hPipeRead, hPipeWrite;

	SECURITY_ATTRIBUTES saAttr = { sizeof(SECURITY_ATTRIBUTES) };
	saAttr.bInheritHandle = TRUE; // Pipe handles are inherited by child process.
	saAttr.lpSecurityDescriptor = NULL;

	// Create a pipe to get results from child's stdout.
	if (!CreatePipe(&hPipeRead, &hPipeWrite, &saAttr, 0))
	{
		// TODO: throw exception
		return "";
	}

	STARTUPINFOA si = { sizeof(STARTUPINFOA) };
	si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
	si.hStdOutput = hPipeWrite;
	si.hStdError = hPipeWrite;
	si.wShowWindow = SW_HIDE; // Prevents cmd window from flashing.
	// Requires STARTF_USESHOWWINDOW in dwFlags.

	PROCESS_INFORMATION pi = { 0 };

	BOOL fSuccess = CreateProcessA(NULL, (char*)(command.c_str()), NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);
	
	if (!fSuccess)
	{
		CloseHandle(hPipeWrite);
		CloseHandle(hPipeRead);

		// TODO: throw exception
		return "";
	}

	bool bProcessEnded = false;

	for (; !bProcessEnded;)
	{
		// Give some timeslice (50 ms), so we won't waste 100% CPU.
		bProcessEnded = WaitForSingleObject(pi.hProcess, 50) == WAIT_OBJECT_0;

		// Even if process exited - we continue reading, if
		// there is some data available over pipe.
		for (;;)
		{
			char buf[1024] = { 0 };
			DWORD dwRead = 0;
			DWORD dwAvail = 0;

			if (!::PeekNamedPipe(hPipeRead, NULL, 0, NULL, &dwAvail, NULL))
			{
				break;
			}

			if (!dwAvail) // No data available, return
			{
				break;
			}

			if (!::ReadFile(hPipeRead, buf, min(sizeof(buf) - 1, dwAvail), &dwRead, NULL) || !dwRead)
			{
				// Error, the child process might ended
				break;
			}

			buf[dwRead] = 0;
			output += buf;
		}
	}

	CloseHandle(hPipeWrite);
	CloseHandle(hPipeRead);
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	return output;
}
