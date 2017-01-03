#pragma once

#include <string>
#include <memory>

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
	CStringList(const size_t n);
	CStringList(const size_t n, const std::string & value);

	CStringList & operator=(const CStringList & list);
	CStringList & operator=(CStringList && list);
	CStringList & operator=(const std::initializer_list<std::string> & initList);

	class CIterator
	{
		friend CStringList;
		CIterator(SNode * node, bool isReverse = false);
	public:
		CIterator() = delete;
		
		std::string & operator*() const;
		CIterator & operator--();
		CIterator & operator++();

		bool operator==(const CIterator & it) const;
		bool operator!=(const CIterator & it) const;

	private:
		SNode * operator->() const;

		SNode * m_pNode = nullptr;
		bool m_isReverse;
	};

	void clear();

	size_t size() const;
	size_t max_size() const;
	bool empty() const;

	void append(const std::string & data);
	void append(std::string && data);
	void push_back(const std::string & data);
	void push_front(const std::string & data);
	void push_back(std::string && data);
	void push_front(std::string && data);

	void insert(const CIterator & it, const std::string & data);
	void insert(const CIterator & it, std::string && data);
	void insert(const CIterator & it, const size_t n, const std::string & data);
	void insert(const CIterator & it, const std::initializer_list<std::string> & il);
	void erase(const CIterator & it);
	void erase(const CIterator & first, const CIterator & last);

	void pop_front();
	void pop_back();

	CIterator begin();
	CIterator end();
	const CIterator begin() const;
	const CIterator end() const;

	const CIterator cbegin() const;
	const CIterator cend() const;

	CIterator rbegin();
	CIterator rend();
	const CIterator rbegin() const;
	const CIterator rend() const;

	const CIterator crbegin() const;
	const CIterator crend() const;

	std::string & front();
	const std::string & front() const;

	std::string & back();
	const std::string & back() const;

	void remove(const std::string & value);

	void swap(CStringList & list);

private:
	size_t m_size = 0;
	std::unique_ptr<SNode> m_firstNode;
	SNode * m_lastNode = nullptr;
};
