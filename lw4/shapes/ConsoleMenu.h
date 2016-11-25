#pragma once

#include <vector>
#include "IShape.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

class CConsoleMenu
{
public:
	CConsoleMenu();
	~CConsoleMenu();

	void DoCommand(const std::string & commandLine);

private:
	std::vector<std::unique_ptr<IShape>> m_shapes;

	class CFactory;
	std::unique_ptr<CFactory> m_pFactory;
};
