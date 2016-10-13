#pragma once

#include "stdafx.h"

namespace
{

std::string FindAndReplace(const std::string & inputStr, const std::string & searchStr, const std::string & replaceStr)
{
	std::string result;
	result.reserve(inputStr.size());

	size_t initialPos = 0;
	for (auto pos = inputStr.find(searchStr); pos != std::string::npos; pos = inputStr.find(searchStr, initialPos))
	{
		result.append(inputStr, initialPos, pos - initialPos);
		result.append(replaceStr);
		initialPos = pos + searchStr.length();
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
