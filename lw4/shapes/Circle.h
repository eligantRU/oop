#pragma once

#include "SolidShape.h"
#pragma warning(push, 3)
#include <glm/vec2.hpp>
#pragma warning(pop)

class CCircle
	:public CSolidShape
{
public:
	CCircle(const CPoint & center, const double radius,
	        const std::string & outlineColor, const std::string & fillColor);
	~CCircle() = default;

	double GetPerimeter() const;
	double GetArea() const;

	CPoint GetCenter() const;
	double GetRadius() const;

protected:
	void AppendProperties(std::ostream & stream) const override;

private:
	CPoint m_center;
	double m_radius;
};
