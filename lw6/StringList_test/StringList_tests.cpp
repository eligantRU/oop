#include "stdafx.h"

#include "../StringList/StringList.h"

struct EmptyStringList
{
	CStringList list;
};

struct when_not_empty : EmptyStringList
{
	when_not_empty()
	{
		list.append("British");
		list.append("r");
		list.append("coming");
		list.append("by");
	}
};

struct TestConstantMethod
{
	template <class T>
	void operator()(T && callback)
	{
		callback();
	}
};

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)

	BOOST_AUTO_TEST_SUITE(when_created)

		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.size(), 0u);
			BOOST_CHECK(list.empty());
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appeding_a_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			BOOST_CHECK(list.empty());
			list.append("hello");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.append("hello");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.append("hello");
			BOOST_CHECK_EQUAL(list.back(), "hello");
			list.append("goodbye");
			BOOST_CHECK_EQUAL(list.back(), "goodbye");
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.append("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_pushing_back_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			BOOST_CHECK(list.empty());
			list.push_back("hello");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.push_back("hello");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.push_back("hello");
			BOOST_CHECK_EQUAL(list.back(), "hello");
			list.push_back("goodbye");
			BOOST_CHECK_EQUAL(list.back(), "goodbye");
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.push_back("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_pushing_front_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			BOOST_CHECK(list.empty());
			list.push_front("hello");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.push_front("hello");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_method)
		{
			list.push_front("hello");
			BOOST_CHECK_EQUAL(list.front(), "hello");
			list.push_front("goodbye");
			BOOST_CHECK_EQUAL(list.front(), "goodbye");
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.push_front("hello");
			auto it = list.begin();
			BOOST_CHECK_EQUAL(addressof(*it), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_insertion_string)
	
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			list.insert(list.begin(), "British");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), 1);

			list.insert(++list.begin(), "coming");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), 2);
			
			list.insert(++list.begin(), "r");
			BOOST_CHECK(!list.empty());
			BOOST_CHECK_EQUAL(list.size(), 3);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_and_GetBackElement_methods)
		{
			list.insert(list.begin(), "British");
			BOOST_CHECK_EQUAL(list.front(), "British");
			BOOST_CHECK_EQUAL(list.back(), "British");

			list.insert(++list.begin(), "coming");
			BOOST_CHECK_EQUAL(list.front(), "British");
			BOOST_CHECK_EQUAL(list.back(), "coming");

			list.insert(++list.begin(), "r");
			BOOST_CHECK_EQUAL(list.front(), "British");
			BOOST_CHECK_EQUAL(list.back(), "coming");
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterators)
		{
			list.insert(list.begin(), "British");
			BOOST_CHECK_EQUAL(*list.begin(), "British");

			list.insert(++list.begin(), "coming");
			BOOST_CHECK_EQUAL(*list.begin(), "British");
			BOOST_CHECK_EQUAL(*(++list.begin()), "coming");

			list.insert(++list.begin(), "r");
			BOOST_CHECK_EQUAL(*list.begin(), "British");
			BOOST_CHECK_EQUAL(*(++list.begin()), "r");
			BOOST_CHECK_EQUAL(*(++(++list.begin())), "coming");
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(when_not_empty_, when_not_empty)

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK(!list.empty());
			list.clear();
			BOOST_CHECK(list.empty());
		}

		BOOST_AUTO_TEST_CASE(can_erase_string_by_iterator)
		{
			{
				list.erase(++list.begin());
				BOOST_CHECK(!list.empty());
				BOOST_CHECK_EQUAL(list.size(), 3);
				BOOST_CHECK_EQUAL(*list.begin(), "British");
				BOOST_CHECK_EQUAL(*(++list.begin()), "coming");
				BOOST_CHECK_EQUAL(*(++(++list.begin())), "by");
			}

			{
				list.erase(list.begin());
				BOOST_CHECK(!list.empty());
				BOOST_CHECK_EQUAL(list.size(), 2);
				BOOST_CHECK_EQUAL(list.front(), "coming");
				BOOST_CHECK_EQUAL(list.back(), "by");
			}

			{
				list.erase(++list.begin());
				BOOST_CHECK(!list.empty());
				BOOST_CHECK_EQUAL(list.size(), 1);
				BOOST_CHECK_EQUAL(list.front(), "coming");
				BOOST_CHECK_EQUAL(list.back(), "coming");
			}

			{
				list.erase(list.begin());
				BOOST_CHECK(list.empty());
				BOOST_CHECK_EQUAL(list.size(), 0);
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(iterator)

		BOOST_AUTO_TEST_CASE(can_be_increnenting)
		{
			list.append("first");
			list.append("second");
			auto iter = list.begin();
			BOOST_CHECK_EQUAL(*iter, "first");
			++iter;
			BOOST_CHECK_EQUAL(*iter, "second");
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
