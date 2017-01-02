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

BOOST_FIXTURE_TEST_SUITE(String_list, EmptyStringList)

	BOOST_AUTO_TEST_CASE(has_copy_assign_operator)
	{
		CStringList nameList({ "Nick", "Alex", "Sergey", "Rinat" });
		CStringList copyList;
		copyList = nameList;
		BOOST_CHECK(!nameList.empty());
		BOOST_CHECK_EQUAL(nameList.size(), 4);
		BOOST_CHECK_EQUAL(nameList.front(), "Nick");
		BOOST_CHECK_EQUAL(nameList.back(), "Rinat");

	}

	BOOST_AUTO_TEST_CASE(has_move_assign_operator)
	{
		CStringList nameList({ "Nick", "Alex", "Sergey", "Rinat" });
		CStringList example;
		example = std::move(nameList);
		BOOST_CHECK(!example.empty());
		BOOST_CHECK_EQUAL(example.size(), 4);
		BOOST_CHECK_EQUAL(example.front(), "Nick");
		BOOST_CHECK_EQUAL(example.back(), "Rinat");

		BOOST_CHECK(nameList.empty());
		BOOST_CHECK_EQUAL(nameList.size(), 0);
	}

	BOOST_AUTO_TEST_CASE(has_initializer_list_assign_operator)
	{
		list = {
			"hello", "world"
		};
		BOOST_CHECK(!list.empty());
		BOOST_CHECK_EQUAL(list.size(), 2);
		BOOST_CHECK_EQUAL(list.front(), "hello");
		BOOST_CHECK_EQUAL(list.back(), "world");
	}

	BOOST_AUTO_TEST_CASE(has_default_constructor)
	{
		CStringList example;
		BOOST_CHECK(example.empty());
		BOOST_CHECK_EQUAL(example.size(), 0);
	}

	BOOST_AUTO_TEST_CASE(has_constructor_with_initializer_list)
	{
		CStringList example({ "initializer", "list " });
		BOOST_CHECK(!example.empty());
		BOOST_CHECK_EQUAL(example.size(), 2);
	}

	BOOST_AUTO_TEST_CASE(has_copy_constructor)
	{
		CStringList baseList({ "initializer", "list " });
		auto example = baseList;
		BOOST_CHECK(!example.empty());
		BOOST_CHECK_EQUAL(example.size(), 2);
	}

	BOOST_AUTO_TEST_CASE(has_move_constructor)
	{
		CStringList baseList({ "initializer", "list " });
		auto example = std::move(baseList);
		BOOST_CHECK(!example.empty());
		BOOST_CHECK_EQUAL(example.size(), 2);
		BOOST_CHECK(baseList.empty());
		BOOST_CHECK_EQUAL(baseList.size(), 0);

	}

	BOOST_AUTO_TEST_SUITE(when_list_created_by_default_constructor)

		BOOST_AUTO_TEST_CASE(is_empty)
		{
			BOOST_CHECK_EQUAL(list.size(), 0);
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

		BOOST_AUTO_TEST_CASE(can_get_first_via_front)
		{
			BOOST_CHECK_EQUAL(list.front(), "British");
		}

		BOOST_AUTO_TEST_CASE(can_get_last_via_back)
		{
			BOOST_CHECK_EQUAL(list.back(), "by");
		}

		BOOST_AUTO_TEST_CASE(can_get_const_first_via_front)
		{
			const auto example(list);
			BOOST_CHECK_EQUAL(example.front(), "British");
		}

		BOOST_AUTO_TEST_CASE(can_get_const_last_via_back)
		{
			const auto example(list);
			BOOST_CHECK_EQUAL(example.back(), "by");
		}

		BOOST_AUTO_TEST_CASE(can_remove_the_first_element_via_pop_front)
		{
			list.pop_front();
			BOOST_CHECK_EQUAL(list.size(), 3);
			BOOST_CHECK_EQUAL(list.front(), "r");
		}

		BOOST_AUTO_TEST_CASE(can_remove_the_last_element_via_pop_back)
		{
			list.pop_back();
			BOOST_CHECK_EQUAL(list.size(), 3);
			BOOST_CHECK_EQUAL(list.back(), "coming");
		}

		BOOST_AUTO_TEST_CASE(can_remove_elements_by_value)
		{
			{
				CStringList example{
					"PHP", "PHP", "C++", "PHP", "Java", "PHP", "PHP", "Go", "Python", "PHP", "PHP"
				};
				example.remove("PHP");
				BOOST_CHECK_EQUAL(example.size(), 4);
			}

			{
				CStringList example{
					"PHP", "PHP"
				};
				example.remove("PHP");
				BOOST_CHECK_EQUAL(example.size(), 0);
			}

			{
				CStringList example{
					"C", "PHP"
				};
				example.remove("PHP");
				BOOST_CHECK_EQUAL(example.size(), 1);
			}

			{
				CStringList example{
					"C", "PHP", "C"
				};
				example.remove("PHP");
				BOOST_CHECK_EQUAL(example.size(), 2);
			}

			{
				CStringList example{
					"C", "PHP", "PHP", "C"
				};
				example.remove("PHP");
				BOOST_CHECK_EQUAL(example.size(), 2);
			}

			{
				CStringList example{
					"PHP", "PHP", "C"
				};
				example.remove("PHP");
				BOOST_CHECK_EQUAL(example.size(), 1);
			}

			{
				CStringList example{
					"OpenGL", "DirectX"
				};
				example.remove("PHP");
				BOOST_CHECK_EQUAL(example.size(), 2);
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(iterator)

		BOOST_AUTO_TEST_CASE(can_be_incrementing)
		{
			list.append("first");
			list.append("second");
			auto iter = list.begin();
			BOOST_CHECK_EQUAL(*iter, "first");
			++iter;
			BOOST_CHECK_EQUAL(*iter, "second");
		}

		BOOST_AUTO_TEST_CASE(can_be_decrementing)
		{
			list.append("first");
			list.append("second");
			list.append("third");

			auto iter = ++(++list.begin());
			BOOST_CHECK_EQUAL(*iter, "third");
			BOOST_CHECK_EQUAL(*(--iter), "second");
			BOOST_CHECK_EQUAL(*(--iter), "first");
		}

		BOOST_AUTO_TEST_CASE(can_work_with_range_based_for)
		{
			list.append("British");
			list.append("r");
			list.append("coming");
			list.append("by");
			const std::vector<std::string> expectedResult = {
				"British", "r", "coming", "by"
			};

			std::vector<std::string> elements;
			for (const auto element : list)
			{
				elements.push_back(element);
			}
			BOOST_CHECK(elements == expectedResult);
		}

		BOOST_AUTO_TEST_CASE(can_be_const)
		{
			{
				const CStringList example = { "bla", "bla-bla" };
				auto it = example.begin();
				BOOST_CHECK_EQUAL(*it, "bla");
				BOOST_CHECK_EQUAL(*(++it), "bla-bla");
				BOOST_CHECK(++it == example.end());
			}

			{
				const CStringList example = { "bla", "bla-bla" };
				auto it = example.cbegin();
				BOOST_CHECK_EQUAL(*it, "bla");
				BOOST_CHECK_EQUAL(*(++it), "bla-bla");
				BOOST_CHECK(++it == example.cend());
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
