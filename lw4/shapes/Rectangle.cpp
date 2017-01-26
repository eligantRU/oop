#include "stdafx.h"

#include "Rectangle.h"
#include <iomanip>

namespace
{

static const unsigned PRECISION = 1;

}

CRectangle::CRectangle(const CPoint & leftTop, const CPoint & rightBottom,
                       const std::string & outlineColor, const std::string & fillColor)
	:CSolidShape("rectangle", outlineColor, fillColor)
	,m_leftTopVertex(leftTop)
	,m_rightBottomVertex(rightBottom)
{
	if (leftTop.x > rightBottom.x)
	{
		throw std::invalid_argument("Rectangle must have left vertex more less than right by Ox");
	}
	if (leftTop.y < rightBottom.y)
	{
		throw std::invalid_argument("Rectangle must have left vertex larger than right by Oy");
	}
}

CPoint CRectangle::GetLeftTop() const
{
	return m_leftTopVertex;
}

CPoint CRectangle::GetRightBottom() const
{
	return m_rightBottomVertex;
}

double CRectangle::GetWidth() const
{
	return m_rightBottomVertex.x - m_leftTopVertex.x;
}

double CRectangle::GetHeight() const
{
	return m_leftTopVertex.y - m_rightBottomVertex.y;
}

double CRectangle::GetPerimeter() const
{
	return 2 * (GetWidth() + GetHeight());
}

double CRectangle::GetArea() const
{
	return GetWidth() * GetHeight();
}

void CRectangle::AppendProperties(std::ostream & stream) const
{
	stream << std::fixed << std::setprecision(PRECISION);

	stream << m_leftTopVertex.x << " " << m_leftTopVertex.y << " "
	       << m_rightBottomVertex.x << " " << m_rightBottomVertex.y << std::endl;
}
