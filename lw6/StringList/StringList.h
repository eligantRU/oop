#pragma once

#include <memory>
#include <string>
#include <assert.h>

class CStringList
{
	template <class T>
	struct SNode
	{
		template <class T>
		SNode(T && data, SNode * prev, std::unique_ptr<SNode> && next)
			:data(std::forward<T>(data))
			,prev(prev)
			,next(std::move(next))
		{

		}

		T data;
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

	template <class T>
	class CIterator
	{
		friend CStringList;

		CIterator(SNode<std::string> * node, bool isReverse = false)
			:m_pNode(node)
			,m_isReverse(isReverse)
		{

		}

	public:
		typedef std::bidirectional_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T * pointer;
		typedef T & reference;

		CIterator() = delete;

		std::string & CIterator<std::string>::operator*() const
		{
			assert(this->m_pNode);
			return m_pNode->data;
		}

		CIterator<std::string> & operator--()
		{
			m_pNode = (!m_isReverse) ? (m_pNode->prev) : (m_pNode->next.get());
			return *this;
		}

		CIterator<std::string> & operator++()
		{
			m_pNode = (!m_isReverse) ? (m_pNode->next.get()) : (m_pNode->prev);
			return *this;
		}

		CIterator<std::string> operator--(int)
		{
			auto copy = *this;
			--*this;
			return copy;
		}

		CIterator<std::string> operator++(int)
		{
			auto copy = *this;
			++*this;
			return copy;
		}

		bool CIterator<std::string>::operator==(const CIterator<std::string> & it) const
		{
			return (m_pNode == it.m_pNode);
		}

		bool CIterator<std::string>::operator!=(const CIterator<std::string> & it) const
		{
			return (m_pNode != it.m_pNode);
		}

		SNode<std::string> * CIterator<std::string>::operator->() const
		{
			return m_pNode;
		}

	private:
		SNode<std::string> * m_pNode = nullptr;
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

	void insert(const CIterator<std::string> & it, const std::string & data);
	void insert(const CIterator<std::string> & it, std::string && data);
	void insert(const CIterator<std::string> & it, const size_t n, const std::string & data);
	void insert(const CIterator<std::string> & it, const std::initializer_list<std::string> & il);
	void insert(const CIterator<std::string> & insIt,
	            const CIterator<std::string> & first, const CIterator<std::string> & last);

	void erase(const CIterator<std::string> & it);
	void erase(const CIterator<std::string> & first, const CIterator<std::string> & last);

	void pop_front();
	void pop_back();

	CIterator<std::string> begin();
	CIterator<std::string> end();

	const CIterator<std::string> begin() const;
	const CIterator<std::string> end() const;

	const CIterator<std::string> cbegin() const;
	const CIterator<std::string> cend() const;

	CIterator<std::string> rbegin();
	CIterator<std::string> rend();

	const CIterator<std::string> rbegin() const;
	const CIterator<std::string> rend() const;

	const CIterator<std::string> crbegin() const;
	const CIterator<std::string> crend() const;

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
	std::unique_ptr<SNode<std::string>> m_firstNode;
	SNode<std::string> * m_lastNode = nullptr;
};

bool operator==(const CStringList & lhs, const CStringList & rhs);
bool operator!=(const CStringList & lhs, const CStringList & rhs);
