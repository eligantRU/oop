#include "stdafx.h"

#include "SolidShape.h"

namespace
{

static const unsigned PRECISION = 1;

}

CSolidShape::CSolidShape(const std::string & type,
                         const std::string & outlineColor, const std::string & fillColor)
	:m_type(type)
	,m_fillColor(fillColor)
{
	SetOutlineColor(outlineColor);
}

void CSolidShape::SetFillColor(const std::string & color)
{
	m_fillColor = color;
}

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

void CSolidShape::SetOutlineColor(const std::string & color)
{
	CShape::SetOutlineColor(color);
}

std::string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}

std::string CSolidShape::ToString() const
{
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(PRECISION);
	stream << m_type << ": "
	       << GetArea() << " "
	       << GetPerimeter() << " "
	       << GetOutlineColor() << " "
	       << GetFillColor() << " ";
	AppendProperties(stream);
	return stream.str();
}
