#include "stdafx.h"

#include "StringList.h"

CStringList::Node::Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next)
	:data(data), prev(prev), next(std::move(next))
{

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
	m_firstNode = nullptr; // because of std::unique_ptr<std::string>
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

CStringList::CIterator & CStringList::CIterator::operator++()
{
	m_node = m_node->next.get();
	return *this;
}
