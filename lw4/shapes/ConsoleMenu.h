#pragma once

#include "Shape.h"
#include <vector>

class CConsoleMenu
{
public:
	CConsoleMenu();
	~CConsoleMenu();

	void DoCommand(const std::string & commandLine);

private:
	std::vector<std::unique_ptr<CShape>> m_shapes;

	class CFactory;
	std::unique_ptr<CFactory> m_pFactory;
};
