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
	void CreateLineSegment(const std::vector<std::string> & commands);
	void CreateTriangle(const std::vector<std::string> & commands);
	void CreateRectangle(const std::vector<std::string> & commands);
	void CreateCircle(const std::vector<std::string> & commands);
	void DeleteShapes();
	void PrintShapesInfo(std::ostream & stream) const;

	std::vector<std::unique_ptr<CShape>> m_shapes;

	class CFactory;
	std::unique_ptr<CFactory> m_pFactory;
};
