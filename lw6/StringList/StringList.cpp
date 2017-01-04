#include "stdafx.h"

#include "StringList.h"

CStringList::SNode::SNode(const std::string & data, SNode * prev, std::unique_ptr<SNode> && next)
	:data(data)
	,prev(prev)
	,next(std::move(next))
{

}

CStringList::CIterator::CIterator(SNode * node, bool isReverse)
	:m_pNode(node)
	,m_isReverse(isReverse)
{

}

std::string & CStringList::CIterator::operator*() const
{
	return m_pNode->data;
}

CStringList::SNode * CStringList::CIterator::operator->() const
{
	return m_pNode;
}

CStringList::CIterator & CStringList::CIterator::operator--()
{
	m_pNode = (!m_isReverse) ? (m_pNode->prev) : (m_pNode->next.get());
	return *this;
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_pNode = (!m_isReverse) ? (m_pNode->next.get()) : (m_pNode->prev);
	return *this;
}

bool CStringList::CIterator::operator==(const CStringList::CIterator & it) const
{
	return (m_pNode == it.m_pNode);
}

bool CStringList::CIterator::operator!=(const CStringList::CIterator & it) const
{
	return (m_pNode != it.m_pNode);
}

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	if (empty())
	{
		return begin();
	}
	return CIterator(m_lastNode->next.get());
}

const CStringList::CIterator CStringList::begin() const
{
	return CIterator(m_firstNode.get());
}

const CStringList::CIterator CStringList::end() const
{
	if (empty())
	{
		return begin();
	}
	return CIterator(m_lastNode->next.get());
}

const CStringList::CIterator CStringList::cbegin() const
{
	return CIterator(m_firstNode.get());
}

const CStringList::CIterator CStringList::cend() const
{
	if (empty())
	{
		return cbegin();
	}
	return CIterator(m_lastNode->next.get());
}

CStringList::CIterator CStringList::rbegin()
{
	return CIterator(m_lastNode, true);
}

CStringList::CIterator CStringList::rend()
{
	return CIterator(m_firstNode->prev, true);
}

const CStringList::CIterator CStringList::rbegin() const
{
	return CIterator(m_lastNode, true);
}

const CStringList::CIterator CStringList::rend() const
{
	return CIterator(m_firstNode->prev, true);
}

const CStringList::CIterator CStringList::crbegin() const
{
	return CIterator(m_lastNode, true);
}

const CStringList::CIterator CStringList::crend() const
{
	return CIterator(m_firstNode->prev, true);
}

CStringList::CStringList(const CStringList & list)
{
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		push_back(*it);
	}
}

CStringList::CStringList(CStringList && list)
{
	m_size = list.m_size;
	m_firstNode = std::move(list.m_firstNode);
	m_lastNode = std::move(list.m_lastNode);

	list.m_size = 0;
	list.m_lastNode = nullptr;
}

CStringList::CStringList(std::initializer_list<std::string> initList)
{
	for (const auto element : initList)
	{
		push_back(element);
	}
}

CStringList::CStringList(const size_t n)
{
	for (size_t i = 0; i < n; ++i)
	{
		push_back(std::string());
	}
}

CStringList::CStringList(const size_t n, const std::string & value)
{
	for (size_t i = 0; i < n; ++i)
	{
		push_back(value);
	}
}

CStringList & CStringList::operator=(const CStringList & list)
{
	clear();
	
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		push_back(*it);
	}
	return *this;
}

CStringList & CStringList::operator=(CStringList && list)
{
	clear();

	m_size = list.m_size;
	m_firstNode = std::move(list.m_firstNode);
	m_lastNode = std::move(list.m_lastNode);

	list.m_size = 0;
	list.m_lastNode = nullptr;

	return *this;
}

CStringList & CStringList::operator=(const std::initializer_list<std::string> & initList)
{
	clear();

	for (const auto element : initList)
	{
		push_back(element);
	}
	return *this;
}

size_t CStringList::size() const
{
	return m_size;
}

size_t CStringList::max_size() const
{
	return std::numeric_limits<size_t>::max();
}

bool CStringList::empty() const
{
	return (m_size == 0);
}

void CStringList::clear()
{
	m_firstNode = nullptr;
	m_lastNode = nullptr;
	m_size = 0;
}

