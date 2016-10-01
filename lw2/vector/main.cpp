#include "stdafx.h"

namespace
{

template <typename T>
void PrintVector(std::ostream & output, const std::vector<T> & vec, unsigned precision = 3)
{
	for (const auto element : vec)
	{
		output << std::fixed << std::setprecision(precision) << element << " ";
	}
	output << std::endl;
}

template <typename Type, class T>
void PrintSortedVector(std::ostream & output, const std::vector<Type> & vec, const T & sortFn, unsigned precision = 3)
{
	auto vecSorted = vec;
	std::sort(vecSorted.begin(), vecSorted.end(), sortFn);
	PrintVector(output, vecSorted, precision);
}

std::vector<std::string> SplitString(const std::string & strToSplit) // TODO: use boost/algorithm/string/split.hpp
{
	std::string buf; 
	std::stringstream ss(strToSplit);

	std::vector<std::string> lexems;

	while (ss >> buf)
	{
		lexems.push_back(buf);
	}
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

}

int main(int, char * [])
{
	auto nums = GetNums(std::cin);
	auto divider = *std::max_element(nums.begin(), nums.end()) / 2; // NOTE: potentially unsafe code
	for (auto & element : nums)
	{
		element /= divider;
	}
	PrintSortedVector(std::cout, nums, [](double a, double b) {
		return a < b;
	});

    return 0;
}
