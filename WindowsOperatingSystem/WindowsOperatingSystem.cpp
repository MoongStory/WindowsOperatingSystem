#include "WindowsOperatingSystem.h"

#include "../../Registry/Registry/Registry.h"
#include "../../ConvertDataType/ConvertDataType/ConvertDataType.h"

#include <fstream>

#include <Windows.h>

#include <sddl.h>
#pragma comment(lib, "Advapi32.lib")	// ConvertSidToStringSid

#include <DSRole.h>
#pragma comment(lib, "netapi32.lib")    // DsRoleGetPrimaryDomainInformation

PVOID MOONG::WindowsOperatingSystem::old_value_ = NULL;

const std::string MOONG::WindowsOperatingSystem::GetActiveDirectoryAccount()
{
	USES_CONVERSION;

	HANDLE hToken = NULL;
	DWORD dwSize = 0;
	char lpName[256] = { 0 };
	char lpDomain[256] = { 0 };
	DWORD dwResult = 0;
	DWORD dwNameSize = 256;
	SID_NAME_USE SidType;
	PSID pSID = NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;
	PTOKEN_USER pUserInfo = { 0 };

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		return "";
	}

	if (!GetTokenInformation(hToken, TokenUser, NULL, dwSize, &dwSize))
	{
		dwResult = GetLastError();

		if (dwResult != ERROR_INSUFFICIENT_BUFFER)
		{
			CloseHandle(hToken);

			return "";
		}
	}

	pUserInfo = (PTOKEN_USER)(GlobalAlloc(GPTR, dwSize));
	if (pUserInfo == NULL)
	{
		CloseHandle(hToken);

		return "";
	}

	if (!GetTokenInformation(hToken, TokenUser, pUserInfo, dwSize, &dwSize))
	{
		CloseHandle(hToken);

		return "";
	}

	dwSize = 256;

	if (!LookupAccountSidA(NULL, pUserInfo->User.Sid, lpName, &dwSize, lpDomain, &dwSize, &SidType))
	{
		CloseHandle(hToken);

		return "";
	}

	if (pUserInfo)
	{
		GlobalFree(pUserInfo);
	}

	CloseHandle(hToken);

	return lpName;
}

const std::string MOONG::WindowsOperatingSystem::GetDomain()
{
	USES_CONVERSION;

	HANDLE hToken = NULL;
	DWORD dwSize = 0;
	char lpName[256] = { 0 };
	char lpDomain[256] = { 0 };
	DWORD dwResult = 0;
	DWORD dwNameSize = 256;
	SID_NAME_USE SidType;
	PSID pSID = NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;
	PTOKEN_USER pUserInfo = { 0 };

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		return "";
	}

	if (!GetTokenInformation(hToken, TokenUser, NULL, dwSize, &dwSize))
	{
		dwResult = GetLastError();

		if (dwResult != ERROR_INSUFFICIENT_BUFFER)
		{
			CloseHandle(hToken);

			return "";
		}
	}

	pUserInfo = (PTOKEN_USER)(GlobalAlloc(GPTR, dwSize));
	if (pUserInfo == NULL)
	{
		CloseHandle(hToken);

		return "";
	}

	if (!GetTokenInformation(hToken, TokenUser, pUserInfo, dwSize, &dwSize))
	{
		CloseHandle(hToken);

		return "";
	}

	dwSize = 256;

	if (!LookupAccountSidA(NULL, pUserInfo->User.Sid, lpName, &dwSize, lpDomain, &dwSize, &SidType))
	{
		CloseHandle(hToken);

		return "";
	}

	if (pUserInfo)
	{
		GlobalFree(pUserInfo);
	}

	CloseHandle(hToken);

	return lpDomain;
}

