#pragma once

#include "stdafx.h"

namespace
{

std::set<uint32_t> GeneratePrimeNumbersSet(unsigned upperBound)
{
	++(++upperBound);
	std::vector<bool> nums;
	nums.reserve(upperBound);
	for (unsigned i = 2; i < upperBound; ++i)
	{
		nums.push_back(true);
	}

	for (unsigned i = 2; i < sqrt(upperBound); ++i)
	{
		for (unsigned j = 2 * i; j <= upperBound; j += i)
		{
			nums[j] = false;
		}
	}

	std::set<uint32_t> primes;
	for (unsigned i = 2; i < upperBound; ++i)
	{
		if (nums[i])
		{
			primes.insert(i);
		}
	}
	return primes;
}

}
