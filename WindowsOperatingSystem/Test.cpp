#include "WindowsOperatingSystem.h"

int main()
{
	if (MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(FALSE))
	{
		std::cout << "GetWindowsProductName[" << MOONG::WindowsOperatingSystem::GetWindowsProductName().c_str() << "]\n" << std::endl;
		MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(TRUE);
	}

	std::cout << "CommandPromptExecute[" << MOONG::WindowsOperatingSystem::command_prompt.Execute("ping www.google.com").c_str() << "]\n" << std::endl;

	return 0;
}