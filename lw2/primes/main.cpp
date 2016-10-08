#include "stdafx.h"

#include "primes_utils.h"

int main(int, char * [])
{
	double start = GetTickCount();

	auto primes = GeneratePrimeNumbersSet(100'000'000);

	for (const auto num : primes)
	{
		// std::cout << num << std::endl;
	}

	double end = GetTickCount();
	std::cerr << "Runtime: " << end - start << std::endl;
	return 0;
}
