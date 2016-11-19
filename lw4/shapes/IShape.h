#pragma once

#include <string>
#pragma warning(push, 3)
#include <glm/vec3.hpp>
#pragma warning(pop)

typedef glm::vec2 CPoint;

class IShape
{
public:
	IShape() = default;
	virtual ~IShape() = default;

	virtual double GetArea() const = 0;
	virtual double GetPerimeter() const = 0;
	virtual std::string ToString() const = 0;
	std::string GetOutlineColor() const;

protected:
	std::string m_outlineColor;
};

std::string DecToHex(const std::string & dec);
std::string HexToDec(const std::string & hex);
