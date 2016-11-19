#pragma once

#include "IShape.h"

class ISolidShape
	:public IShape
{
public:
	ISolidShape() = default;
	virtual ~ISolidShape() = default;

	std::string GetFillColor() const;

protected:
	std::string m_fillColor;
};
