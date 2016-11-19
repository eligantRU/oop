#include "stdafx.h"

#include "Circle.h"
#include <iomanip>

namespace
{

static const unsigned PRECISION = 1;

}

CCircle::CCircle(const CPoint & center, const double radius,
                 const std::string & outlineColor, const std::string & fillColor)
	:m_center(center)
	,m_radius(radius)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Circle-radius must be not-negative");
	}
	m_outlineColor = outlineColor;
	m_fillColor = fillColor;
}

CPoint CCircle::GetCenter() const
{
	return m_center;
}

double CCircle::GetRadius() const
{
	return m_radius;
}

double CCircle::GetPerimeter() const
{
	return 2 * M_PI * m_radius;
}

double CCircle::GetArea() const
{
	return M_PI * pow(m_radius, 2);
}

std::string CCircle::ToString() const
{
	std::stringstream buffer;
	buffer << std::fixed << std::setprecision(PRECISION);
	buffer << "circle "
	       << m_center.x << " " << m_center.y << " "
	       << m_radius << " "
	       << GetOutlineColor() << " "
	       << GetFillColor();
	return buffer.str();
}
