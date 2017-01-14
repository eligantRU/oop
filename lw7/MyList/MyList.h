#pragma once

#include <memory>
#include <assert.h>

template <class T>
class CMyList
{
	template <class T>
	struct SNode
	{
		SNode(const T & data, SNode * prev, std::unique_ptr<SNode> && next)
			:data(data)
			,prev(prev)
			,next(std::move(next))
		{

		}

		SNode(const T && data, SNode * prev, std::unique_ptr<SNode> && next)
			:data(std::move(data))
			,prev(prev)
			,next(std::move(next))
		{

		}

		T data;
		SNode * prev;
		std::unique_ptr<SNode> next;
	};

public:
	CMyList() = default;
	~CMyList() = default;
	
	CMyList(const CMyList & list)
	{
		insert(begin(), list.begin(), list.end());
	}

	CMyList(CMyList && list)
	{
		m_size = list.m_size;
		m_firstNode = std::move(list.m_firstNode);
		m_lastNode = list.m_lastNode;

		list.m_size = 0;
	}

	CMyList(const std::initializer_list<T> & il)
	{
		for (const auto & element : il)
		{
			push_back(element);
		}
	}

	explicit CMyList(const size_t n)
		:CMyList(n, T())
	{

	}

	CMyList(const size_t n, const T & value)
	{
		insert(begin(), n, value);
	}

	CMyList & operator=(const CMyList & list)
	{
		clear();
		insert(begin(), list.begin(), list.end());
		return *this;
	}

	CMyList & operator=(CMyList && list)
	{
		clear();
		m_size = list.m_size;
		m_firstNode = std::move(list.m_firstNode);
		m_lastNode = list.m_lastNode;
		list.m_size = 0;
		return *this;
	}

	CMyList & operator=(const std::initializer_list<T> & initList)
	{
		clear();
		for (const auto element : initList)
		{
			push_back(element);
		}
		return *this;
	}

	template <class T>
	class CIterator
	{
		friend CMyList;
		CIterator::CIterator(SNode<T> * node, bool isReverse = false)
			:m_pNode(node)
			,m_isReverse(isReverse)
		{

		}

	public:
		CIterator() = delete;

		T & CIterator::operator*() const
		{
			assert(this->m_pNode);
			return m_pNode->data;
		}

		CIterator<T> & operator--()
		{
			m_pNode = (!m_isReverse) ? (m_pNode->prev) : (m_pNode->next.get());
			return *this;
		}

		CIterator<T> & operator++()
		{
			m_pNode = (!m_isReverse) ? (m_pNode->next.get()) : (m_pNode->prev);
			return *this;
		}

		bool CIterator::operator==(const CIterator & it) const
		{
			return (m_pNode == it.m_pNode);
		}

		bool CIterator::operator!=(const CIterator & it) const
		{
			return (m_pNode != it.m_pNode);
		}

	private:
		SNode<T> * CIterator::operator->() const
		{
			return m_pNode;
		}

		SNode<T> * m_pNode = nullptr;
		bool m_isReverse;
	};

	void clear()
	{
		m_firstNode = nullptr;
		m_lastNode = nullptr;
		m_size = 0;
	}

	size_t size() const
	{
		return m_size;
	}

	size_t max_size() const
	{
		return std::numeric_limits<size_t>::max();
	}

	bool empty() const
	{
		return (m_size == 0);
	}

	void append(const T & data)
	{
		assert(size() + 1 <= max_size());
		auto newNode = std::make_unique<SNode<T>>(data, m_lastNode, nullptr);
		auto * newLastNode = newNode.get();
		if (m_lastNode)
		{
			m_lastNode->next = move(newNode);
		}
		else
		{
			m_firstNode = move(newNode);
		}
		m_lastNode = newLastNode;
		++m_size;
	}

	void append(T && data)
	{
		assert(size() + 1 <= max_size());
		auto newNode = std::make_unique<SNode<T>>(std::move(data), m_lastNode, nullptr);
		auto * newLastNode = newNode.get();
		if (m_lastNode)
		{
			m_lastNode->next = std::move(newNode);
		}
		else
		{
			m_firstNode = std::move(newNode);
		}
		m_lastNode = newLastNode;
		++m_size;
	}

	void push_back(const T & data)
	{
		assert(size() + 1 <= max_size());
		append(data);
	}

	void push_front(const T & data)
	{
		assert(size() + 1 <= max_size());
		if (empty())
		{
			append(data);
		}
		else
		{
			auto secondNode = std::move(m_firstNode);
			m_firstNode = std::make_unique<SNode<T>>(data, nullptr, std::move(secondNode));
			++m_size;
		}
	}

	void push_back(T && data)
	{
		assert(size() + 1 <= max_size());
		append(std::move(data));
	}

	void push_front(T && data)
	{
		assert(size() + 1 <= max_size());
		if (empty())
		{
			append(std::move(data));
		}
		else
		{
			auto secondNode = std::move(m_firstNode);
			m_firstNode = std::make_unique<SNode<T>>(std::move(data), nullptr, std::move(secondNode));
			++m_size;
		}
	}

	void insert(const CIterator<T> & it, const T & data)
	{
		assert(size() + 1 <= max_size());
		if (it == begin())
		{
			push_front(data);
		}
		else if (it == end())
		{
			push_back(data);
		}
		else
		{
			auto newNode = std::make_unique<SNode<T>>(data, it->prev, std::move(it->prev->next));
			it->prev = std::move(newNode.get());
			newNode->prev->next = std::move(newNode);
			++m_size;
		}
	}

