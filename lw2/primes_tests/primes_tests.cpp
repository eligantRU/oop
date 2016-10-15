#include "stdafx.h"

#include "../primes/primes_utils.h"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(primes_count)
{
	{
		const auto expectedResult = 0;
		auto primes = GeneratePrimeNumbersSet(0);
		BOOST_CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 0;
		auto primes = GeneratePrimeNumbersSet(1);
		BOOST_CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 1;
		auto primes = GeneratePrimeNumbersSet(2);
		BOOST_CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 2;
		auto primes = GeneratePrimeNumbersSet(3);
		BOOST_CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 4;
		auto primes = GeneratePrimeNumbersSet(10);
		BOOST_CHECK(primes.size() == expectedResult);
	}

	{
		const auto expectedResult = 5'761'455;
		auto primes = GeneratePrimeNumbersSet(100'000'000);
		BOOST_CHECK(primes.size() == expectedResult);
	}
}

BOOST_AUTO_TEST_CASE(compare_sets)
{
	{
		const std::set<uint32_t> expectedResult = { 
			2, 3, 5, 7 
		};
		const auto primes = GeneratePrimeNumbersSet(10);
		BOOST_CHECK(primes == expectedResult);
	}

	{
		const std::set<uint32_t> expectedResult = { 
			2, 3, 5, 7, 11 
		};
		const auto primes = GeneratePrimeNumbersSet(12);
		BOOST_CHECK(primes == expectedResult);
	}

	{
		const std::set<uint32_t> expectedResult = {	2 };
		const auto primes = GeneratePrimeNumbersSet(2);
		BOOST_CHECK(primes == expectedResult);
	}

	{
		const std::set<uint32_t> expectedResult = { };
		const auto primes = GeneratePrimeNumbersSet(1);
		BOOST_CHECK(primes == expectedResult);
	}
}

BOOST_AUTO_TEST_SUITE_END()
