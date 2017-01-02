#pragma once

#include <string>
#include <memory>

class CStringList
{
	struct Node
	{
		Node(const std::string & data, Node * prev, std::unique_ptr<Node> && next);
		std::string data;
		Node * prev;
		std::unique_ptr<Node> next;
	};

public:
	class CIterator
	{
		friend CStringList;
		CIterator(Node * node);
	public:
		CIterator() = default;
		std::string & operator*() const;
		CIterator & operator++();
	private:
		Node * m_node = nullptr;
	};

	void clear();

	size_t size() const;
	bool empty() const;

	void append(const std::string & data);
	void push_back(const std::string & data);
	void push_front(const std::string & data);

	CIterator begin();

	std::string & front();
	const std::string & front() const;

	std::string & back();
	const std::string & back() const;

private:
	size_t m_size = 0;
	std::unique_ptr<Node> m_firstNode;
	Node * m_lastNode = nullptr;
};
