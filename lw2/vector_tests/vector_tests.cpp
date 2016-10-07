#include "stdafx.h"

#include "../vector/vector_utils.h"

template <typename Type>
bool Compare(const std::vector<Type> & vec1, const std::vector<Type> & vec2)
{
	if (vec1.size() != vec2.size())
	{
		return false;
	}
	for (unsigned i = 0; i < vec1.size(); ++i)
	{
		if (vec1[i] != vec2[i])
		{
			return false;
		}
	}
	return true;
}

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(GettingNums)
{
	{
		std::stringstream str("5 4 3 2 1 0");
		auto nums = GetNums(str);
		BOOST_CHECK(Compare(nums, { 5, 4, 3, 2, 1, 0 }));
	}

	{
		std::stringstream str("0 1 2 3 4 5");
		auto nums = GetNums(str);
		BOOST_CHECK(Compare(nums, { 0, 1, 2, 3, 4, 5 }));
	}

	{
		std::stringstream str("5.7 0.5 1.25 3.75 4.8 2.5");
		auto nums = GetNums(str);
		BOOST_CHECK(Compare(nums, { 5.7, 0.5, 1.25, 3.75, 4.8, 2.5 }));
	}
}

BOOST_AUTO_TEST_CASE(GettingMax)
{
	{
		const std::vector<double> nums = {
			5, 4, 3, 2, 1, 0
		};
		BOOST_CHECK(GetMax(nums) == 5);
	}

	{
		const std::vector<double> nums = {
			0, 1, 2, 3, 4, 5
		};
		BOOST_CHECK(GetMax(nums) == 5);
	}

	{
		const std::vector<double> nums = {
			0, 3, 2, 1, 5, 4
		};
		BOOST_CHECK(GetMax(nums) == 5);
	}

	{
		const std::vector<double> nums = {
			5.7, 0.5, 1.25, 3.75, 4.8, 2.5
		};
		BOOST_CHECK(GetMax(nums) == 5.7);
	}
}

BOOST_AUTO_TEST_CASE(Division)
{
	{
		std::vector<double> nums = {
			5, 4, 3, 2, 1, 0
		};
		Div(nums, 2);
		BOOST_CHECK(Compare(nums, { 2.5, 2, 1.5, 1, 0.5, 0 }));
	}

	{
		std::vector<double> nums = {
			0, 1, 2, 3, 4, 5
		};
		Div(nums, 1);
		BOOST_CHECK(Compare(nums, { 0, 1, 2, 3, 4, 5 }));
	}

	{
		std::vector<double> nums = {
			5.7, 0.5, 1.25, 3.75, 4.8, 2.5
		};
		Div(nums, 0.5);
		BOOST_CHECK(Compare(nums, { 11.4, 1, 2.5, 7.5, 9.6, 5 }));
	}
}

BOOST_AUTO_TEST_CASE(SortingVector)
{
	{
		std::vector<double> nums = {
			0, 1, 2, 3, 4, 5
		};
		SortVector(nums, [](double a, double b) {
			return a < b;
		});
		BOOST_CHECK(Compare(nums, { 0, 1, 2, 3, 4, 5 }));
	}

	{
		std::vector<double> nums = {
			5, 4, 3, 2, 1, 0
		};
		SortVector(nums, [](double a, double b) {
			return a < b;
		});
		BOOST_CHECK(Compare(nums, { 0, 1, 2, 3, 4, 5 }));
	}

	{
		std::vector<double> nums = {
			3, 4, 1, 2, 5, 0
		};
		SortVector(nums, [](double a, double b) {
			return a < b;
		});
		BOOST_CHECK(Compare(nums, { 0, 1, 2, 3, 4, 5 }));
	}
}

BOOST_AUTO_TEST_CASE(PrintingVector)
{
	{
		std::stringstream buffer; 
		std::vector<double> nums = {
			0, 1, 2, 3, 4, 5
		};
		PrintVector(buffer, nums, 3);
		std::string str;
		std::getline(buffer, str);
		BOOST_CHECK(str == "0.000 1.000 2.000 3.000 4.000 5.000 ");
	}

	{
		std::stringstream buffer;
		std::vector<double> nums = {
			0, 1, 2, 3, 4, 5
		};
		PrintVector(buffer, nums, 2);
		std::string str;
		std::getline(buffer, str);
		BOOST_CHECK(str == "0.00 1.00 2.00 3.00 4.00 5.00 ");
	}

	{
		std::stringstream buffer;
		std::vector<double> nums = {
			0.001, 1.089, 2.016, 3.014, 4.090, 5.096
		};
		PrintVector(buffer, nums, 2);
		std::string str;
		std::getline(buffer, str);
		BOOST_CHECK(str == "0.00 1.09 2.02 3.01 4.09 5.10 ");
	}
}

BOOST_AUTO_TEST_SUITE_END()