const std::string MOONG::WindowsOperatingSystem::GetPrimaryDomain()
{
	// Âü°í - https://stackoverflow.com/questions/9792411/how-to-get-windows-domain-name

	DSROLE_PRIMARY_DOMAIN_INFO_BASIC* info = NULL;

	if (DsRoleGetPrimaryDomainInformation(NULL, DsRolePrimaryDomainInfoBasic, (PBYTE*)&info) != ERROR_SUCCESS)
	{
		return "";
	}

	std::string return_string = "";

	if (info->DomainForestName != NULL)
	{
		try
		{
			return_string = MOONG::ConvertDataType::wstring_to_string(info->DomainForestName);
		}
		catch (const std::bad_alloc&)
		{
			return_string = "";
		}
	}

	if (info != NULL)
	{
		DsRoleFreeMemory(info);
	}

	return return_string;
}

const std::string MOONG::WindowsOperatingSystem::GetSidString()
{
	USES_CONVERSION;

	HANDLE hToken = NULL;
	DWORD dwSize = 0;
	char lpName[256] = { 0 };
	char lpDomain[256] = { 0 };
	DWORD dwResult = 0;
	DWORD dwNameSize = 256;
	PSID pSID = NULL;
	SID_IDENTIFIER_AUTHORITY SIDAuth = SECURITY_NT_AUTHORITY;
	PTOKEN_USER pUserInfo = { 0 };

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
	{
		return "";
	}

	if (!GetTokenInformation(hToken, TokenUser, NULL, dwSize, &dwSize))
	{
		dwResult = GetLastError();

		if (dwResult != ERROR_INSUFFICIENT_BUFFER)
		{
			CloseHandle(hToken);

			return "";
		}
	}

	pUserInfo = (PTOKEN_USER)(GlobalAlloc(GPTR, dwSize));
	if (pUserInfo == NULL)
	{
		CloseHandle(hToken);

		return "";
	}

	if (!GetTokenInformation(hToken, TokenUser, pUserInfo, dwSize, &dwSize))
	{
		CloseHandle(hToken);

		return "";
	}

	LPSTR sidString;
	ConvertSidToStringSidA(pUserInfo->User.Sid, &sidString);

	std::string return_value = sidString;

	if (pUserInfo)
	{
		GlobalFree(pUserInfo);
	}

	CloseHandle(hToken);

	return return_value;
}

const bool MOONG::WindowsOperatingSystem::GetUserName(OUT std::string& user_name)
{
	char buffer[256] = { 0 };
	DWORD size = sizeof(buffer);

	bool return_value = ::GetUserNameA(buffer, &size) ? true : false;

	user_name = buffer;

	return return_value;
}

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

const bool MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(IN const BOOLEAN enable)
{
	return Wow64EnableWow64FsRedirection(enable) ? true : false;
}

const bool MOONG::WindowsOperatingSystem::Disable_WOW64_Redirection()
{
#if _MSC_VER > 1200
	return Wow64DisableWow64FsRedirection(&MOONG::WindowsOperatingSystem::old_value_) ? true : false;
#else
	return false;
#endif
}

const bool MOONG::WindowsOperatingSystem::Revert_WOW64_Redirection()
{
#if _MSC_VER > 1200
	if (MOONG::WindowsOperatingSystem::old_value_ != NULL)
	{
		if (Wow64RevertWow64FsRedirection(MOONG::WindowsOperatingSystem::old_value_) == TRUE)
		{
			MOONG::WindowsOperatingSystem::old_value_ = NULL;

			return true;
		}
	}
#endif

	return false;

}

const int MOONG::WindowsOperatingSystem::MessageBoxShowMostTop(IN const std::string text, IN const std::string caption, IN const unsigned int type)
{
	return MessageBoxA(GetDesktopWindow(), text.c_str(), caption.c_str(), type | MB_SETFOREGROUND | MB_TOPMOST | MB_SYSTEMMODAL);
}


const HINSTANCE MOONG::WindowsOperatingSystem::FindExecutable(IN const std::string extension, OUT std::string& execute_program)
{
	std::ofstream create_file(std::string("dummy.") + extension);
	create_file.close();

	char temp[MAX_PATH] = { 0 };
	HINSTANCE return_value = ::FindExecutableA(std::string(std::string("dummy.") + extension).c_str(), NULL, temp);
	execute_program = temp;

	DeleteFileA(std::string(std::string("dummy.") + extension).c_str());

	return return_value;
}
