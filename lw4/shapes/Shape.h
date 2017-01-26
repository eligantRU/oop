#pragma once

#include "IShape.h"

class CShape
	:virtual public IShape
{
public:
	CShape() = default;
	virtual ~CShape() = default;

	void SetOutlineColor(const std::string & color) override;
	std::string GetOutlineColor() const override;

private:
	std::string m_outlineColor;
};
