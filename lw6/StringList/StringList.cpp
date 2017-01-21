#include "stdafx.h"

#include "StringList.h"

CStringList::~CStringList()
{
	clear();
}

CStringList::CStringList(const CStringList & list)
{
	CStringList tmp;
	tmp.insert(tmp.begin(), list.begin(), list.end());
	swap(tmp);
}

CStringList::CStringList(CStringList && list)
{
	m_size = list.m_size;
	m_firstNode = std::move(list.m_firstNode);
	m_lastNode = list.m_lastNode;
	list.m_lastNode = nullptr;
	list.m_size = 0;
}

CStringList::CStringList(const std::initializer_list<std::string> & il)
{
	for (const auto & element : il)
	{
		push_back(element);
	}
}

CStringList::CStringList(const size_t n)
	:CStringList(n, std::string())
{

}

CStringList::CStringList(const size_t n, const std::string & value)
{
	insert(begin(), n, value);
}

CStringList & CStringList::operator=(const CStringList & list)
{
	if (list != *this)
	{
		CStringList tmp;
		tmp.insert(tmp.begin(), list.begin(), list.end());
		swap(tmp);
	}
	return *this;
}

CStringList & CStringList::operator=(CStringList && list)
{
	if (list != *this)
	{
		clear();
		m_size = list.m_size;
		m_firstNode = std::move(list.m_firstNode);
		m_lastNode = list.m_lastNode;
		list.m_size = 0;
		list.m_lastNode = nullptr;
	}
	return *this;
}

CStringList & CStringList::operator=(const std::initializer_list<std::string> & il)
{
	clear();
	for (const auto & element : il)
	{
		push_back(element);
	}
	return *this;
}

void CStringList::clear()
{
	erase(begin(), end());
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
	return (size() == 0);
}

void CStringList::append(const std::string & data)
{
	auto newNode = std::make_unique<SNode<std::string>>(data, m_lastNode, nullptr);
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

void CStringList::append(std::string && data)
{
	auto newNode = std::make_unique<SNode<std::string>>(std::move(data), m_lastNode, nullptr);
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

void CStringList::push_back(const std::string & data)
{
	append(data);
}

void CStringList::push_back(std::string && data)
{
	append(std::move(data));
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
		m_firstNode = std::make_unique<SNode<std::string>>(data, nullptr, std::move(secondNode));
		++m_size;
	}
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
		m_firstNode = std::make_unique<SNode<std::string>>(std::move(data), nullptr, std::move(secondNode));
		++m_size;
	}
}

void CStringList::insert(const CIterator<std::string> & it, const std::string & data)
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
		auto newNode = std::make_unique<SNode<std::string>>(data, it->prev, std::move(it->prev->next));
		it->prev = std::move(newNode.get());
		newNode->prev->next = std::move(newNode);
		++m_size;
	}
}

void CStringList::insert(const CIterator<std::string> & it, std::string && data)
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
		auto newNode = std::make_unique<SNode<std::string>>(std::move(data), it->prev, std::move(it->prev->next));
		it->prev = std::move(newNode.get());
		newNode->prev->next = std::move(newNode);
		++m_size;
	}
}

void CStringList::insert(const CIterator<std::string> & it, const size_t n, const std::string & data)
{
	for (size_t i = 0; i < n; ++i)
	{
		insert(it, data);
	}
}

void CStringList::insert(const CIterator<std::string> & it, const std::initializer_list<std::string> & il)
{
	for (const auto & el : il)
	{
		insert(it, el);
	}
}

void CStringList::insert(const CIterator<std::string> & insIt,
                         const CIterator<std::string> & first, const CIterator<std::string> & last)
{
	for (auto it = first; it != last; ++it)
	{
		insert(insIt, *it);
	}
}

void CStringList::erase(const CStringList::CIterator<std::string> & it)
{
	assert(size() > 0);
	if (size() == 1)
	{
		m_firstNode = nullptr;
		m_lastNode = nullptr;
		m_size = 0;
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

void CStringList::erase(const CIterator<std::string> & first, const CIterator<std::string> & last)
{
	auto it = first;
	while (it != last)
	{
		assert(size() > 0);
		erase(it++);
	}
}

void CStringList::pop_front()
{
	erase(begin());
}

void CStringList::pop_back()
{
	erase(rbegin());
}

CStringList::CIterator<std::string> CStringList::begin()
{
	return CIterator<std::string>(m_firstNode.get());
}

CStringList::CIterator<std::string> CStringList::end()
{
	if (empty())
	{
		return begin();
	}
	return CIterator<std::string>(m_lastNode->next.get());
}

const CStringList::CIterator<std::string> CStringList::begin() const
{
	return CIterator<std::string>(m_firstNode.get());
}

const CStringList::CIterator<std::string> CStringList::end() const
{
	if (empty())
	{
		return begin();
	}
	return CIterator<std::string>(m_lastNode->next.get());
}

const CStringList::CIterator<std::string> CStringList::cbegin() const
{
	return CIterator<std::string>(m_firstNode.get());
}

const CStringList::CIterator<std::string> CStringList::cend() const
{
	if (empty())
	{
		return cbegin();
	}
	return CIterator<std::string>(m_lastNode->next.get());
}

CStringList::CIterator<std::string> CStringList::rbegin()
{
	if (empty())
	{
		return CIterator<std::string>(m_firstNode.get(), true);
	}
	return CIterator<std::string>(m_lastNode, true);
}

CStringList::CIterator<std::string> CStringList::rend()
{
	if (empty())
	{
		return rbegin();
	}
	return CIterator<std::string>(m_firstNode->prev, true);
}

const CStringList::CIterator<std::string> CStringList::rbegin() const
{
	if (empty())
	{
		return CIterator<std::string>(m_firstNode.get(), true);
	}
	return CIterator<std::string>(m_lastNode, true);
}

const CStringList::CIterator<std::string> CStringList::rend() const
{
	if (empty())
	{
		return rbegin();
	}
	return CIterator<std::string>(m_firstNode->prev, true);
}

const CStringList::CIterator<std::string> CStringList::crbegin() const
{
	if (empty())
	{
		return CIterator<std::string>(m_firstNode.get(), true);
	}
	return CIterator<std::string>(m_lastNode, true);
}

const CStringList::CIterator<std::string> CStringList::crend() const
{
	if (empty())
	{
		return crbegin();
	}
	return CIterator<std::string>(m_firstNode->prev, true);
}

std::string & CStringList::front()
{
	assert(m_firstNode);
	return m_firstNode->data;
}

const std::string & CStringList::front() const
{
	assert(m_firstNode);
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
	for (auto it = begin(); it != end();)
	{
		if (*it != value)
		{
			++it;
		}
		else
		{
			erase(it++);
		}
	}
}

void CStringList::resize(const size_t n)
{
	if (n >= size())
	{
		insert(end(), n - size(), std::string());
	}
	else
	{
		while (size() != n)
		{
			assert(size() > 0);
			pop_back();
		}
	}
}

void CStringList::resize(const size_t n, const std::string & value)
{
	if (n >= size())
	{
		insert(end(), n - size(), value);
	}
	else
	{
		while (size() != n)
		{
			assert(size() > 0);
			pop_back();
		}
	}
}

void CStringList::swap(CStringList & list)
{
	std::swap(list, *this);
}
bool operator==(const CStringList & lhs, const CStringList & rhs)
{
	if (&lhs == &rhs)
	{
		return true;
	}
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

bool operator!=(const CStringList & lhs, const CStringList & rhs)
{
	return !(lhs == rhs);
}
