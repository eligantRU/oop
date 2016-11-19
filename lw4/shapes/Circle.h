#pragma once

#include "ISolidShape.h"
#pragma warning(push, 3)
#include <glm/vec2.hpp>
#pragma warning(pop)

class CCircle
	:public ISolidShape
{
public:
	CCircle(const CPoint & center, const double radius,
	        const std::string & outlineColor, const std::string & fillColor);
	~CCircle() = default;

	double GetPerimeter() const;
	double GetArea() const;
	std::string ToString() const;

	CPoint GetCenter() const;
	double GetRadius() const;

private:
	CPoint m_center;
	double m_radius;
};
