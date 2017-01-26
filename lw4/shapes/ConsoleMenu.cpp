#include "stdafx.h"

#include "ConsoleMenu.h"
#include "LineSegment.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Circle.h"

class CConsoleMenu::CFactory
{
public:
	std::unique_ptr<CShape> CreateLineSegment(const std::vector<std::string> & params) const
	{
		if (params.size() != 6)
		{
			throw std::runtime_error("Incorrect number of arguments");
		}
		return std::make_unique<CLineSegment>(
			CPoint(stod(params[1]), stod(params[2])),
			CPoint(stod(params[3]), stod(params[4])),
			params[5]
		);
	}

	std::unique_ptr<CShape> CreateTriangle(const std::vector<std::string> & params) const
	{
		if (params.size() != 9)
		{
			throw std::runtime_error("Incorrect number of arguments");
		}
		return std::make_unique<CTriangle>(
			CPoint(stod(params[1]), stod(params[2])),
			CPoint(stod(params[3]), stod(params[4])),
			CPoint(stod(params[5]), stod(params[6])),
			params[7], params[8]
		);
	}

	std::unique_ptr<CShape> CreateRectangle(const std::vector<std::string> & params) const
	{
		if (params.size() != 7)
		{
			throw std::runtime_error("Incorrect number of arguments");
		}
		return std::make_unique<CRectangle>(
			CPoint(stod(params[1]), stod(params[2])),
			CPoint(stod(params[3]), stod(params[4])),
			params[5], params[6]
		);
	}

	std::unique_ptr<CShape> CreateCircle(const std::vector<std::string> & params) const
	{
		if (params.size() != 6)
		{
			throw std::runtime_error("Incorrect number of arguments");
		}
		return std::make_unique<CCircle>(
			CPoint(stod(params[1]), stod(params[2])),
			stod(params[3]),
			params[4], params[5]
		);
	}

private:
};

CConsoleMenu::CConsoleMenu()
	:m_pFactory(std::make_unique<CConsoleMenu::CFactory>())
{

}

CConsoleMenu::~CConsoleMenu()
{

}

void CConsoleMenu::DoCommand(const std::string & commandLine)
{
	auto command(commandLine);
	boost::to_upper(command);
	std::vector<std::string> commands;
	boost::split(commands, command, boost::is_any_of(" "));

	if (commands[0] == "LINE_SEGMENT")
	{
		CreateLineSegment(commands);
	} 
	else if (commands[0] == "TRIANGLE")
	{
		CreateTriangle(commands);
	} 
	else if (commands[0] == "RECTANGLE")
	{
		CreateRectangle(commands);
	}
	else if ((commands[0] == "CIRCLE") && (commands.size() == 6))
	{
		CreateCircle(commands);
	}
	else if (commands[0] == "SORT_BY_MAX_AREA")
	{
		std::sort(m_shapes.begin(), m_shapes.end(), [=](const auto & lhs, const auto & rhs) {
			return lhs->GetArea() < rhs->GetArea();
		});
	}
	else if (commands[0] == "SORT_BY_MIN_PERIMETER")
	{
		std::sort(m_shapes.begin(), m_shapes.end(), [](const auto & lhs, const auto & rhs) {
			return lhs->GetPerimeter() > rhs->GetPerimeter();
		});
	}
	else if (commands[0] == "CLEAR")
	{
		DeleteShapes();
	}
	else if (commands[0] == "INFO")
	{
		PrintShapesInfo(std::cout);
	}
	else
	{
		std::cout << "Unknown command" << std::endl;
	}
}

void CConsoleMenu::CreateLineSegment(const std::vector<std::string> & commands)
{
	m_shapes.push_back(m_pFactory->CreateLineSegment(commands));
}

void CConsoleMenu::CreateTriangle(const std::vector<std::string> & commands)
{
	m_shapes.push_back(m_pFactory->CreateTriangle(commands));
}

void CConsoleMenu::CreateRectangle(const std::vector<std::string> & commands)
{
	m_shapes.push_back(m_pFactory->CreateRectangle(commands));
}

void CConsoleMenu::CreateCircle(const std::vector<std::string> & commands)
{
	m_shapes.push_back(m_pFactory->CreateCircle(commands));
}

void CConsoleMenu::DeleteShapes()
{
	m_shapes.clear();
	m_shapes.shrink_to_fit();
}

void CConsoleMenu::PrintShapesInfo(std::ostream & stream) const
{
	for (const auto &shape : m_shapes)
	{
		stream << shape->ToString() << std::endl;
	}
}
