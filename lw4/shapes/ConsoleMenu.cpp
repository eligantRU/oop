#include "stdafx.h"

#include "ConsoleMenu.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

class CConsoleMenu::CFactory
{
public:
	auto CreateLineSegment(const CPoint & start, const CPoint & end, 
	                       const std::string & outlineColor) const
	{
		return std::make_unique<CLineSegment>(start, end, outlineColor);
	}

	auto CreateTriangle(const CPoint & vertex1, const CPoint & vertex2, const CPoint & vertex3,
	                    const std::string & outlineColor, const std::string & fillColor) const
	{
		return std::make_unique<CTriangle>(vertex1, vertex2, vertex3, outlineColor, fillColor);
	}

	auto CreateRectangle(const CPoint & leftTop, const CPoint & rightBottom,
	                     const std::string & outlineColor, const std::string & fillColor) const
	{
		return std::make_unique<CRectangle>(leftTop, rightBottom, outlineColor, fillColor);
	}

	auto CreateCircle(const CPoint & center, const double radius,
	                  const std::string & outlineColor, const std::string & fillColor) const
	{
		return std::make_unique<CCircle>(center, radius, outlineColor, fillColor);
	}

private:
};

CConsoleMenu::CConsoleMenu()
	:m_pFactory(new CConsoleMenu::CFactory)
{

}

CConsoleMenu::~CConsoleMenu()
{

}

void CConsoleMenu::DoCommand(std::string & commandLine)
{
	boost::to_upper(commandLine);
	std::vector<std::string> commands;
	boost::split(commands, commandLine, boost::is_any_of(" "));

	if ((commands[0] == "LINE_SEGMENT") && (commands.size() == 6))
	{
		m_shapes.push_back(m_pFactory->CreateLineSegment(
			CPoint(stod(commands[1]), stod(commands[2])),
			CPoint(stod(commands[3]), stod(commands[4])),
			commands[5])
		);
	} 
	else if ((commands[0] == "TRIANGLE") && (commands.size() == 9))
	{
		m_shapes.push_back(m_pFactory->CreateTriangle(
			CPoint(stod(commands[1]), stod(commands[2])),
			CPoint(stod(commands[3]), stod(commands[4])),
			CPoint(stod(commands[5]), stod(commands[6])),
			commands[7], commands[8])
		);
	} 
	else if ((commands[0] == "RECTANGLE") && (commands.size() == 7))
	{
		m_shapes.push_back(m_pFactory->CreateRectangle(
			CPoint(stod(commands[1]), stod(commands[2])),
			CPoint(stod(commands[3]), stod(commands[4])),
			commands[5], commands[6])
		);
	}
	else if ((commands[0] == "CIRCLE") && (commands.size() == 6))
	{
		m_shapes.push_back(m_pFactory->CreateCircle(
			CPoint(stod(commands[1]), stod(commands[2])),
			stod(commands[3]),
			commands[4], commands[5])
		);
	}
	else if (commands[0] == "SORT_BY_MAX_AREA")
	{
		std::sort(m_shapes.begin(), m_shapes.end(), [=](const std::unique_ptr<IShape> & lhs, const std::unique_ptr<IShape> & rhs) {
			return lhs->GetArea() < rhs->GetArea();
		});
	}
	else if (commands[0] == "SORT_BY_MIN_PERIMETER")
	{
		std::sort(m_shapes.begin(), m_shapes.end(), [](const std::unique_ptr<IShape> & lhs, const std::unique_ptr<IShape> & rhs) {
			return lhs->GetPerimeter() > rhs->GetPerimeter();
		});
	}
	else if (commands[0] == "CLEAR")
	{
		m_shapes.clear();
		m_shapes.shrink_to_fit();
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
	}
}
