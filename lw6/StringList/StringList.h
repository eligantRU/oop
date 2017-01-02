#pragma once

#include <string>
#include <memory>
#include <algorithm>

class CStringList
{
	struct Node
	{
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next);
		std::string data;
		Node * prev;
		std::unique_ptr<Node> next;
	};

public:
	CStringList() = default;
	CStringList(const CStringList & list);
	CStringList(CStringList && list);
	CStringList(std::initializer_list<std::string> initList);

	CStringList & operator=(const CStringList & list);
	CStringList & operator=(CStringList && list);
	CStringList & operator=(const std::initializer_list<std::string> & initList);

	class CIterator
	{
		friend CStringList;
		CIterator(Node * node);
	public:
		CIterator() = default;
		
		std::string & operator*() const;
		Node * operator->() const;
		CIterator & operator--();
		CIterator & operator++();

		bool operator==(const CStringList::CIterator & it) const;
		bool operator!=(const CStringList::CIterator & it) const;

	private:
		Node * m_node = nullptr;
	};

	void clear();

	size_t size() const;
	bool empty() const;

	void append(const std::string & data);
	void push_back(const std::string & data);
	void push_front(const std::string & data);

	void insert(const CIterator & it, const std::string & data);
	void erase(const CIterator & it);
	
	void pop_front();
	void pop_back();

	CIterator begin();
	CIterator end();
	const CIterator begin() const;
	const CIterator end() const;

	const CIterator cbegin() const;
	const CIterator cend() const;

	std::string & front();
	const std::string & front() const;

	std::string & back();
	const std::string & back() const;

	void remove(const std::string & value);

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node * m_lastNode = nullptr;
};
