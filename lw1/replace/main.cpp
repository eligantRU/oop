#include "stdafx.h"

namespace
{

std::string FindAndReplace(const std::string & inputStr, const std::string & searchStr, const std::string & replaceStr)
{
	auto currentStr = inputStr;

	auto pos = currentStr.find(searchStr);
	while (pos != std::string::npos)
	{
		currentStr.replace(pos, searchStr.length(), replaceStr);
		pos = currentStr.find(searchStr, pos + replaceStr.length());
	}
	return currentStr;
}

}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "replace.exe <input file> <output file> <search string> <replace string>" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[1] << " for reading" << std::endl; 
		return 1;
	}

	std::ofstream output(argv[2]);
	if (!output.is_open())
	{
		std::cerr << "Failed to open " << argv[2] << " for writing" << std::endl;
		return 1;
	}

	const std::string searchStr = argv[3];
	const std::string replaceStr = argv[4];
	if (searchStr.empty())
	{
		std::cerr << "<search string> must be not empty" << std::endl;
		return 1;
	}

	std::string currentStr;
	while (std::getline(input, currentStr))
	{
		currentStr = FindAndReplace(currentStr, searchStr, replaceStr);
		output << currentStr << std::endl;
	}

	if (!output.flush())
	{
		std::cerr << "Failed to save data on disk" << std::endl;
		return 1;
	}
	return 0;
}