	void insert(const CIterator<T> & it, T && data)
	{
		assert(size() + 1 <= max_size());
		if (it == begin())
		{
			push_front(std::move(data));
		}
		else if (it == end())
		{
			push_back(std::move(data));
		}
		else
		{
			auto newNode = std::make_unique<SNode<T>>(std::move(data), it->prev, std::move(it->prev->next));
			it->prev = std::move(newNode.get());
			newNode->prev->next = std::move(newNode);
			++m_size;
		}
	}

	void insert(const CIterator<T> & it, const size_t n, const T & data)
	{
		assert(size() + n <= max_size());
		for (size_t i = 0; i < n; ++i)
		{
			insert(it, data);
		}
	}

	void insert(const CIterator<T> & it, const std::initializer_list<T> & il)
	{
		assert(size() + il.size() <= max_size());
		for (const auto & el : il)
		{
			insert(it, el);
		}
	}

	void insert(const CIterator<T> & insIt, const CIterator<T> & first, const CIterator<T> & last)
	{
		for (auto it = first; it != last; ++it)
		{
			assert(size() + 1 <= max_size());
			insert(insIt, *it);
		}
	}

	void erase(const CIterator<T> & it)
	{
		assert(size() > 0);
		if (m_size == 1)
		{
			clear();
			return;
		}
		else if (it == begin())
		{
			m_firstNode = std::move(m_firstNode->next);
			m_firstNode->prev = nullptr;
		}
		else if (it.m_pNode == m_lastNode)
		{
			m_lastNode = it->prev;
			m_lastNode->next = nullptr;
		}
		else
		{
			it->next->prev = it->prev;
			it->prev->next = std::move(it->next);
		}
		--m_size;
	}

	void erase(const CIterator<T> & first, const CIterator<T> & last)
	{
		auto it = first;
		while (it != last)
		{
			assert(size() > 0);
			if (it == begin())
			{
				erase(it);
				it = begin();
			}
			else
			{
				auto beforeIt = it;
				--beforeIt;
				erase(it);
				it = beforeIt;
				++it;
			}
		}
	}

	void pop_front()
	{
		erase(begin());
	}

	void pop_back()
	{
		erase(rbegin());
	}

	CIterator<T> begin()
	{
		return CIterator<T>(m_firstNode.get());
	}

	CIterator<T> end()
	{
		if (empty())
		{
			return begin();
		}
		return CIterator<T>(m_lastNode->next.get());
	}

	const CIterator<T> begin() const
	{
		return CIterator<T>(m_firstNode.get());
	}

	const CIterator<T> end() const
	{
		if (empty())
		{
			return begin();
		}
		return CIterator<T>(m_lastNode->next.get());
	}

	const CIterator<T> cbegin() const
	{
		return CIterator<T>(m_firstNode.get());
	}

	const CIterator<T> cend() const
	{
		if (empty())
		{
			return cbegin();
		}
		return CIterator<T>(m_lastNode->next.get());
	}

	CIterator<T> rbegin()
	{
		if (empty())
		{
			return CIterator<T>(m_firstNode.get(), true);
		}
		return CIterator<T>(m_lastNode, true);
	}

	CIterator<T> rend()
	{
		if (empty())
		{
			return rbegin();
		}
		return CIterator<T>(m_firstNode->prev, true);
	}

	const CIterator<T> rbegin() const
	{
		if (empty())
		{
			return CIterator<T>(m_firstNode.get(), true);
		}
		return CIterator<T>(m_lastNode, true);
	}

	const CIterator<T> rend() const
	{
		if (empty())
		{
			return rbegin();
		}
		return CIterator<T>(m_firstNode->prev, true);
	}

	const CIterator<T> crbegin() const
	{
		if (empty())
		{
			return CIterator<T>(m_firstNode.get(), true);
		}
		return CIterator<T>(m_lastNode, true);
	}

	const CIterator<T> crend() const
	{
		if (empty())
		{
			return crbegin();
		}
		return CIterator<T>(m_firstNode->prev, true);
	}

	T & front()
	{
		assert(m_firstNode);
		return m_firstNode->data;
	}

	const T & front() const
	{
		assert(m_firstNode);
		return m_firstNode->data;
	}

	T & back()
	{
		assert(m_lastNode);
		return m_lastNode->data;
	}

	const T & back() const
	{
		assert(m_lastNode);
		return m_lastNode->data;
	}

	void remove(const T & value)
	{
		for (auto it = begin(); it != end();)
		{
			if (*it != value)
			{
				++it;
			}
			else
			{
				if (it == begin())
				{
					erase(it);
					it = begin();
				}
				else
				{
					auto last = it;
					--last;
					erase(it);
					it = last;
				}
			}
		}
	}

	void resize(const size_t n)
	{
		if (n >= m_size)
		{
			insert(end(), n - m_size, T());
		}
		else
		{
			while (m_size != n)
			{
				assert(size() > 0);
				erase(rbegin());
			}
		}
	}

	void resize(const size_t n, const T & value)
	{
		if (n >= m_size)
		{
			insert(end(), n - m_size, value);
		}
		else
		{
			while (m_size != n)
			{
				assert(size() > 0);
				erase(rbegin());
			}
		}
	}

	void swap(CMyList & list)
	{
		std::swap(list, *this);
	}

private:
	size_t m_size = 0;
	std::unique_ptr<SNode<T>> m_firstNode;
	SNode<T> * m_lastNode = nullptr;
};

template <class T>
bool operator==(const CMyList<T> & lhs, const CMyList<T> & rhs)
{
	if (lhs.size() == rhs.size())
	{
		auto itr = rhs.begin();
		for (auto itl = lhs.begin(); itl != lhs.end(); ++itl, ++itr)
		{
			if (*itl != *itr)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

template <class T>
bool operator!=(const CMyList<T> & lhs, const CMyList<T> & rhs)
{
	return !(lhs == rhs);
}