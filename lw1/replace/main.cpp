#include "stdafx.h"

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "replace.exe <input file> <output file> <search string> <replace string>" << std::endl;
		std::exit(1);
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[1] << " for reading" << std::endl;
		std::exit(2);
	}

	std::ofstream output(argv[2]);
	if (!output.is_open())
	{
		std::cerr << "Failed to open " << argv[2] << " for writing" << std::endl;
		std::exit(3);
	}

	const std::string searchStr = argv[3];
	const std::string replaceStr = argv[4];
	if (searchStr.empty())
	{
		std::cerr << "<search string> must be not empty" << std::endl;
		std::exit(4);
	}

	std::string currentStr = "";
	while (std::getline(input, currentStr))
	{
		int it = currentStr.find(searchStr);
		while (it != std::string::npos)
		{
			output << currentStr.substr(0, it) << replaceStr;
			currentStr = currentStr.substr(it + searchStr.length(), currentStr.length());
			it = currentStr.find(searchStr);
		}
		output << currentStr << std::endl;
	}

	if (!output.flush())
	{
		std::cerr << "Failed to save data on disk" << std::endl;
		std::exit(5);
	}
	return 0;
}
