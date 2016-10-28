#include "stdafx.h"

#include "replace_utils.h"

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
