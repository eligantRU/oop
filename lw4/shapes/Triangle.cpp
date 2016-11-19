#include "stdafx.h"

#include "Triangle.h"
#include <iomanip>

namespace
{

static const unsigned PRECISION = 1;

}

CTriangle::CTriangle(const CPoint & point1, const CPoint & point2, const CPoint & point3,
                     const std::string & outlineColor, const std::string & fillColor)
	:m_vertices({ point1, point2, point3 })
{
	m_outlineColor = outlineColor;
	m_fillColor = fillColor;
}

CPoint CTriangle::GetVertex1() const
{
	return m_vertices[0];
}

CPoint CTriangle::GetVertex2() const
{
	return m_vertices[1];
}

CPoint CTriangle::GetVertex3() const
{
	return m_vertices[2];
}

double CTriangle::GetPerimeter() const
{
	return std::hypotf(m_vertices[0].x - m_vertices[1].x, m_vertices[0].y - m_vertices[1].y)
		+ std::hypotf(m_vertices[1].x - m_vertices[2].x, m_vertices[1].y - m_vertices[2].y)
		+ std::hypotf(m_vertices[0].x - m_vertices[2].x, m_vertices[0].y - m_vertices[2].y);
}

double CTriangle::GetArea() const
{
	auto p = GetPerimeter() / 2;
	auto a = std::hypotf(m_vertices[0].x - m_vertices[1].x, m_vertices[0].y - m_vertices[1].y);
	auto b = std::hypotf(m_vertices[1].x - m_vertices[2].x, m_vertices[1].y - m_vertices[2].y);
	auto c = std::hypotf(m_vertices[0].x - m_vertices[2].x, m_vertices[0].y - m_vertices[2].y);
	return sqrt(p * (p - a) * (p - b) * (p - c));
}

std::string CTriangle::ToString() const
{
	std::stringstream buffer;
	buffer << std::fixed << std::setprecision(PRECISION);
	buffer << "triangle "
	       << m_vertices[0].x << " " << m_vertices[0].y << " "
	       << m_vertices[1].x << " " << m_vertices[1].y << " "
	       << m_vertices[2].x << " " << m_vertices[2].y << " "
	       << GetOutlineColor() << " "
	       << GetFillColor();
	return buffer.str();
}
