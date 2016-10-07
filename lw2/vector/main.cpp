#include "stdafx.h"
#include "vector_utils.h"

int main(int, char * [])
{
	auto nums = GetNums(std::cin);
	auto divider = GetMax(nums) / 2;
	Div(nums, divider);
	SortVector(nums, [](double a, double b) {
		return a < b;
	});
	PrintVector(std::cout, nums, 3);

    return 0;
}
