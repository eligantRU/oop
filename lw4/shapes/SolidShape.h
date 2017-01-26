#pragma once

#include "ISolidShape.h"
#include "Shape.h"

class CSolidShape
	:public ISolidShape
	,public CShape
{
public:
	CSolidShape(const std::string & type, const std::string & outlineColor, const std::string & fillColor);
	virtual ~CSolidShape() = default;

	void SetFillColor(const std::string & color) override;
	std::string GetFillColor() const final;

	void SetOutlineColor(const std::string & color) final;
	std::string GetOutlineColor() const final;

	std::string ToString() const final;

protected:
	virtual void AppendProperties(std::ostream & stream) const = 0;

protected:
	std::string m_type;
	std::string m_fillColor;
};
