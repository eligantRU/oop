#include "stdafx.h"

#include "../findMaxEx/findMaxEx_utils.h"

namespace
{

struct SAthlete
{
	std::string name;
	double height;
	double weight;
};

bool IsLessWeight(const SAthlete & lhs, const SAthlete & rhs)
{
	return (lhs.weight < rhs.weight);
}

bool IsLessHeight(const SAthlete & lhs, const SAthlete & rhs)
{
	return (lhs.height < rhs.height);
}

const SAthlete Tigress = { "Master Tigress", 220.5, 100.50 };
const SAthlete Monkey = { "Master Monkey ", 150.8, 78.42 };
const SAthlete Mantis = { "Master Mantis", 18.5, 0.85 };
const SAthlete Crane = { "Master Crane", 180.0, 50.20 };
const SAthlete Viper = { "Master Viper", 250.5, 42.05 };
const SAthlete Po = { "Dragon Warrior", 187.96, 118.00 };

const std::vector<SAthlete> athletes = { Tigress, Monkey, Mantis, Crane, Viper, Po };

void VerifyAthlete(const SAthlete & lhs, const SAthlete & rhs)
{
	BOOST_CHECK_EQUAL(lhs.name, rhs.name);
	BOOST_CHECK_EQUAL(lhs.height, rhs.height);
	BOOST_CHECK_EQUAL(lhs.weight, rhs.weight);
}

}

BOOST_AUTO_TEST_SUITE(FindMax_)

	BOOST_AUTO_TEST_CASE(cannot_find_in_empty_vector)
	{
		{
			float max = NAN;
			BOOST_CHECK(!FindMax({}, max));
			BOOST_CHECK(isnan(max));
		}

		{
			float max = NAN;
			BOOST_CHECK(!FindMax({ }, max, [](const auto lhs, const auto rhs) {
				return (lhs < rhs);
			}));
			BOOST_CHECK(isnan(max));
		}

		{
			auto lessAthlete = Tigress;
			BOOST_CHECK(!FindMax({ }, lessAthlete, IsLessWeight));
			VerifyAthlete(lessAthlete, Tigress);
		}

		{
			auto lessAthlete = Po;
			BOOST_CHECK(!FindMax({ }, lessAthlete, IsLessHeight));
			VerifyAthlete(lessAthlete, Po);
		}

		{
			auto lessAthlete = Po;
			BOOST_CHECK(!FindMax({}, lessAthlete, IsLessHeight));
			VerifyAthlete(lessAthlete, Po);
		}
	}

	BOOST_AUTO_TEST_CASE(return_max_element_in_nonempty_vector)
	{
		{
			int max;
			BOOST_CHECK(FindMax({ -16, -9, -11, -3, -17, -4 }, max));
			BOOST_CHECK_EQUAL(max, -3);
		}

		{
			int max;
			BOOST_CHECK(FindMax({ -16, -9, -11, -3, -17, -4 }, max, [](const auto lhs, const auto rhs) {
				return (lhs < rhs);
			}));
			BOOST_CHECK_EQUAL(max, -3);
		}

		{
			SAthlete theWeightestAthlete;
			BOOST_CHECK(FindMax(athletes, theWeightestAthlete, IsLessWeight));
			VerifyAthlete(theWeightestAthlete, Po);
		}

		{
			SAthlete theHeightestAthlete;
			BOOST_CHECK(FindMax(athletes, theHeightestAthlete, IsLessHeight));
			VerifyAthlete(theHeightestAthlete, Viper);
		}
	}

BOOST_AUTO_TEST_SUITE_END()
