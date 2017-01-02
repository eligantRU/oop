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

CStringList::CIterator CStringList::begin()
{
	return CIterator(m_firstNode.get());
}

std::string & CStringList::back()
{
	assert(m_lastNode);
	return m_lastNode->data;
}

std::string const & CStringList::back() const
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
