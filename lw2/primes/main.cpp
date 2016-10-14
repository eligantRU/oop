#include "stdafx.h"

#include "primes_utils.h"

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "prime.exe <upperBound>" << std::endl;
		return 1;
	}

	const std::string upperBound = argv[1];
	if (!IsNumber(upperBound))
	{
		std::cerr << "<upperBound> must be unsigned integer" << std::endl;
		return 1;
	}

	auto primes = GeneratePrimeNumbersSet(atoi(upperBound.c_str()));

	return 0;
}