void CStringList::pop_front()
{
	erase(begin());
}

void CStringList::pop_back()
{
	m_lastNode = m_lastNode->prev;
	m_lastNode->next = nullptr;
	--m_size;
}

void CStringList::append(const std::string & data)
{
	auto newNode = std::make_unique<SNode>(data, m_lastNode, nullptr);
	SNode * newLastNode = newNode.get();
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

void CStringList::append(std::string && data)
{
	auto newNode = std::make_unique<SNode>(std::move(data), m_lastNode, nullptr);
	SNode * newLastNode = newNode.get();
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

void CStringList::push_back(const std::string & data)
{
	append(data);
}

void CStringList::push_front(const std::string & data)
{
	if (empty())
	{
		append(data);
	}
	else
	{
		auto secondNode = std::move(m_firstNode);
		m_firstNode = std::make_unique<SNode>(data, nullptr, std::move(secondNode));
		++m_size;
	}
}

void CStringList::push_back(std::string && data)
{
	append(std::move(data));
}

void CStringList::push_front(std::string && data)
{
	if (empty())
	{
		append(std::move(data));
	}
	else
	{
		auto secondNode = std::move(m_firstNode);
		m_firstNode = std::make_unique<SNode>(std::move(data), nullptr, std::move(secondNode));
		++m_size;
	}
}

void CStringList::insert(const CIterator & it, const std::string & data)
{
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
		auto newNode = std::make_unique<SNode>(data, it->prev, std::move(it->prev->next));
		it->prev = std::move(newNode.get());
		newNode->prev->next = std::move(newNode);
		++m_size;
	}
}

void CStringList::insert(const CIterator & it, std::string && data)
{
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
		auto newNode = std::make_unique<SNode>(std::move(data), it->prev, std::move(it->prev->next));
		it->prev = std::move(newNode.get());
		newNode->prev->next = std::move(newNode);
		++m_size;
	}
}

void CStringList::insert(const CIterator & it, const size_t n, const std::string & data)
{
	for (size_t i = 0; i < n; ++i)
	{
		insert(it, data);
	}
}

void CStringList::insert(const CIterator & it, const std::initializer_list<std::string> & il)
{
	for (const auto &el : il)
	{
		insert(it, el);
	}
}

void CStringList::insert(const CIterator & insIt, const CIterator & first, const CIterator & last)
{
	for (auto it = first; it != last; ++it)
	{
		insert(insIt, *it);
	}
}

void CStringList::erase(const CIterator & it)
{
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
		m_lastNode = std::move(it->prev);
		m_lastNode->next = nullptr;
	}
	else
	{
		it->next->prev = std::move(it->prev);
		it->prev->next = std::move(it->next);
	}
	--m_size;
}

void CStringList::erase(const CIterator & first, const CIterator & last)
{
	auto it = first;
	while (it != last)
	{
		if (it == begin())
		{
			erase(it);
			it = begin();
		}
		else
		{
			auto bla = it;
			--bla;
			erase(it);
			it = bla;
			++it;
		}
	}
}

std::string & CStringList::front()
{
	assert(m_lastNode);
	return m_firstNode->data;
}

const std::string & CStringList::front() const
{
	assert(m_lastNode);
	return m_firstNode->data;
}

std::string & CStringList::back()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

const std::string & CStringList::back() const
{
	assert(m_lastNode);
	return m_lastNode->data;
}

void CStringList::remove(const std::string & value)
{
	for (auto it = begin(); !empty() && (it != end());)
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

void CStringList::resize(const size_t n)
{
	if (n >= m_size)
	{
		insert(end(), n - m_size, std::string());
	}
	else
	{
		while (m_size != n)
		{
			erase(rbegin());
		}
	}
}

void CStringList::resize(const size_t n, const std::string & value)
{
	if (n >= m_size)
	{
		insert(end(), n - m_size, value);
	}
	else
	{
		while (m_size != n)
		{
			erase(rbegin());
		}
	}
}

void CStringList::swap(CStringList & list)
{
	std::swap(list, *this);
}

bool operator==(CStringList & lhs, CStringList & rhs)
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

bool operator!=(CStringList & lhs, CStringList & rhs)
{
	return !(lhs == rhs);
}
