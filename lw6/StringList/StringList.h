#pragma once

#include <string>
#include <memory>
#include <algorithm>

class CStringList
{
	struct SNode
	{
		SNode(const std::string & data, SNode * prev, std::unique_ptr<SNode> && next);
		std::string data;
		SNode * prev;
		std::unique_ptr<SNode> next;
	};

public:
	CStringList() = default;
	CStringList(const CStringList & list);
	CStringList(CStringList && list);
	CStringList(std::initializer_list<std::string> initList);

	CStringList & operator=(const CStringList & list);
	CStringList & operator=(CStringList && list);
	CStringList & operator=(const std::initializer_list<std::string> & initList);

	class CStringListIterator
	{
		friend CStringList;
		CStringListIterator(SNode * node, bool isReverse = false);
	public:
		CStringListIterator() = delete;
		
		std::string & operator*() const;

		CStringListIterator & operator--();
		CStringListIterator & operator++();

		bool operator==(const CStringListIterator & it) const;
		bool operator!=(const CStringListIterator & it) const;

	private:
		SNode * operator->() const;

		SNode * m_pNode = nullptr;
		bool m_isReverse;
	};

	void clear();

	size_t size() const;
	bool empty() const;

	void append(const std::string & data);
	void push_back(const std::string & data);
	void push_front(const std::string & data);

	void insert(const CStringListIterator & it, const std::string & data);
	void erase(const CStringListIterator & it);
	
	void pop_front();
	void pop_back();

	CStringListIterator begin();
	CStringListIterator end();
	const CStringListIterator begin() const;
	const CStringListIterator end() const;

	const CStringListIterator cbegin() const;
	const CStringListIterator cend() const;

	CStringListIterator rbegin();
	CStringListIterator rend();
	const CStringListIterator rbegin() const;
	const CStringListIterator rend() const;

	const CStringListIterator crbegin() const;
	const CStringListIterator crend() const;

	std::string & front();
	const std::string & front() const;

	std::string & back();
	const std::string & back() const;

	void remove(const std::string & value);

private:
	size_t m_size = 0;
	std::unique_ptr<SNode> m_firstNode;
	SNode * m_lastNode = nullptr;
};
