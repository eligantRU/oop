#include "stdafx.h"

#include "../replace/replace_utils.h"
#include "../replace/replace_utils.cpp"

BOOST_AUTO_TEST_SUITE(Test)

BOOST_AUTO_TEST_CASE(Find_And_Replace)
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
		const std::string expectedResult = "Hello C++!";
		auto result = FindAndReplace("Hello world!", "world", "C++");
		BOOST_CHECK(result == expectedResult);
	}

	{
		const std::string expectedResult = "Hello boost boost boost boost!";
		auto result = FindAndReplace("Hello world world world world!", "world", "boost");
		BOOST_CHECK(result == expectedResult);
	}

	{
		const std::string expectedResult = "Hello    bla-bla-bla !";
		auto result = FindAndReplace("Hello world world world bla-bla-bla world!", "world", "");
		BOOST_CHECK(result == expectedResult);
	}

	{
		const std::string expectedResult = "Hello completed HELLO hElLo";
		auto result = FindAndReplace("Hello hello HELLO hElLo", "hello", "completed");
		BOOST_CHECK(result == expectedResult);
	}

	{
		const std::string expectedResult = "01234567890123456789";
		auto result = FindAndReplace("0123456789", "0", "01234567890");
		BOOST_CHECK(result == expectedResult);
	}
}

BOOST_AUTO_TEST_SUITE_END()
