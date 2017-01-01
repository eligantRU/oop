#include "stdafx.h"

#include "vector_utils.h"

int main(int, char * [])
{
	auto nums = GetNums(std::cin);
	ProcessVector(nums);
	std::sort(nums.begin(), nums.end());
	PrintVector(std::cout, nums, 3);

	return 0;
}
