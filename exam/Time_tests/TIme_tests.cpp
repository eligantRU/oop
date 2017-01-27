#include "stdafx.h"

#include "../exam/Time.h"

namespace
{

void VerifyTime(const CTime & lhs, const CTime & rhs)
{
	BOOST_CHECK_EQUAL(lhs.GetSeconds(), rhs.GetSeconds());
	BOOST_CHECK_EQUAL(lhs.GetMinutes(), rhs.GetMinutes());
	BOOST_CHECK_EQUAL(lhs.GetHours(), rhs.GetHours());
}

}

BOOST_AUTO_TEST_SUITE(Time)

	BOOST_AUTO_TEST_CASE(is_0_by_default)
	{
		CTime time;
		BOOST_CHECK_EQUAL(time.GetTimeStamp(), 0);
		BOOST_CHECK_EQUAL(time.GetHours(), 0);
		BOOST_CHECK_EQUAL(time.GetMinutes(), 0);
		BOOST_CHECK_EQUAL(time.GetSeconds(), 0);
	}

	BOOST_AUTO_TEST_CASE(cannot_have_invalid_time_value)
	{
		BOOST_REQUIRE_THROW(CTime(-1, 0, 0), std::invalid_argument);
		BOOST_REQUIRE_THROW(CTime(0, -1, 0), std::invalid_argument);
		BOOST_REQUIRE_THROW(CTime(0, 0, -1), std::invalid_argument);
		BOOST_REQUIRE_THROW(CTime(24, 0, 0), std::invalid_argument);
		BOOST_REQUIRE_THROW(CTime(0, 60, 0), std::invalid_argument);
		BOOST_REQUIRE_THROW(CTime(0, 0, 60), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_return_seconds)
	{
		{
			CTime time(23, 42, 17);
			BOOST_CHECK_EQUAL(time.GetSeconds(), 17);
		}

		{
			CTime time(23, 42, 59);
			BOOST_CHECK_EQUAL(time.GetSeconds(), 59);
		}

		{
			CTime time(23, 42, 31);
			BOOST_CHECK_EQUAL(time.GetSeconds(), 31);
		}
	}

	BOOST_AUTO_TEST_CASE(can_return_minutes)
	{
		{
			CTime time(23, 59, 17);
			BOOST_CHECK_EQUAL(time.GetMinutes(), 59);
		}

		{
			CTime time(23, 17, 59);
			BOOST_CHECK_EQUAL(time.GetMinutes(), 17);
		}

		{
			CTime time(23, 1, 31);
			BOOST_CHECK_EQUAL(time.GetMinutes(), 1);
		}
	}

	BOOST_AUTO_TEST_CASE(can_return_hours)
	{
		{
			CTime time(11, 59, 17);
			BOOST_CHECK_EQUAL(time.GetHours(), 11);
		}

		{
			CTime time(1, 17, 59);
			BOOST_CHECK_EQUAL(time.GetHours(), 1);
		}

		{
			CTime time(23, 1, 31);
			BOOST_CHECK_EQUAL(time.GetHours(), 23);
		}
	}

	BOOST_AUTO_TEST_CASE(can_be_converted_to_string)
	{
		{
			CTime time(11, 59, 4);
			BOOST_CHECK_EQUAL(time.ToString(), "11:59:04");
		}

		{
			CTime time(1, 17, 59);
			BOOST_CHECK_EQUAL(time.ToString(), "01:17:59");
		}

		{
			CTime time(23, 1, 31);
			BOOST_CHECK_EQUAL(time.ToString(), "23:01:31");
		}
	}

	BOOST_AUTO_TEST_CASE(has_binary_addition_operator)
	{
		VerifyTime(CTime(23, 59, 59) + CTime(0, 0, 0), CTime(23, 59, 59));
		VerifyTime(CTime(23, 59, 59) + CTime(0, 0, 1), CTime(0, 0, 0));
		VerifyTime(CTime(22, 59, 59) + CTime(0, 0, 1), CTime(23, 0, 0));
		VerifyTime(CTime(17, 16, 11) + CTime(17, 49, 59), CTime(11, 6, 10));
		VerifyTime(CTime(8, 29, 39) + CTime(01, 01, 01), CTime(9, 30, 40));
	}

	BOOST_AUTO_TEST_CASE(has_binary_assign_addition_operator)
	{
		VerifyTime(CTime(23, 59, 59) += CTime(0, 0, 0), CTime(23, 59, 59));
		VerifyTime(CTime(23, 59, 59) += CTime(0, 0, 1), CTime(0, 0, 0));
		VerifyTime(CTime(22, 59, 59) += CTime(0, 0, 1), CTime(23, 0, 0));
		VerifyTime(CTime(17, 16, 11) += CTime(17, 49, 59), CTime(11, 6, 10));
		VerifyTime(CTime(8, 29, 39) += CTime(1, 1, 1), CTime(9, 30, 40));
	}

	BOOST_AUTO_TEST_CASE(has_binary_subtraction_operator)
	{
		VerifyTime(CTime(23, 59, 59) - CTime(0, 0, 0), CTime(23, 59, 59));
		VerifyTime(CTime(23, 59, 59) - CTime(23, 59, 59), CTime(0, 0, 0));
		VerifyTime(CTime(22, 59, 59) - CTime(0, 0, 1), CTime(22, 59, 58));
		VerifyTime(CTime(17, 16, 11) - CTime(17, 49, 59), CTime(23, 26, 12));
		VerifyTime(CTime(8, 29, 39) - CTime(1, 1, 1), CTime(7, 28, 38));
	}

	BOOST_AUTO_TEST_CASE(has_binary_assign_subtraction_operator)
	{
		VerifyTime(CTime(23, 59, 59) -= CTime(0, 0, 0), CTime(23, 59, 59));
		VerifyTime(CTime(23, 59, 59) -= CTime(23, 59, 59), CTime(0, 0, 0));
		VerifyTime(CTime(22, 59, 59) -= CTime(1, 27, 16), CTime(21, 32, 43));
		VerifyTime(CTime(17, 16, 11) -= CTime(17, 49, 59), CTime(23, 26, 12));
		VerifyTime(CTime(8, 29, 39) -= CTime(1, 1, 1), CTime(7, 28, 38));
	}

	BOOST_AUTO_TEST_CASE(can_be_print_to_ostream)
	{
		std::stringstream stream;
		stream << CTime(23, 1, 17);
		BOOST_CHECK_EQUAL(stream.str(), "23:01:17");
	}

BOOST_AUTO_TEST_SUITE_END()
