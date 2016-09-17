#include "stdafx.h"

namespace
{

bool isNumber(const std::string & str)
{
	return std::all_of(str.begin(), str.end(), std::isdigit);
}

uint8_t byte(uint8_t byte)
{
	byte = ((byte & 0x55) << 1) | ((byte & 0xAA) >> 1);
	byte = ((byte & 0xCC) >> 2) | ((byte & 0x33) << 2);
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
		std::exit(1);
	}

	const std::string inputData = argv[1];
	if (!isNumber(inputData))
	{
		std::cerr << "<input byte> must be unsigned integer(0..255)" << std::endl;
		std::exit(1);
	}

	if (!((atoi(inputData.c_str()) >= 0 && atoi(inputData.c_str()) <= 255)))
	{
		std::cerr << "<input byte> must be 0..255" << std::endl;
		std::exit(1);
	}

	const uint8_t inputByte = static_cast<uint8_t>(atoi(inputData.c_str()));
	printf("%u\n", byte(inputByte));

	return 0;
}
