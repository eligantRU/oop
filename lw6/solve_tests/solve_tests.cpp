#include "stdafx.h"

#include "../solve/solve_utils.h"

namespace
{

static const auto eps = 10e-6;

void VerifyArray(const std::array<double, 3> & lhs, const std::array<double, 3> & rhs)
{
	for (auto i = 0; i < 3; ++i)
	{
		if (!(isnan(lhs[i]) && isnan(rhs[i])))
		{
			BOOST_REQUIRE_CLOSE_FRACTION(lhs[i], rhs[i], eps);
		}
	}
}

}

BOOST_AUTO_TEST_SUITE(Solve3_)

	BOOST_AUTO_TEST_CASE(leading_coefficient_cannot_be_zero)
	{
		BOOST_REQUIRE_THROW(Solve3(0, 1, 1, 1), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(work_on_3_real_root)
	{
		{
			const auto roots = Solve3(-18, +365, -989, -238);
			const std::array<double, 3> expectedRoots = { 
				-2.0 / 9, +3.5, +17
			};
			const unsigned expectedRootsNumber = 3;
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const auto roots = Solve3(+1, +418, -658'365, -102'635'694);
			const std::array<double, 3> expectedRoots = { 
				-982, -147, +711
			};
			const unsigned expectedRootsNumber = 3;
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const auto roots = Solve3(+1, +2, -5, -6);
			const std::array<double, 3> expectedRoots = {
				-3, -1, 2
			};
			const unsigned expectedRootsNumber = 3;
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}
	}

	BOOST_AUTO_TEST_CASE(work_on_2_real_root)
	{
		{
			const auto roots = Solve3(+49, -1'911, +24'696, -105'644);
			const std::array<double, 3> expectedRoots = {
				+11, +14, NAN
			};
			const unsigned expectedRootsNumber = 2;
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const auto roots = Solve3(+1, -9, +24, -16);
			const std::array<double, 3> expectedRoots = {
				+1, +4, NAN
			};
			const unsigned expectedRootsNumber = 2;
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}
	}

	BOOST_AUTO_TEST_CASE(work_on_1_real_root)
	{
		{
			const auto roots = Solve3(+1, +160, -150, +1000.587);
			const std::array<double, 3> expectedRoots = {
				-160.97, NAN, NAN
			};
			const unsigned expectedRootsNumber = 1;
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}

		{
			const auto roots = Solve3(+17, -14, +25.7, -600'000'000);
			const std::array<double, 3> expectedRoots = {
				328.293585440745, NAN, NAN
			};
			const unsigned expectedRootsNumber = 1;
			BOOST_CHECK_EQUAL(roots.numRoots, expectedRootsNumber);
			VerifyArray(roots.roots, expectedRoots);
		}
	}

BOOST_AUTO_TEST_SUITE_END()
