#pragma once

#include "IShape.h"

class CShape
	:public IShape
{
public:
	CShape() = default;
	virtual ~CShape() = default;

	std::string GetOutlineColor() const override;

protected:
	std::string m_outlineColor;
};
