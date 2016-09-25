#include "stdafx.h"

namespace
{

bool IsNumber(const std::string & str)
{
	return std::all_of(str.begin(), str.end(), std::isdigit);
}

uint8_t FlipByte(uint8_t byte)
{
	byte = ((byte & 0b01010101) << 1) | ((byte & 0b10101010) >> 1);
	byte = ((byte & 0b11001100) >> 2) | ((byte & 0b00110011) << 2);
	byte = (byte >> 4) | (byte << 4);
	return byte;
}

}

int main(int argc, char * argv[])
{
	if (argc != 2)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "flipbyte.exe <input byte>" << std::endl;
		return 1;
	}

	const std::string inputData = argv[1];
	if (!IsNumber(inputData))
	{
		std::cerr << "<input byte> must be unsigned integer(0..255)" << std::endl;
		return 1;
	}

	if (!((atoi(inputData.c_str()) >= 0 && atoi(inputData.c_str()) <= 255)))
	{
		std::cerr << "<input byte> must be 0..255" << std::endl;
		return 1;
	}

	const uint8_t inputByte = static_cast<uint8_t>(atoi(inputData.c_str()));
	
	std::cout << static_cast<unsigned>(FlipByte(inputByte)) << std::endl;

	return 0;
}
