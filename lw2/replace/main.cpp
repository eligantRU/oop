#include "stdafx.h"

#include "replace_utils.h"

int main(int argc, char * argv[])
{
	if (argc != 3)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "replace.exe <search string> <replace string>" << std::endl;
		return 1;
	}
	const std::string searchStr = argv[1];
	const std::string replaceStr = argv[2];

	try
	{
		Replace(std::cin, std::cout, searchStr, replaceStr);
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
		return 1;
	}
	return 0;
}
