#include "WindowsOperatingSystem.h"

int main()
{
	//std::cout << "GetActiveDirectoryAccount\n\t[" << MOONG::WindowsOperatingSystem::GetActiveDirectoryAccount().c_str() << "]" << std::endl;

	//std::cout << std::endl;

	//std::cout << "GetDomain\n\t[" << MOONG::WindowsOperatingSystem::GetDomain().c_str() << "]" << std::endl;

	//std::cout << std::endl;

	//std::cout << "GetPrimaryDomain\n\t[" << MOONG::WindowsOperatingSystem::GetPrimaryDomain().c_str() << "]" << std::endl;

	//std::cout << std::endl;

	//std::cout << "GetSidString[" << MOONG::WindowsOperatingSystem::GetSidString().c_str() << "]" << std::endl;

	//std::cout << std::endl;

	//std::string user_name;
	//MOONG::WindowsOperatingSystem::GetUserName(user_name);
	//std::cout << "GetUserName[" << user_name.c_str() << "]" << std::endl;

	//std::cout << std::endl;

	//std::cout << "GetWindowsProductName[" << MOONG::WindowsOperatingSystem::GetWindowsProductName().c_str() << "]\n" << std::endl;
	//MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(TRUE);

	//if (MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(FALSE))
	//{
	//	std::cout << "GetWindowsProductName[" << MOONG::WindowsOperatingSystem::GetWindowsProductName().c_str() << "]\n" << std::endl;
	//	MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(TRUE);
	//}

	//MOONG::WindowsOperatingSystem::MessageBoxShowMostTop("test text", "test caption", MB_OK);

	//std::cout << std::endl;

	std::string execute_program;
	MOONG::WindowsOperatingSystem::FindExecutable("html", execute_program);
	std::cout << "FindExecutable[" + execute_program + "]" << std::endl;

	return 0;
}