#pragma once

#include "stdafx.h"

namespace
{

template <typename T>
void PrintVector(std::ostream & output, const std::vector<T> & vec, unsigned precision = 3)
{
	for (const auto & element : vec)
	{
		output << std::fixed << std::setprecision(precision) << element << " ";
	}
	output << std::endl;
}

std::vector<std::string> SplitString(const std::string & strToSplit)
{
	std::vector<std::string> lexems;
	boost::split(lexems, strToSplit, boost::is_any_of(" "));
	return lexems;
}

std::vector<double> GetNums(std::istream & input)
{
	std::vector<double> result;

	std::string inputStr;
	std::getline(input, inputStr);

	auto lexems = SplitString(inputStr);
	for (const auto lexem : lexems)
	{
		result.push_back(stod(lexem)); // NOTE: potentially unsafe code
	}

	return result;
}

template <typename Type>
Type GetMax(const std::vector<Type> & vec) // NOTE: potentially unsafe code
{
	return *std::max_element(vec.begin(), vec.end());
}

template <typename Type>
void Div(std::vector<Type> & vec, const double divider) // NOTE: operator/
{
	for (auto & element : vec)
	{
		element /= divider;
	}
}

template <typename Type>
void ProcessVector(std::vector<Type> & vec)
{
	auto divider = GetMax(vec) / 2;
	std::transform(vec.begin(), vec.end(), vec.begin() /*std::back_inserter(vec)*/, [=](double element) -> double {
		return element / divider;
	});
}

}
