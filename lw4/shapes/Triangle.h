#pragma once

#include "SolidShape.h"
#include <array>
#pragma warning(push, 3)
#include <glm/vec2.hpp>
#pragma warning(pop)

class CTriangle
	:public CSolidShape
{
public:
	CTriangle(const CPoint & point1, const CPoint & point2, const CPoint & point3,
	          const std::string & outlineColor, const std::string & fillColor);
	~CTriangle() = default;

	double GetPerimeter() const;
	double GetArea() const;

	CPoint GetVertex1() const;
	CPoint GetVertex2() const;
	CPoint GetVertex3() const;

protected:
	void AppendProperties(std::ostream & stream) const override;

private:
	std::array<CPoint, 3> m_vertices;
};
