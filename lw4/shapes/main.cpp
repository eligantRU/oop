#include "stdafx.h"

#include "ConsoleMenu.h"

int main(int, char * [])
{
	CConsoleMenu menu;
	std::string commandLine;
	try
	{
		std::cout << std::endl << ">> ";
		while (std::getline(std::cin, commandLine))
		{
			try
			{
				menu.DoCommand(commandLine);
			}
			catch (const std::invalid_argument & ex)
			{
				std::cout << ex.what() << std::endl;
			}
			std::cout << std::endl << ">> ";
		}
		menu.DoCommand("INFO");
	}
	catch (const std::exception & ex)
	{
		std::cerr << ex.what() << std::endl;
		return -1;
	}
	return 0;
}
