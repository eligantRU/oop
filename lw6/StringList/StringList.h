#pragma once

#include <memory>
#include <string>
#include <assert.h>

class CStringList
{
	struct SNode
	{
		template <class T>
		SNode(T && data, SNode * prev, std::unique_ptr<SNode> && next)
			:data(std::forward<T>(data))
			,prev(prev)
			,next(std::move(next))
		{

		}

		std::string data;
		SNode * prev;
		std::unique_ptr<SNode> next;
	};

public:
	CStringList() = default;
	~CStringList();

	CStringList(const CStringList & list);
	CStringList(CStringList && list);
	CStringList(const std::initializer_list<std::string> & il);
	explicit CStringList(const size_t n);
	CStringList(const size_t n, const std::string & value);
	CStringList & operator=(const CStringList & list);
	CStringList & operator=(CStringList && list);
	CStringList & operator=(const std::initializer_list<std::string> & il);

	class CIterator
	{
		friend CStringList;

		CIterator(SNode * node, bool isReverse = false)
			:m_pNode(node)
			,m_isReverse(isReverse)
		{

		}

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef std::string value_type;
		typedef ptrdiff_t difference_type;
		typedef std::string * pointer;
		typedef std::string & reference;

		CIterator() = delete;

		std::string & operator*() const
		{
			assert(this->m_pNode);
			return m_pNode->data;
		}

		CIterator & operator--()
		{
			m_pNode = (!m_isReverse) ? (m_pNode->prev) : (m_pNode->next.get());
			return *this;
		}

		CIterator & operator++()
		{
			m_pNode = (!m_isReverse) ? (m_pNode->next.get()) : (m_pNode->prev);
			return *this;
		}

		CIterator operator--(int)
		{
			auto copy = *this;
			--*this;
			return copy;
		}

		CIterator operator++(int)
		{
			auto copy = *this;
			++*this;
			return copy;
		}

		bool operator==(const CIterator & it) const
		{
			return (m_pNode == it.m_pNode);
		}

		bool operator!=(const CIterator & it) const
		{
			return (m_pNode != it.m_pNode);
		}

		SNode * operator->() const
		{
			return m_pNode;
		}

	private:
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
	void push_back(std::string && data);

	void push_front(const std::string & data);
	void push_front(std::string && data);

	void insert(const CIterator & it, const std::string & data);
	void insert(const CIterator & it, std::string && data);
	void insert(const CIterator & it, const size_t n, const std::string & data);
	void insert(const CIterator & it, const std::initializer_list<std::string> & il);
	void insert(const CIterator & insIt,
	            const CIterator & first, const CIterator & last);

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

	void resize(const size_t n);
	void resize(const size_t n, const std::string & value);

	void swap(CStringList & list);

private:
	size_t m_size = 0;
	std::unique_ptr<SNode> m_firstNode;
	SNode * m_lastNode = nullptr;
};

bool operator==(const CStringList & lhs, const CStringList & rhs);
bool operator!=(const CStringList & lhs, const CStringList & rhs);
