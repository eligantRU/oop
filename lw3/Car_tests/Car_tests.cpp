#include "stdafx.h"
#include "../Car/Car.h"
#include "../Car/Car.cpp"

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Test, CarFixture)

	BOOST_AUTO_TEST_CASE(is_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsEngineTurnOn());
	}
	
	BOOST_AUTO_TEST_CASE(cannot_select_gear_when_engine_turned_off)
	{
		{
			BOOST_CHECK(!car.IsEngineTurnOn());
			BOOST_CHECK(car.SetGear(0));
			BOOST_CHECK(car.GetGear() == 0);
		}

		{
			BOOST_CHECK(!car.IsEngineTurnOn());
			BOOST_CHECK(!car.SetGear(1));
			BOOST_CHECK(car.GetGear() == 0);
		}

		{
			BOOST_CHECK(!car.IsEngineTurnOn());
			BOOST_CHECK(!car.SetGear(-1));
			BOOST_CHECK(car.GetGear() == 0);
		}
	}

	BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
	{
		{
			car.TurnOnEngine();
			BOOST_CHECK(car.IsEngineTurnOn());
		}

		{
			car.TurnOnEngine();
			BOOST_CHECK(!car.TurnOnEngine());
			BOOST_CHECK(car.IsEngineTurnOn());
		}
	}

	struct when_engine_turned_on_ : CarFixture
	{
		when_engine_turned_on_()
		{
			car.TurnOnEngine();
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_engine_turned_on, when_engine_turned_on_)
		
		BOOST_AUTO_TEST_CASE(engine_can_be_turned_off)
		{
			{
				car.TurnOffEngine();
				BOOST_CHECK(!car.IsEngineTurnOn());
			}

			{
				car.TurnOffEngine();
				BOOST_CHECK(!car.TurnOffEngine());
				BOOST_CHECK(!car.IsEngineTurnOn());
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
