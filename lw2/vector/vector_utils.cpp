#include "stdafx.h"

#include "vector_utils.h"

void PrintVector(std::ostream & output, const std::vector<double> & vec, unsigned precision)
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

void Div(std::vector<double> & vec, const double divider)
{
	for (auto & element : vec)
	{
		element /= divider;
	}
}

void ProcessVector(std::vector<double> & vec)
{
	if (vec.empty())
	{
		return;
	}

	auto divider = *std::max_element(vec.begin(), vec.end()) / 2;
	std::transform(vec.begin(), vec.end(), vec.begin(), [=](double element) {
		return element / divider;
	});
}
