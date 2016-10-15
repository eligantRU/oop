#pragma once

#include "stdafx.h"

bool IsNumber(const std::string & str);
std::set<uint32_t> GeneratePrimeNumbersSet(const unsigned upperBound);

/*bool IsNumber(const std::string & str)
{
	return std::all_of(str.begin(), str.end(), std::isdigit);
}

std::set<uint32_t> GeneratePrimeNumbersSet(const unsigned upperBound)
{
	std::vector<bool> nums(upperBound + 1, true);

	for (unsigned i = 2; i * i <= upperBound; ++i)
	{
		if (nums[i])
		{
			for (unsigned j = i * i; j <= upperBound; j += i)
			{
				nums[j] = false;
			}
		}
	}

	std::set<uint32_t> primes;
	if (upperBound >= 2)
	{
		primes.insert(2);
	}
	for (unsigned i = 3; i <= upperBound; i += 2)
	{
		if (nums[i])
		{
			primes.emplace_hint(primes.end(), i);
		}
	}
	return primes;
}*/
