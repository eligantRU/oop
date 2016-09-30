#include "stdafx.h"

namespace
{

bool IsNumber(const std::string & str)
{
	return std::all_of(str.begin(), str.end(), std::isdigit);
}

enum class Mode
{
	Crypt,
	Decrypt
};

uint8_t MixBits(const uint8_t byte)
{
	uint8_t result = 0;

	result |= (byte & 0b10000000) >> 2;
	result |= (byte & 0b01000000) >> 5;
	result |= (byte & 0b00100000) >> 5;
	result |= (byte & 0b00010000) << 3;
	result |= (byte & 0b00001000) << 3;
	result |= (byte & 0b00000100) << 2;
	result |= (byte & 0b00000010) << 2;
	result |= (byte & 0b00000001) << 2;
	return result;
}

uint8_t MixBitsBack(const uint8_t byte)
{
	uint8_t result = 0;

	result |= (byte & 0b10000000) >> 3;
	result |= (byte & 0b01000000) >> 3;
	result |= (byte & 0b00100000) << 2;
	result |= (byte & 0b00010000) >> 2;
	result |= (byte & 0b00001000) >> 2;
	result |= (byte & 0b00000100) >> 2;
	result |= (byte & 0b00000010) << 5;
	result |= (byte & 0b00000001) << 5;
	return result;
}

void Crypt(std::ifstream & input, std::ofstream & output, const uint8_t key)
{
	uint8_t byte;
	std::string currentStr;
	while (std::getline(input, currentStr))
	{
		for (const auto ch : currentStr)
		{
			byte = static_cast<uint8_t>(ch);
			byte ^= key;
			output.put(static_cast<char>(MixBits(byte)));
		}
		output << std::endl;
	}
}

void Decrypt(std::ifstream & input, std::ofstream & output, const uint8_t key)
{
	uint8_t byte;
	std::string currentStr;
	while (std::getline(input, currentStr))
	{
		for (const auto ch : currentStr)
		{
			byte = static_cast<uint8_t>(ch);
			byte = MixBitsBack(byte);
			byte ^= key;
			output.put(static_cast<char>(byte));
		}
		output << std::endl;
	}
}

}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "crypt.exe <mode> <input file> <output file> <key>" << std::endl;
		return 1;
	}

	Mode cryptMode;
	std::string mode = argv[1];
	if (mode == "crypt")
	{
		cryptMode = Mode::Crypt;
	}
	else if (mode == "decrypt")
	{
		cryptMode = Mode::Decrypt;
	}
	else
	{
		std::cerr << "<mode> must be \"crypt\" or \"decrypt\"" << std::endl;
		return 1;
	}

	std::ifstream input(argv[2], std::ios::binary);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[2] << " for reading" << std::endl;
		return 1;
	}

	std::ofstream output(argv[3], std::ios::binary);
	if (!output.is_open())
	{
		std::cerr << "Failed to open " << argv[3] << " for writing" << std::endl;
		return 1;
	}

	const std::string inputData = argv[4];
	if (!IsNumber(inputData))
	{
		std::cerr << "<key> must be unsigned integer(0..255)" << std::endl;
		return 1;
	}

	if (!((atoi(inputData.c_str()) >= 0 && atoi(inputData.c_str()) <= 255)))
	{
		std::cerr << "<key> must be 0..255" << std::endl;
		return 1;
	}
	const uint8_t key = static_cast<uint8_t>(atoi(inputData.c_str()));
	
	switch (cryptMode)
	{
	case Mode::Crypt:
		Crypt(input, output, key);
		break; 
	case Mode::Decrypt:
		Decrypt(input, output, key);
		break;
	default:
		assert(!"Unknown mode");
	}

	return 0;
}
