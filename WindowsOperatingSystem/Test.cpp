#include "WindowsOperatingSystem.h"

int main()
{
	if (MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(FALSE))
	{
		std::cout << "GetWindowsProductName[" << MOONG::WindowsOperatingSystem::GetWindowsProductName().c_str() << "]\n" << std::endl;
		MOONG::WindowsOperatingSystem::Enable_WOW64_Redirection(TRUE);
	}

	MOONG::WindowsOperatingSystem::MessageBoxShowMostTop("test text", "test caption", MB_OK);

	return 0;
}