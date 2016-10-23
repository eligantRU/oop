#include "stdafx.h"

namespace
{

std::string FindAndReplace(const std::string & inputStr, const std::string & searchStr, const std::string & replaceStr)
{
	std::string result;
	result.reserve(inputStr.size());

	size_t initialPos = 0;
	for (size_t pos; (pos = inputStr.find(searchStr, initialPos)) != std::string::npos; initialPos = pos + searchStr.length())
	{
		result.append(inputStr, initialPos, pos - initialPos);
		result.append(replaceStr);
	}
	result.append(inputStr, initialPos);
	return result;
}

void Replace(const std::string & inputFilePath, const std::string & outputFilePath, const std::string & searchStr, const std::string & replaceStr)
{
	std::ifstream input(inputFilePath);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFilePath + " for reading");
	}

	std::ofstream output(outputFilePath);
	if (!output.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFilePath + " for writing");
	}

	std::string currentStr;
	while (std::getline(input, currentStr))
	{
		currentStr = FindAndReplace(currentStr, searchStr, replaceStr);
		output << currentStr << std::endl;
	}

	if (!output.flush())
	{
		throw std::runtime_error("Failed to save data on disk");
	}
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
