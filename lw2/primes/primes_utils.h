#pragma once

#include "stdafx.h"

namespace
{

bool IsNumber(const std::string & str)
{
	return std::all_of(str.begin(), str.end(), std::isdigit);
}

std::set<uint32_t> GeneratePrimeNumbersSet(const unsigned upperBound)
{
	std::vector<bool> nums(upperBound, true);

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
