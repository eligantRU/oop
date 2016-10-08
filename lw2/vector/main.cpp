#include "stdafx.h"
#include "vector_utils.h"

int main(int, char * [])
{
	auto nums = GetNums(std::cin);
	ProcessVector(nums);
	std::sort(nums.begin(), nums.end(), [](double a, double b) {
		return a < b;
	});
	PrintVector(std::cout, nums);

    return 0;
}
