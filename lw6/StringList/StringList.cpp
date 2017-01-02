#include "stdafx.h"

#include "StringList.h"

CStringList::Node::Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
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

CStringList & CStringList::operator=(std::initializer_list<std::string> initList)
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
	m_firstNode = nullptr; // because of unique pointers
	m_lastNode = nullptr;
	m_size = 0;
}

void CStringList::append(const std::string & data)
{
	auto newNode = std::make_unique<Node>(data, m_lastNode, nullptr);
	Node *newLastNode = newNode.get();
	if (m_lastNode)
	{
		m_lastNode->next = move(newNode);
	}
	else // empty list
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
		m_firstNode = std::make_unique<Node>(data, nullptr, std::move(secondNode));
		
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
		auto newNode = std::make_unique<Node>(data, it->prev, std::move(it->prev->next));
		it->prev = std::move(newNode.get());
		newNode->prev->next = std::move(newNode);
		++m_size;
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
	else if (it.m_node == m_lastNode)
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

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

CStringList::CIterator CStringList::end()
{
	return CIterator(m_lastNode->next.get());
}

const CStringList::CIterator CStringList::begin() const
{
	return CIterator(m_firstNode.get());
}

const CStringList::CIterator CStringList::end() const
{
	return CIterator(m_lastNode->next.get());
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

CStringList::CIterator::CIterator(Node * node)
	:m_node(node)
{

}

std::string & CStringList::CIterator::operator*() const
{
	return m_node->data;
}

CStringList::Node * CStringList::CIterator::operator->() const
{
	return m_node;
}

CStringList::CIterator & CStringList::CIterator::operator--()
{
	m_node = m_node->prev;
	return *this;
}

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}

bool CStringList::CIterator::operator==(const CStringList::CIterator & it) const
{
	return (m_node == it.m_node);
}

bool CStringList::CIterator::operator!=(const CStringList::CIterator & it) const
{
	return (m_node != it.m_node);
}
