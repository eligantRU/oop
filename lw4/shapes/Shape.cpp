#include "stdafx.h"

#include "Shape.h"

void CShape::SetOutlineColor(const std::string & color)
{
	m_outlineColor = color;
}

std::string CShape::GetOutlineColor() const
{
	return m_outlineColor;
}
