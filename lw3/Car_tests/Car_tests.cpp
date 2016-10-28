#include "stdafx.h"

#include "../Car/Car.h"
#include "../Car/Car.cpp"

struct CarFixture
{
	CCar car;
};

BOOST_FIXTURE_TEST_SUITE(Test, CarFixture)

	BOOST_AUTO_TEST_CASE(is_engine_turned_off_by_default)
	{
		BOOST_CHECK(!car.IsEngineTurnOn());
	}

	BOOST_AUTO_TEST_CASE(is_speed_is_zero_by_default)
	{
		BOOST_CHECK(car.GetSpeed() == 0);
	}

	BOOST_AUTO_TEST_CASE(is_direction_is_stop_by_default)
	{
		BOOST_CHECK(car.GetDirection() == Direction::Stop);
	}

	BOOST_AUTO_TEST_CASE(can_select_neutral_gear_when_engine_turned_off)
	{
		{
			BOOST_CHECK(car.SetGear(Gear::Neutral));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
		}
	}

	BOOST_AUTO_TEST_CASE(cannot_select_others_gear_when_engine_turned_off)
	{
		{
			BOOST_CHECK(car.SetGear(Gear::Neutral));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
		}

		{
			BOOST_CHECK(!car.SetGear(Gear::First));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
		}

		{
			BOOST_CHECK(!car.SetGear(Gear::Reverse));
			BOOST_CHECK(car.GetGear() == Gear::Neutral);
		}
	}

	BOOST_AUTO_TEST_CASE(engine_can_be_turned_on)
	{
		{
			car.TurnOnEngine();
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

		BOOST_AUTO_TEST_CASE(engine_cannot_be_turned_on_twice)
		{
			auto clone(car);
			BOOST_CHECK(!car.TurnOnEngine());
			BOOST_CHECK(car == clone);
		}

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

			{
				car.SetGear(Gear::Fifth);
				auto clone(car);
				car.TurnOffEngine();
				BOOST_CHECK(car == clone);
			}

			{
				car.SetGear(Gear::Reverse);
				auto clone(car);
				car.TurnOffEngine();
				BOOST_CHECK(car == clone);
			}

			{
				car.SetSpeed(5);
				auto clone(car);
				car.TurnOffEngine();
				BOOST_CHECK(car == clone);
			}
		}

		BOOST_AUTO_TEST_CASE(gear_can_be_changed_in_dormancy)
		{
			{
				BOOST_CHECK(car.SetGear(Gear::Neutral));
				BOOST_CHECK(car.GetGear() == Gear::Neutral);
			}

			{
				BOOST_CHECK(car.SetGear(Gear::First));
				BOOST_CHECK(car.GetGear() == Gear::First);
			}

			{
				BOOST_CHECK(car.SetGear(Gear::Reverse));
				BOOST_CHECK(car.GetGear() == Gear::Reverse);
			}

			{
				BOOST_CHECK(!car.SetGear(Gear::Second));
				auto clone(car);
				BOOST_CHECK(car == clone);
			}
		}

		struct in_motion : when_engine_turned_on_
		{
			in_motion()
			{
				car.SetGear(Gear::First);
				car.SetSpeed(25);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(in_motion_, in_motion)

			BOOST_AUTO_TEST_CASE(speed_can_be_changed)
			{
				{
					BOOST_CHECK(car.SetSpeed(30));
					BOOST_CHECK(car.GetSpeed() == 30);
				}

				{
					BOOST_CHECK(car.SetSpeed(20));
					BOOST_CHECK(car.GetSpeed() == 20);
				}

				{
					BOOST_CHECK(!car.SetSpeed(40));
					auto clone(car);
					BOOST_CHECK(car == clone);
				}
			}
			
			BOOST_AUTO_TEST_CASE(gear_can_be_changed)
			{
				{
					BOOST_CHECK(car.SetGear(Gear::First));
				}

				{
					BOOST_CHECK(car.SetGear(Gear::Second));
				}

				{
					BOOST_CHECK(car.SetGear(Gear::Neutral));
				}

				{
					BOOST_CHECK(!car.SetGear(Gear::Third));
				}

				{
					BOOST_CHECK(!car.SetGear(Gear::Reverse));
				}
			}

			BOOST_AUTO_TEST_CASE(gear_can_be_changed_to_itself)
			{
				{
					BOOST_CHECK(car.SetGear(Gear::First));
				}

				{
					BOOST_CHECK(car.SetGear(Gear::Neutral));
					BOOST_CHECK(car.SetGear(Gear::Neutral));
				}

				{
					BOOST_CHECK(car.SetSpeed(0));
					BOOST_CHECK(car.SetGear(Gear::Reverse));
					BOOST_CHECK(car.SetGear(Gear::Reverse));
				}
			}

			struct on_neutral_in_motion : in_motion
			{
				on_neutral_in_motion()
				{
					car.SetGear(Gear::Neutral);
				}
			};


			BOOST_FIXTURE_TEST_SUITE(on_neutral_in_motion_, on_neutral_in_motion)

				BOOST_AUTO_TEST_CASE(direcion_is_forward)
				{
					{
						BOOST_CHECK(car.GetDirection() == Direction::Forward);
					}
				}

				BOOST_AUTO_TEST_CASE(can_reduce_speed) 
				{
					{
						BOOST_CHECK(car.SetSpeed(5));
					}
				}

				BOOST_AUTO_TEST_CASE(cannot_accelerate)
				{
					{
						BOOST_CHECK(!car.SetSpeed(26));
					}

					{
						BOOST_CHECK(car.SetSpeed(25));
					}

					{
						BOOST_CHECK(car.SetSpeed(5));
					}
				}

				BOOST_AUTO_TEST_CASE(can_reduce_speed_to_zero_and_select_reverse_gear)
				{
					{
						BOOST_CHECK(car.SetSpeed(0));
						BOOST_CHECK(car.GetDirection() == Direction::Stop);
						BOOST_CHECK(car.SetGear(Gear::Reverse));
						BOOST_CHECK(car.GetDirection() == Direction::Stop);
						BOOST_CHECK(car.SetSpeed(5));
						BOOST_CHECK(car.GetDirection() == Direction::Back);
					}
				}
			
			BOOST_AUTO_TEST_SUITE_END()

		BOOST_AUTO_TEST_SUITE_END()

		struct on_reverse : when_engine_turned_on_
		{
			on_reverse()
			{
				car.SetGear(Gear::Reverse);
				car.SetSpeed(20);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(on_reverse_, on_reverse)

			BOOST_AUTO_TEST_CASE(can_change_speed)
			{
				{
					BOOST_CHECK(!car.SetSpeed(21));
				}

				{
					BOOST_CHECK(car.SetSpeed(19));
				}

				{
					BOOST_CHECK(car.SetSpeed(0));
				}
			}

			BOOST_AUTO_TEST_CASE(can_change_gear_on_neutral)
			{
				{
					BOOST_CHECK(car.SetGear(Gear::Reverse));
				}

				{
					BOOST_CHECK(car.SetGear(Gear::Neutral));
				}

				{
					BOOST_CHECK(!car.SetGear(Gear::First));
				}
			}

			BOOST_AUTO_TEST_CASE(can_change_gear_from_neutral_to_first_only_in_dormancy)
			{
				{
					BOOST_CHECK(car.SetGear(Gear::Neutral));
					auto clone(car);
					BOOST_CHECK(!car.SetGear(Gear::First));
					BOOST_CHECK(car == clone);
					BOOST_CHECK(car.SetSpeed(0));
					BOOST_CHECK(car.SetGear(Gear::First));
				}
			}

			BOOST_AUTO_TEST_CASE(can_can_get_up_speed_to_zero)
			{
				{
					BOOST_CHECK(car.SetSpeed(0));
				}
			}

			BOOST_AUTO_TEST_CASE(can_can_get_up_speed_to_zero_and_change_gear_to_move_forward)
			{
				{
					BOOST_CHECK(car.SetSpeed(0));
					BOOST_CHECK(car.SetGear(Gear::First));
				}

				{
					BOOST_CHECK(car.SetSpeed(0));
					auto clone(car);
					BOOST_CHECK(!car.SetGear(Gear::Second));
					BOOST_CHECK(car == clone);
				}
			}

		BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
