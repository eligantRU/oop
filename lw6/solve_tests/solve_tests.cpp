#include "stdafx.h"

#include "../solve/solve_utils.h"

namespace
{

static const auto eps = 10e-6;

template <class T>
void VerifyArray(const T & lhs, const T & rhs)
{
	BOOST_REQUIRE_EQUAL(lhs.size(), rhs.size());
	for (auto i = 0; i < lhs.size(); ++i)
	{
		if (!(isnan(lhs[i]) && isnan(rhs[i])))
		{
			BOOST_REQUIRE_CLOSE_FRACTION(lhs[i], rhs[i], eps);
		}
	}
}

}

BOOST_AUTO_TEST_SUITE(Solve2_)

	BOOST_AUTO_TEST_CASE(leading_coefficient_cannot_be_zero)
	{
		BOOST_REQUIRE_THROW(Solve2(0, +1, +1), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(work_on_no_real_roots)
	{
		BOOST_REQUIRE_THROW(Solve2(+17, -146, +327), std::domain_error);
	}

	BOOST_AUTO_TEST_CASE(work_on_2_real_roots)
	{
		{
			const unsigned expectedRootsNumber = 2;
			const std::array<double, 2> expectedRoots = {
				-0.25, +1
			};
			const auto roots = Solve2(+4, -3, -1);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const unsigned expectedRootsNumber = 2;
			const std::array<double, 2> expectedRoots = {
				0, 16.0 / 17
			};
			const auto roots = Solve2(+17, -16, 0);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}
	}

	BOOST_AUTO_TEST_CASE(work_on_1_real_root)
	{
		{
			const unsigned expectedRootsNumber = 1;
			const std::array<double, 2> expectedRoots = {
				-1, NAN
			};
			const auto roots = Solve2(-2, -4, -2);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const unsigned expectedRootsNumber = 1;
			const std::array<double, 2> expectedRoots = {
				0, NAN
			};
			const auto roots = Solve2(+4, 0, 0);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}
	}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Solve3_)

	BOOST_AUTO_TEST_CASE(leading_coefficient_cannot_be_zero)
	{
		BOOST_REQUIRE_THROW(Solve3(0, 1, 1, 1), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(work_on_3_real_roots)
	{
		{
			const unsigned expectedRootsNumber = 3;
			const std::array<double, 3> expectedRoots = { 
				-2.0 / 9, +3.5, +17
			};
			const auto roots = Solve3(-18, +365, -989, -238);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const unsigned expectedRootsNumber = 3;
			const std::array<double, 3> expectedRoots = { 
				-982, -147, +711
			};
			const auto roots = Solve3(+1, +418, -658'365, -102'635'694);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const unsigned expectedRootsNumber = 3;
			const std::array<double, 3> expectedRoots = {
				-3, -1, 2
			};
			const auto roots = Solve3(+1, +2, -5, -6);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}
	}

	BOOST_AUTO_TEST_CASE(work_on_2_real_roots)
	{
		{
			const unsigned expectedRootsNumber = 2;
			const std::array<double, 3> expectedRoots = {
				+11, +14, NAN
			};
			const auto roots = Solve3(+49, -1'911, +24'696, -105'644);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const unsigned expectedRootsNumber = 2;
			const std::array<double, 3> expectedRoots = {
				+1, +4, NAN
			};
			const auto roots = Solve3(+1, -9, +24, -16);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}
	}

	BOOST_AUTO_TEST_CASE(work_on_1_real_root)
	{
		{
			const unsigned expectedRootsNumber = 1;
			const std::array<double, 3> expectedRoots = {
				-160.97, NAN, NAN
			};
			const auto roots = Solve3(+1, +160, -150, +1'000.587);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const unsigned expectedRootsNumber = 1;
			const std::array<double, 3> expectedRoots = {
				328.293585440745, NAN, NAN
			};
			const auto roots = Solve3(+17, -14, +25.7, -600'000'000);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const unsigned expectedRootsNumber = 1;
			const std::array<double, 3> expectedRoots = {
				-1, NAN, NAN
			};
			const auto roots = Solve3(+3, +3, +1, +1);
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}
	}

BOOST_AUTO_TEST_SUITE_END()
