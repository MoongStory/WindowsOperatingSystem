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