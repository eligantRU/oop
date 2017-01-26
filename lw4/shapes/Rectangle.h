#pragma once

#include "SolidShape.h"
#pragma warning(push, 3)
#include <glm/vec2.hpp>
#pragma warning(pop)

class CRectangle
	:public CSolidShape
{
public:
	CRectangle(const CPoint & leftTop, const CPoint & rightBottom,
	           const std::string & outlineColor, const std::string & fillColor);
	~CRectangle() = default;

	double GetPerimeter() const;
	double GetArea() const;

	CPoint GetLeftTop() const;
	CPoint GetRightBottom() const;
	double GetWidth() const;
	double GetHeight() const;

protected:
	void AppendProperties(std::ostream & stream) const override;

private:
	CPoint m_leftTopVertex;
	CPoint m_rightBottomVertex;
};
