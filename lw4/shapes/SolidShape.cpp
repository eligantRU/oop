#include "stdafx.h"

#include "SolidShape.h"

std::string CSolidShape::GetFillColor() const
{
	return m_fillColor;
}

std::string CSolidShape::GetOutlineColor() const
{
	return CShape::GetOutlineColor();
}
