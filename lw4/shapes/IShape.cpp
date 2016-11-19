#include "stdafx.h"

#include "IShape.h"
#include <boost/algorithm/string.hpp>

std::string DecToHex(const std::string & dec)
{
	std::stringstream buffer;
	buffer << std::hex << stoi(dec);
	auto result(buffer.str());
	boost::to_upper(result);
	return result;
}

std::string HexToDec(const std::string & hex)
{
	std::stringstream buffer;
	int dec;
	buffer << hex << std::endl;
	buffer >> std::hex >> dec;
	return std::to_string(dec);
}

std::string IShape::GetOutlineColor() const
{
	return m_outlineColor;
}
