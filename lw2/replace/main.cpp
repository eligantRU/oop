#include "stdafx.h"

#include "replace_utils.h"

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "replace.exe <input file> <output file> <search string> <replace string>" << std::endl;
		return 1;
	}
	const std::string inputFilePath = argv[1];
	const std::string outputFilePath = argv[2];
	const std::string searchStr = argv[3];
	const std::string replaceStr = argv[4];
	if (searchStr.empty())
	{
		std::cerr << "<search string> must be not empty" << std::endl;
		return 1;
	}

	try
	{
		Replace(inputFilePath, outputFilePath, searchStr, replaceStr);
	}
	catch (const std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
		return 1;
	}
	return 0;
}
