#include "stdafx.h"

#include "../findMaxEx/findMaxEx_utils.hpp"

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

SAthlete Tigress = { "Master Tigress", 220.5, 100.50 };
SAthlete Monkey = { "Master Monkey ", 150.8, 78.42 };
SAthlete Mantis = { "Master Mantis", 18.5, 0.85 };
SAthlete Crane = { "Master Crane", 180.0, 50.20 };
SAthlete Viper = { "Master Viper", 250.5, 42.05 };
SAthlete Po = { "Dragon Warrior", 187.96, 118.00 };

const std::vector<SAthlete> athletes = { Tigress, Monkey, Mantis, Crane, Viper, Po };

void IsAthleteEqual(const SAthlete & lhs, const SAthlete & rhs)
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
			BOOST_CHECK(!FindMax({ }, max, [](const auto lhs, const auto rhs) {
				return (lhs < rhs);
			}));
			BOOST_CHECK(isnan(max));
		}

		{
			auto lessAthlete = Tigress;
			BOOST_CHECK(!FindMax({ }, lessAthlete, IsLessWeight));
			IsAthleteEqual(lessAthlete, Tigress);
		}

		{
			auto lessAthlete = Po;
			BOOST_CHECK(!FindMax({ }, lessAthlete, IsLessHeight));
			IsAthleteEqual(lessAthlete, Po);
		}
	}

	BOOST_AUTO_TEST_CASE(return_max_element_in_nonempty_vector)
	{
		{
			int max;
			BOOST_CHECK(FindMax({ 16, 9, 11, 3, 17, 4, 0 }, max, [](const auto lhs, const auto rhs) {
				return (lhs < rhs);
			}));
			BOOST_CHECK_EQUAL(max, 17);
		}

		{
			SAthlete theWeightestAthlete;
			BOOST_CHECK(FindMax(athletes, theWeightestAthlete, IsLessWeight));
			IsAthleteEqual(theWeightestAthlete, Po);
		}

		{
			SAthlete theHeightestAthlete;
			BOOST_CHECK(FindMax(athletes, theHeightestAthlete, IsLessHeight));
			IsAthleteEqual(theHeightestAthlete, Viper);
		}
	}

BOOST_AUTO_TEST_SUITE_END()
