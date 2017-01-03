#include "stdafx.h"

#include "StringList.h"

CStringList::SNode::SNode(const std::string & data, SNode * prev, std::unique_ptr<SNode> && next)
	:data(data), prev(prev), next(std::move(next))
{

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

void CStringList::insert(const CStringListIterator & it, const std::string & data)
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

void CStringList::erase(const CStringListIterator & it)
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

CStringList::CStringListIterator::CStringListIterator(SNode * node, bool isReverse)
	:m_pNode(node)
	,m_isReverse(isReverse)
{

}

std::string & CStringList::CStringListIterator::operator*() const
{
	return m_pNode->data;
}

CStringList::SNode * CStringList::CStringListIterator::operator->() const
{
	return m_pNode;
}

CStringList::CStringListIterator & CStringList::CStringListIterator::operator--()
{
	m_pNode = (!m_isReverse) ? (m_pNode->prev) : (m_pNode->next.get());
	return *this;
}

CStringList::CStringListIterator & CStringList::CStringListIterator::operator++()
{
	m_pNode = (!m_isReverse) ? (m_pNode->next.get()) : (m_pNode->prev);
	return *this;
}

bool CStringList::CStringListIterator::operator==(const CStringList::CStringListIterator & it) const
{
	return (m_pNode == it.m_pNode);
}

bool CStringList::CStringListIterator::operator!=(const CStringList::CStringListIterator & it) const
{
	return (m_pNode != it.m_pNode);
}


CStringList::CStringListIterator CStringList::begin()
{
	return CStringListIterator(m_firstNode.get());
}

CStringList::CStringListIterator CStringList::end()
{
	return CStringListIterator(m_lastNode->next.get());
}

const CStringList::CStringListIterator CStringList::begin() const
{
	return CStringListIterator(m_firstNode.get());
}

const CStringList::CStringListIterator CStringList::end() const
{
	return CStringListIterator(m_lastNode->next.get());
}

const CStringList::CStringListIterator CStringList::cbegin() const
{
	return CStringListIterator(m_firstNode.get());
}

const CStringList::CStringListIterator CStringList::cend() const
{
	return CStringListIterator(m_lastNode->next.get());
}

CStringList::CStringListIterator CStringList::rbegin()
{
	return CStringListIterator(m_lastNode, true);
}

CStringList::CStringListIterator CStringList::rend()
{
	return CStringListIterator(m_firstNode->prev, true);
}

const CStringList::CStringListIterator CStringList::rbegin() const
{
	return CStringListIterator(m_lastNode, true);
}

const CStringList::CStringListIterator CStringList::rend() const
{
	return CStringListIterator(m_firstNode->prev, true);
}

const CStringList::CStringListIterator CStringList::crbegin() const
{
	return CStringListIterator(m_lastNode, true);
}

const CStringList::CStringListIterator CStringList::crend() const
{
	return CStringListIterator(m_firstNode->prev, true);
}
