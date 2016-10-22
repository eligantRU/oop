#pragma once

#include "stdafx.h"

template <typename T>
void PrintVector(std::ostream & output, const std::vector<T> & vec, unsigned precision = 3)
{
	for (const auto & element : vec)
	{
		output << std::fixed << std::setprecision(precision) << element << " ";
	}
	output << std::endl;
}

std::vector<double> GetNums(std::istream & input)
{
	return {
		std::istream_iterator<double>(input), std::istream_iterator<double>()
	};
}

template <typename Type>
Type GetMax(const std::vector<Type> & vec)
{
	return *std::max_element(vec.begin(), vec.end());
}

template <typename Type>
void Div(std::vector<Type> & vec, const double divider)
{
	for (auto & element : vec)
	{
		element /= divider;
	}
}

template <typename Type>
void ProcessVector(std::vector<Type> & vec)
{
	if (vec.empty())
	{
		return;
	}

	auto divider = GetMax(vec) / 2;
	std::transform(vec.begin(), vec.end(), vec.begin(), [=](double element) {
		return element / divider;
	});
}
