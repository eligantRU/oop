#include "stdafx.h"

#include "../vector/vector_utils.h"

namespace
{

const auto inf = std::numeric_limits<double>::infinity();

void ExpectEqualVectors(const std::vector<double> & lhs, const std::vector<double> & rhs)
{
	BOOST_REQUIRE_EQUAL(lhs.size(), rhs.size());
	BOOST_REQUIRE(equal(lhs.begin(), lhs.end(), rhs.begin(), [](auto x, auto y) {
		return x == y || (isnan(x) && isnan(y));
	}));
}

}

BOOST_AUTO_TEST_SUITE(Vector)

	BOOST_AUTO_TEST_SUITE(Get_nums)

		BOOST_AUTO_TEST_CASE(can_get_double_nums_from_istream)
		{
			{
				std::stringstream str("3 4 2 0 1 5");
				auto nums = GetNums(str);
				const std::vector<double> correctVec = {
					3, 4, 2, 0, 1, 5
				};
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::stringstream str("5.7 0.5 1.25 3.75 4.8 2.5");
				auto nums = GetNums(str);
				const std::vector<double> correctVec = {
					5.7, 0.5, 1.25, 3.75, 4.8, 2.5
				};
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::stringstream str("");
				auto nums = GetNums(str);
				const std::vector<double> correctVec = {};
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::stringstream str("0 1 2 3 4 5 abcd efg");
				auto nums = GetNums(str);
				const std::vector<double> correctVec = {
					0, 1, 2, 3, 4, 5
				};
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::stringstream str("0 1 2 3 4 5 abcd efg 6 7 8 9");
				auto nums = GetNums(str);
				const std::vector<double> correctVec = {
					0, 1, 2, 3, 4, 5
				};
				ExpectEqualVectors(nums, correctVec);
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Division)

		BOOST_AUTO_TEST_CASE(can_div_vector_of_double_on_double)
		{
			{
				std::vector<double> nums = {
					5, 4, 3, 2, 1, 0
				};
				const std::vector<double> correctVec = {
					2.5, 2, 1.5, 1, 0.5, 0
				};
				Div(nums, 2);
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::vector<double> nums = {
					0, 1, 2, 3, 4, 5
				};
				const std::vector<double> correctVec = {
					0, 1, 2, 3, 4, 5
				};
				Div(nums, 1);
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::vector<double> nums = {
					5.7, 0.5, 1.25, 3.75, 4.8, 2.5
				};
				const std::vector<double> correctVec = {
					11.4, 1, 2.5, 7.5, 9.6, 5
				};
				Div(nums, 0.5);
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::vector<double> nums = {
					-1, 0
				};
				const std::vector<double> correctVec = {
					-inf, NAN
				};
				Div(nums, 0);
				ExpectEqualVectors(nums, correctVec);
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Process_vector)
	
		BOOST_AUTO_TEST_CASE(can_modified_vector_by_the_division_on_the_half_of_greatest_num)
		{
			{
				std::vector<double> nums = {
					4, 2, 0, 1, 3
				};
				ProcessVector(nums);
				const std::vector<double> correctVec = {
					2, 1, 0, 0.5, 1.5
				};
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::vector<double> nums = { };
				ProcessVector(nums);
				const std::vector<double> correctVec = { };
				ExpectEqualVectors(nums, correctVec);
			}

			{
				std::vector<double> nums = {
					-1, 0
				};
				const std::vector<double> correctVec = {
					-inf, NAN
				};
				ProcessVector(nums);
				ExpectEqualVectors(nums, correctVec);
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(Print_vector)

		BOOST_AUTO_TEST_CASE(can_print_vector_of_double_to_ostream)
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

			{
				std::stringstream buffer;
				std::vector<double> nums = {};
				PrintVector(buffer, nums, 3);
				std::string str;
				std::getline(buffer, str);
				BOOST_CHECK(str.empty());
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
