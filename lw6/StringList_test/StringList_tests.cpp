#include "stdafx.h"

#include "../StringList/StringList.h"

namespace
{

std::string exampleStr1 = "bla";
std::string exampleStr2 = "bla-bla";
std::string exampleStr3 = "bla-bla-bla";

}

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

BOOST_FIXTURE_TEST_SUITE(MyList, EmptyStringList)

	BOOST_AUTO_TEST_CASE(has_default_constructor)
	{
		BOOST_CHECK(list.empty());
	}

	BOOST_AUTO_TEST_CASE(has_constructor_with_initializer_list)
	{
		CStringList example({ "initializer", "list" });
		BOOST_CHECK_EQUAL(example.size(), 2);
		BOOST_CHECK(example == CStringList({ "initializer", "list" }));
	}

	BOOST_AUTO_TEST_CASE(has_copy_constructor)
	{
		CStringList baseList({ "initializer", "list" });
		auto example(baseList);
		BOOST_CHECK_EQUAL(example.size(), 2);
		BOOST_CHECK(example == CStringList({ "initializer", "list" }));
	}

	BOOST_AUTO_TEST_CASE(has_move_constructor)
	{
		CStringList baseList({ "initializer", "list" });
		auto example = std::move(baseList);
		BOOST_CHECK_EQUAL(example.size(), 2);
		BOOST_CHECK(baseList.empty());
		BOOST_CHECK(example == CStringList({ "initializer", "list" }));
		BOOST_CHECK(baseList == CStringList());
	}

	BOOST_AUTO_TEST_CASE(has_fill_constructor)
	{
		{
			CStringList example(3);
			BOOST_CHECK_EQUAL(example.size(), 3);
			BOOST_CHECK(example == CStringList({ "", "", "" }));
		}

		{
			CStringList example(4, "OOP");
			BOOST_CHECK_EQUAL(example.size(), 4);
			BOOST_CHECK(example == CStringList({ "OOP", "OOP", "OOP", "OOP" }));
		}
	}

	BOOST_AUTO_TEST_CASE(has_copy_assign_operator)
	{
		CStringList nameList({ "Nick", "Alex", "Sergey", "Rinat" });
		nameList = nameList;
		BOOST_CHECK(nameList == CStringList({ "Nick", "Alex", "Sergey", "Rinat" }));
		CStringList copyList;
		copyList = nameList;
		BOOST_CHECK_EQUAL(nameList.size(), 4);
		BOOST_CHECK_EQUAL(copyList.size(), 4);
		BOOST_CHECK(nameList == CStringList({ "Nick", "Alex", "Sergey", "Rinat" }));
		BOOST_CHECK(copyList == CStringList({ "Nick", "Alex", "Sergey", "Rinat" }));
	}

	BOOST_AUTO_TEST_CASE(has_initializer_list_assign_operator)
	{
		list = {
			"hello", "world"
		};
		BOOST_CHECK_EQUAL(list.size(), 2);
		BOOST_CHECK(list == CStringList({ "hello", "world" }));
	}

	BOOST_AUTO_TEST_CASE(has_move_assign_operator)
	{
		{
			list = {
				"Nick", "Alex", "Sergey", "Rinat"
			};
			CStringList example;
			example = std::move(list);
			BOOST_CHECK_EQUAL(example.size(), 4);
			BOOST_CHECK(example == CStringList({ "Nick", "Alex", "Sergey", "Rinat" }));

			BOOST_CHECK(list.empty());
			BOOST_CHECK(list == CStringList());
		}

		{
			list = {
				"Nick", "Alex", "Sergey", "Rinat"
			};
			const auto clone(list);
			list = std::move(list);
			BOOST_CHECK(list == clone);
		}
	}

	BOOST_AUTO_TEST_CASE(can_potential_contain_max_size_strings)
	{
		BOOST_CHECK_EQUAL(list.max_size(), std::numeric_limits<size_t>::max());
	}

	BOOST_AUTO_TEST_SUITE(after_appeding_rvalue_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			list.append("hello");
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.append("hello");
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
			BOOST_CHECK_EQUAL(addressof(*list.begin()), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_appeding_lvalue_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			list.append(exampleStr1);
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.append(exampleStr1);
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.append(exampleStr1);
			BOOST_CHECK_EQUAL(list.back(), exampleStr1);
			list.append(exampleStr2);
			BOOST_CHECK_EQUAL(list.back(), exampleStr2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.append(exampleStr2);
			BOOST_CHECK_EQUAL(addressof(*list.begin()), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_pushing_back_rvalue_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			list.push_back("hello");
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.push_back("hello");
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
			BOOST_CHECK_EQUAL(addressof(*list.begin()), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_pushing_back_lvalue_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			list.push_back(exampleStr1);
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.push_back(exampleStr1);
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetBackElement_method)
		{
			list.push_back(exampleStr1);
			BOOST_CHECK_EQUAL(list.back(), exampleStr1);
			list.push_back(exampleStr2);
			BOOST_CHECK_EQUAL(list.back(), exampleStr2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.push_back(exampleStr1);
			BOOST_CHECK_EQUAL(addressof(*list.begin()), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_pushing_front_rvalue_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			list.push_front("hello");
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.push_front("hello");
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
			BOOST_CHECK_EQUAL(addressof(*list.begin()), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_pushing_front_lvalue_string)

		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			list.push_front(exampleStr1);
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);
			list.push_front(exampleStr1);
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_GetFrontElement_method)
		{
			list.push_front(exampleStr1);
			BOOST_CHECK_EQUAL(list.front(), exampleStr1);
			list.push_front(exampleStr2);
			BOOST_CHECK_EQUAL(list.front(), exampleStr2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterator_to_first_element)
		{
			list.push_front(exampleStr1);
			BOOST_CHECK_EQUAL(addressof(*list.begin()), addressof(list.back()));
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(after_insertion_rvalue_string)
	
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			list.insert(list.begin(), "British");
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);

			list.insert(++list.begin(), "coming");
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
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

	BOOST_AUTO_TEST_SUITE(after_insertion_lvalue_string)
	
		BOOST_AUTO_TEST_CASE(increases_its_size_by_1)
		{
			auto oldSize = list.size();
			list.insert(list.begin(), exampleStr1);
			BOOST_CHECK_EQUAL(list.size(), oldSize + 1);

			list.insert(++list.begin(), exampleStr2);
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
		}

		BOOST_AUTO_TEST_CASE(makes_it_accessible_via_iterators)
		{
			list.insert(list.begin(), exampleStr1);
			BOOST_CHECK_EQUAL(*list.begin(), exampleStr1);

			list.insert(++list.begin(), exampleStr2);
			BOOST_CHECK_EQUAL(*list.begin(), exampleStr1);
			BOOST_CHECK_EQUAL(*(++list.begin()), exampleStr2);

			list.insert(++list.begin(), exampleStr3);
			BOOST_CHECK_EQUAL(*list.begin(), exampleStr1);
			BOOST_CHECK_EQUAL(*(++list.begin()), exampleStr3);
			BOOST_CHECK_EQUAL(*(++(++list.begin())), exampleStr2);
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(when_not_empty_, when_not_empty)

		BOOST_AUTO_TEST_CASE(can_be_compared_for_equality)
		{
			CStringList list0 = {};
			CStringList list1 = {};
			CStringList list2 = { "hello" };
			CStringList list3 = { "hello" };
			CStringList list4 = { "hello", "bla" };
			CStringList list5 = { "hello", "bla" };
			CStringList list6 = { "hello", "bla-bla" };

			BOOST_CHECK(list0 == list1);
			BOOST_CHECK(list2 == list3);
			BOOST_CHECK(list4 == list5);
			BOOST_CHECK(list6 == list6);
			BOOST_CHECK(!(list0 == list5));
			BOOST_CHECK(!(list5 == list6));

			BOOST_CHECK(!(list0 != list1));
			BOOST_CHECK(!(list2 != list3));
			BOOST_CHECK(!(list4 != list5));
			BOOST_CHECK(!(list6 != list6));
			BOOST_CHECK(list0 != list5);
			BOOST_CHECK(list5 != list6);
		}

		BOOST_AUTO_TEST_CASE(can_be_cleared)
		{
			BOOST_CHECK(!list.empty());
			list.clear();
			BOOST_CHECK(list.empty());
		}

		BOOST_AUTO_TEST_CASE(can_be_resized)
		{
			{
				list.resize(6);
				BOOST_CHECK_EQUAL(list.size(), 6);
				BOOST_CHECK(list == CStringList({ "British", "r", "coming", "by", "", "" }));

				list.resize(2);
				BOOST_CHECK_EQUAL(list.size(), 2);
				BOOST_CHECK(list == CStringList({ "British", "r" }));

				auto clone(list);
				list.resize(2);
				BOOST_CHECK(clone == list);
			}

			{
				list = {
					"British", "r", "coming", "by"
				};
				list.resize(6, "sea");
				BOOST_CHECK_EQUAL(list.size(), 6);
				BOOST_CHECK(list == CStringList({ "British", "r", "coming", "by", "sea", "sea" }));

				list.resize(2, "unused string");
				BOOST_CHECK_EQUAL(list.size(), 2);
				BOOST_CHECK(list == CStringList({ "British", "r" }));

				auto clone(list);
				list.resize(2, "unused string");
				BOOST_CHECK(clone == list);
			}
		}

		BOOST_AUTO_TEST_CASE(can_be_swapped)
		{
			CStringList first(3, "hello");
			CStringList second(2, "world");
			auto it1 = first.begin();
			auto it2 = second.begin();
			BOOST_CHECK_EQUAL(*it1, "hello");
			BOOST_CHECK_EQUAL(*it2, "world");
			first.swap(second);
			BOOST_CHECK_EQUAL(first.size(), 2);
			BOOST_CHECK(first == CStringList({ "world", "world" }));
			BOOST_CHECK_EQUAL(second.size(), 3);
			BOOST_CHECK(second == CStringList({ "hello", "hello", "hello" }));
			BOOST_CHECK_EQUAL(*it1, "hello");
			BOOST_CHECK_EQUAL(*it2, "world");
		}

		BOOST_AUTO_TEST_CASE(can_erase_string_by_iterator)
		{
			{
				auto oldSize = list.size();
				list.erase(++list.begin());
				BOOST_CHECK_EQUAL(list.size(), oldSize - 1);
				BOOST_CHECK(list == CStringList({"British", "coming", "by"}));
			}

			{
				auto oldSize = list.size();
				list.erase(list.begin());
				BOOST_CHECK_EQUAL(list.size(), oldSize - 1);
				BOOST_CHECK(list == CStringList({ "coming", "by" }));
			}

			{
				auto oldSize = list.size();
				list.erase(++list.begin());
				BOOST_CHECK_EQUAL(list.size(), oldSize - 1);
				BOOST_CHECK(list == CStringList({ "coming" }));
			}

			{
				list.erase(list.begin());
				BOOST_CHECK(list.empty());
			}
		}

		BOOST_AUTO_TEST_CASE(can_erase_strings_by_two_iterators)
		{
			{
				CStringList example = {
					"British", "r", "coming", "by"
				};
				example.erase(++example.begin(), example.end());
				BOOST_CHECK_EQUAL(example.size(), 1);
				BOOST_CHECK(example == CStringList({ "British" }));
			}

			{
				CStringList example = {
					"British", "r", "coming", "by"
				};
				example.erase(++example.begin(), ++(++(++example.begin())));
				BOOST_CHECK_EQUAL(example.size(), 2);
				BOOST_CHECK(example == CStringList({ "British", "by" }));
			}

			{
				CStringList example = {
					"British", "r", "coming"
				};
				example.erase(++example.begin(), ++(++example.begin()));
				BOOST_CHECK_EQUAL(example.size(), 2);
				BOOST_CHECK(example == CStringList({ "British", "coming" }));
			}

			{
				CStringList example = {
					"British", "r", "coming"
				};
				example.erase(example.begin(), ++example.begin());
				BOOST_CHECK_EQUAL(example.size(), 2);
				BOOST_CHECK(example == CStringList({ "r", "coming" }));
			}

			{
				CStringList example = {
					"Lucky"
				};
				example.erase(example.begin(), example.begin());
				BOOST_CHECK_EQUAL(example.size(), 1);
				BOOST_CHECK(example == CStringList({ "Lucky" }));
			}

			{
				CStringList example = {
					"We", "r", "not", "too", "lucky"
				};
				example.erase(example.begin(), example.end());
				BOOST_CHECK(example.empty());
			}
		}

		BOOST_AUTO_TEST_CASE(can_insert_some_strings_via_iterator)
		{
			auto oldSize = list.size();
			list.insert(++list.begin(), 2, "tygydyk");
			BOOST_CHECK_EQUAL(list.size(), oldSize + 2);
			BOOST_CHECK(list == CStringList({ "British", "tygydyk" , "tygydyk", "r", "coming", "by", }));
		}

		BOOST_AUTO_TEST_CASE(can_insert_some_strings_via_initializer_list)
		{
			auto oldSize = list.size();
			list.insert(++list.begin(), { "Lorem", "ipsum", "dolor" });
			BOOST_CHECK_EQUAL(list.size(), oldSize + 3);
			BOOST_CHECK(list == CStringList({ "British", "Lorem", "ipsum", "dolor", "r", "coming", "by", }));
		}

		BOOST_AUTO_TEST_CASE(can_insert_some_string_from_other_list_via_iterators)
		{
			{
				CStringList example = {
					"loves", "OOP", "and"
				};
				list.insert(++list.begin(), example.begin(), example.end());
				BOOST_CHECK_EQUAL(list.size(), 7);
				BOOST_CHECK(list == CStringList({ "British", "loves", "OOP", "and", "r", "coming", "by", }));
			}

			{
				CStringList example = {
					"loves", "OOP", "and"
				};
				CStringList empty;
				auto clone(example);

				example.insert(example.begin(), empty.begin(), empty.end());
				BOOST_CHECK(clone == example);
				example.insert(example.end(), empty.begin(), empty.end());
				BOOST_CHECK(clone == example);
				example.insert(++example.begin(), empty.begin(), empty.end());
				BOOST_CHECK(clone == example);
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
			auto oldSize = list.size();
			list.pop_front();
			BOOST_CHECK_EQUAL(list.size(), oldSize - 1);
			BOOST_CHECK_EQUAL(list.front(), "r");
		}

		BOOST_AUTO_TEST_CASE(can_remove_the_last_element_via_pop_back)
		{
			auto oldSize = list.size();
			list.pop_back();
			BOOST_CHECK_EQUAL(list.size(), oldSize - 1);
			BOOST_CHECK_EQUAL(list.back(), "coming");
		}

		BOOST_AUTO_TEST_CASE(can_remove_elements_by_value)
		{
			{
				CStringList example{
					"PHP", "PHP"
				};
				example.remove("PHP");
				BOOST_CHECK(example.empty());
			}

			{
				CStringList example{
					"C", "PHP"
				};
				example.remove("PHP");
				BOOST_CHECK(example == CStringList({ "C" }));
			}

			{
				CStringList example{
					"C", "PHP", "C"
				};
				example.remove("PHP");
				BOOST_CHECK(example == CStringList({ "C", "C" }));
			}

			{
				CStringList example{
					"C", "PHP", "PHP", "C"
				};
				example.remove("PHP");
				BOOST_CHECK(example == CStringList({ "C", "C" }));
			}

			{
				CStringList example{
					"PHP", "PHP", "C"
				};
				example.remove("PHP");
				BOOST_CHECK(example == CStringList({ "C" }));
			}

			{
				CStringList example{
					"OpenGL", "DirectX"
				};
				auto clone(example);
				example.remove("PHP");
				BOOST_CHECK(example == clone);
			}

			{
				CStringList example{
					"PHP", "PHP", "C++", "PHP", "Java", "PHP", "PHP", "Go", "Python", "PHP", "PHP"
				};
				example.remove("PHP");
				BOOST_CHECK(example == CStringList({ "C++", "Java", "Go", "Python" }));
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

	BOOST_FIXTURE_TEST_SUITE(iterator, when_not_empty)

		BOOST_AUTO_TEST_CASE(when_the_list_is_empty_begin_and_end_r_equal)
		{
			{
				CStringList empty;
				BOOST_CHECK(empty.begin() == empty.end());
			}

			{
				const CStringList empty;
				BOOST_CHECK(empty.begin() == empty.end());
			}

			{
				CStringList empty;
				BOOST_CHECK(empty.cbegin() == empty.cend());
			}

			{
				CStringList empty;
				BOOST_CHECK(empty.rbegin() == empty.rend());
			}

			{
				const CStringList empty;
				BOOST_CHECK(empty.rbegin() == empty.rend());
			}

			{
				CStringList empty;
				BOOST_CHECK(empty.crbegin() == empty.crend());
			}
		}

		BOOST_AUTO_TEST_CASE(can_be_preincrementing)
		{
			auto iter1 = ++list.begin();
			BOOST_CHECK_EQUAL(*iter1, "r");

			const auto iter2 = ++list.begin();
			BOOST_CHECK_EQUAL(*iter2, "r");

			auto iter3 = ++list.rbegin();
			BOOST_CHECK_EQUAL(*iter3, "coming");

			const auto iter4 = ++list.rbegin();
			BOOST_CHECK_EQUAL(*iter4, "coming");
		}

		BOOST_AUTO_TEST_CASE(can_be_predecrementing)
		{
			auto iter1 = ++(++list.begin());
			BOOST_CHECK_EQUAL(*(--iter1), "r");

			const auto iter2 = --iter1;
			BOOST_CHECK_EQUAL(*iter2, "British");

			auto iter3 = ++(++list.rbegin());
			BOOST_CHECK_EQUAL(*(--iter3), "coming");

			const auto iter4 = --iter3;
			BOOST_CHECK_EQUAL(*iter4, "by");
		}

		BOOST_AUTO_TEST_CASE(can_be_postincrementing)
		{
			auto iter1 = list.begin();
			BOOST_CHECK_EQUAL(*iter1++, "British");
			BOOST_CHECK_EQUAL(*iter1, "r");

			const auto iter2 = list.begin()++;
			BOOST_CHECK_EQUAL(*iter2, "British");

			auto iter3 = list.rbegin();
			BOOST_CHECK_EQUAL(*iter3++, "by");
			BOOST_CHECK_EQUAL(*iter3++, "coming");

			const auto iter4 = list.rbegin()++;
			BOOST_CHECK_EQUAL(*iter4, "by");
		}

		BOOST_AUTO_TEST_CASE(can_be_postdecrementing)
		{
			auto iter1 = ++(++list.begin());
			BOOST_CHECK_EQUAL(*(iter1--), "coming");
			BOOST_CHECK_EQUAL(*iter1, "r");

			const auto iter2 = iter1--;
			BOOST_CHECK_EQUAL(*iter2, "r");

			auto iter3 = ++(++list.rbegin());
			BOOST_CHECK_EQUAL(*(iter3--), "r");
			BOOST_CHECK_EQUAL(*iter3, "coming");

			const auto iter4 = iter3--;
			BOOST_CHECK_EQUAL(*iter4, "coming");
		}

		BOOST_AUTO_TEST_CASE(can_work_with_range_based_for)
		{
			const CStringList expectedResult = {
				"British", "r", "coming", "by"
			};

			CStringList elements;
			for (const auto & element : list)
			{
				elements.push_back(element);
			}
			BOOST_CHECK(elements == expectedResult);
		}

		BOOST_AUTO_TEST_CASE(can_work_with_algorithms)
		{
			const auto min = *std::min_element(list.begin(), list.end());
			BOOST_CHECK_EQUAL(min, "British");
			const auto max = *std::max_element(list.begin(), list.end());
			BOOST_CHECK_EQUAL(max, "r");
		}

		BOOST_AUTO_TEST_CASE(can_be_reversed)
		{
			{
				CStringList developers = {
					"Malov", "Shambir", "Larionov"
				};
				BOOST_CHECK_EQUAL(*developers.rbegin(), "Larionov");
				BOOST_CHECK_EQUAL(*(++developers.rbegin()), "Shambir");
				BOOST_CHECK_EQUAL(*(++(++developers.rbegin())), "Malov");
				BOOST_CHECK(++(++(++developers.rbegin())) == developers.rend());
			}
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

			{
				const CStringList developers = {
					"Malov", "Shambir", "Larionov"
				};
				auto it = developers.rbegin();
				BOOST_CHECK_EQUAL(*it, "Larionov");
				BOOST_CHECK_EQUAL(*(++it), "Shambir");
				BOOST_CHECK_EQUAL(*(++it), "Malov");
				BOOST_CHECK(++it == developers.rend());
			}

			{
				const CStringList developers = {
					"Malov", "Shambir", "Larionov"
				};
				auto it = developers.crbegin();
				BOOST_CHECK_EQUAL(*it, "Larionov");
				BOOST_CHECK_EQUAL(*(++it), "Shambir");
				BOOST_CHECK_EQUAL(*(++it), "Malov");
				BOOST_CHECK(++it == developers.crend());
			}
		}

	BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE_END()
