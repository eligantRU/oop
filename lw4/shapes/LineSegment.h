#pragma once

#include "Shape.h"
#pragma warning(push, 3)
#include <glm/vec2.hpp>
#pragma warning(pop)

class CLineSegment final
	:public CShape
{
public:
	CLineSegment(const CPoint & start, const CPoint & end, const std::string & outlineColor);
	~CLineSegment() = default;

	double GetArea() const;
	double GetPerimeter() const override;

	std::string ToString() const override;

	CPoint GetStartPoint() const;
	CPoint GetEndPoint() const;

private:
	CPoint m_startPoint;
	CPoint m_endPoint;
};
