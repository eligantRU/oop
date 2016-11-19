#include "stdafx.h"

#include "LineSegment.h"
#include <iomanip>

namespace
{

static const unsigned PRECISION = 1;

}

CLineSegment::CLineSegment(const CPoint & start, const CPoint & end, 
	                       const std::string & outlineColor)
	:m_startPoint(start)
	,m_endPoint(end)
{
	m_outlineColor = outlineColor;
}

double CLineSegment::GetArea() const
{
	return 0.0;
}

double CLineSegment::GetPerimeter() const
{
	return std::hypot(m_endPoint.x - m_startPoint.x,
	                  m_endPoint.y - m_startPoint.y);
}

std::string CLineSegment::ToString() const
{
	std::stringstream buffer;
	buffer << std::fixed << std::setprecision(PRECISION);
	buffer << "line_segment "
	       << m_startPoint.x << " "
	       << m_startPoint.y << " "
	       << m_endPoint.x << " "
	       << m_endPoint.y << " "
	       << GetOutlineColor();
	return buffer.str();
}

CPoint CLineSegment::GetStartPoint() const
{
	return m_startPoint;
}

CPoint CLineSegment::GetEndPoint() const
{
	return m_endPoint;
}
