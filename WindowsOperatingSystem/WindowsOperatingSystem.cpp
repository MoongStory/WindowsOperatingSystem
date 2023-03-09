#include "WindowsOperatingSystem.h"

#if _MSC_VER <= 1200
	#ifndef _WIN32_WINNT
		#define _WIN32_WINNT 0x0501
	#endif

	#define _ATL_APARTMENT_THREADED
#endif

#include "../../Registry/Registry/Registry.h"
#include "../../ConvertDataType/ConvertDataType/ConvertDataType.h"

#include <fstream>

#include <Windows.h>

#include <Sddl.h>
#pragma comment(lib, "Advapi32.lib")	// ConvertSidToStringSid

#include <DSRole.h>
#pragma comment(lib, "netapi32.lib")    // DsRoleGetPrimaryDomainInformation

#if _MSC_VER <= 1200
	#include <shellapi.h>
	#pragma comment(lib, "Shell32.lib")    // FindExecutable
#endif

PVOID MOONG::WindowsOperatingSystem::old_value_ = NULL;

const std::string MOONG::WindowsOperatingSystem::get_active_directory_account()
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

const std::string MOONG::WindowsOperatingSystem::get_domain()
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

const std::string MOONG::WindowsOperatingSystem::get_primary_domain()
{
	// 참고 - https://stackoverflow.com/questions/9792411/how-to-get-windows-domain-name

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

const std::string MOONG::WindowsOperatingSystem::get_sid_string()
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

const bool MOONG::WindowsOperatingSystem::get_user_name(OUT std::string& user_name)
{
	char buffer[256] = { 0 };
	DWORD size = sizeof(buffer);

	bool return_value = ::GetUserNameA(buffer, &size) ? true : false;

	user_name = buffer;

	return return_value;
}

const std::string MOONG::WindowsOperatingSystem::get_windows_product_name()
{
	std::string windows_version;

	std::string output;
	MOONG::Registry::read(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "ProductName", output);

	windows_version = output;

	output.erase();
	MOONG::Registry::read(HKEY_LOCAL_MACHINE, "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", "CSDVersion", output);
	if (output.empty() == false)
	{
		windows_version += " ";
		windows_version += output;
	}

	return windows_version;
}

const bool MOONG::WindowsOperatingSystem::enable_wow64_redirection(IN const BOOLEAN enable)
{
#if _MSC_VER > 1200
	return Wow64EnableWow64FsRedirection(enable) ? true : false;
#else
	return false;
#endif
}

const bool MOONG::WindowsOperatingSystem::disable_wow64_redirection()
{
#if _MSC_VER > 1200
	return Wow64DisableWow64FsRedirection(&MOONG::WindowsOperatingSystem::old_value_) ? true : false;
#else
	return false;
#endif
}

const bool MOONG::WindowsOperatingSystem::revert_wow64_redirection()
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

const int MOONG::WindowsOperatingSystem::messagebox_show_most_top(IN const std::string text, IN const std::string caption, IN const unsigned int type)
{
	return MessageBoxA(GetDesktopWindow(), text.c_str(), caption.c_str(), type | MB_SETFOREGROUND | MB_TOPMOST | MB_SYSTEMMODAL);
}

const bool MOONG::WindowsOperatingSystem::write_credential(const std::string& internet_or_network_address, const std::string& user_name, const std::string& password, const DWORD type/* = CRED_TYPE_GENERIC*/, const DWORD persist/* = CRED_PERSIST_LOCAL_MACHINE*/)
{
	// https://learn.microsoft.com/en-us/windows/win32/api/wincred/ns-wincred-credentiala
	CREDENTIALA credential = {0};

	if (CRED_TYPE_DOMAIN_PASSWORD == type || CRED_TYPE_DOMAIN_CERTIFICATE == type)
	{
		credential.Flags = CRED_FLAGS_USERNAME_TARGET;
	}
	else
	{
		credential.Flags = CRED_FLAGS_PROMPT_NOW;
	}
	credential.Type = type;
	credential.TargetName = const_cast<char*>(internet_or_network_address.c_str());
	credential.Comment;
	credential.LastWritten; // 쓰기 작업의 경우 이 값은 무시됨.
	credential.CredentialBlobSize = static_cast<DWORD>(password.length());
	credential.CredentialBlob = reinterpret_cast<LPBYTE>(const_cast<char*>(password.c_str()));
	credential.Persist = persist;
	credential.AttributeCount;
	credential.Attributes;
	credential.TargetAlias;
	credential.UserName = const_cast<char*>(user_name.c_str());
	
	// 자격 증명 등록
	return CredWriteA(&credential, 0);
}


const std::string MOONG::WindowsOperatingSystem::find_execute_program(IN const std::string extension)
{
	std::ofstream create_file(std::string(std::string("dummy.") + extension).c_str());
	create_file.close();

	char temp[MAX_PATH] = { 0 };
	FindExecutableA(std::string(std::string("dummy.") + extension).c_str(), NULL, temp);

	std::string execute_program = temp;

	DeleteFileA(std::string(std::string("dummy.") + extension).c_str());

	return execute_program;
}
