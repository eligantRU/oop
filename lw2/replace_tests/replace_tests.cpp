#include "stdafx.h"

#include "../replace/replace_utils.h"

BOOST_AUTO_TEST_SUITE(Find_And_Replace)

	BOOST_AUTO_TEST_CASE(can_replace_one_string_on_second)
	{
		{
			const std::string expectedResult = "Hello world!";
			auto result = FindAndReplace("Hello world!", "world", "world");
			BOOST_CHECK(result == expectedResult);
		}

		{
			const std::string expectedResult = "Hello elephant!";
			auto result = FindAndReplace("Hello world!", "world", "elephant");
			BOOST_CHECK(result == expectedResult);
		}

		{
			const std::string expectedResult = "Hello boost boost boost boost!";
			auto result = FindAndReplace("Hello world world world world!", "world", "boost");
			BOOST_CHECK(result == expectedResult);
		}

		{
			const std::string expectedResult = "Hello completed HELLO hElLo";
			auto result = FindAndReplace("Hello hello HELLO hElLo", "hello", "completed");
			BOOST_CHECK(result == expectedResult);
		}

		{
			const std::string expectedResult = "Hello world";
			auto result = FindAndReplace("Hello world", "", "");
			BOOST_CHECK(result == expectedResult);
		}

		{
			const std::string expectedResult = "Hello world";
			auto result = FindAndReplace("Hello world", "", "1234");
			BOOST_CHECK(result == expectedResult);
		}

		{
			const std::string expectedResult = "Hello world";
			auto result = FindAndReplace("Hello world", "elephant", "1234");
			BOOST_CHECK(result == expectedResult);
		}
	}

	BOOST_AUTO_TEST_CASE(can_remove_substring_when_the_replace_string_is_empty)
	{
		const std::string expectedResult = "Hello    bla-bla-bla !";
		auto result = FindAndReplace("Hello world world world bla-bla-bla world!", "world", "");
		BOOST_CHECK(result == expectedResult);
	}

	BOOST_AUTO_TEST_CASE(can_remove_self_repeating_sequence)
	{
		const std::string expectedResult = "01234567890123456789";
		auto result = FindAndReplace("0123456789", "0", "01234567890");
		BOOST_CHECK(result == expectedResult);
	}

BOOST_AUTO_TEST_SUITE_END()
