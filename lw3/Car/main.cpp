#include "stdafx.h"

#include "Car.h"
#include "CarMenu.h"

int main(int, char * [])
{
	CCar car;
	CCarMenu carMenu(car);

	std::string commandLine;
	std::cout << std::endl << ">>";
	while (std::getline(std::cin, commandLine))
	{
		carMenu.DoCommand(commandLine);
		std::cout << std::endl << ">>";
	}
    return 0;
}
