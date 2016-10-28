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
	result |= (byte & 0b01100000) >> 5;
	result |= (byte & 0b00011000) << 3;
	result |= (byte & 0b00000111) << 2;
	return result;
}

uint8_t MixBitsBack(const uint8_t byte)
{
	uint8_t result = 0;

	result |= (byte & 0b11000000) >> 3;
	result |= (byte & 0b00100000) << 2;
	result |= (byte & 0b00011100) >> 2;
	result |= (byte & 0b00000011) << 5;
	return result;
}

void Crypt(const std::string inputFileName, const std::string outputFileName, const std::function<uint8_t(uint8_t)> & fn)
{
	std::ifstream input(inputFileName, std::ios::binary);
	if (!input.is_open())
	{
		throw std::runtime_error("Failed to open " + inputFileName + " for reading");
	}

	std::ofstream output(outputFileName, std::ios::binary);
	if (!output.is_open())
	{
		throw std::runtime_error("Failed to open " + outputFileName + " for writing");
	}

	for (char ch; input.get(ch); )
	{
		auto byte = fn(static_cast<uint8_t>(ch));
		output.put(static_cast<char>(byte));
	}
}

uint8_t ValidateKey(const std::string & key)
{
	if (!IsNumber(key))
	{
		throw std::runtime_error("<key> must be unsigned integer(0..255)");
	}

	if (!((atoi(key.c_str()) >= 0 && atoi(key.c_str()) <= 255)))
	{
		throw std::runtime_error("<key> must be 0..255");
	}
	return static_cast<uint8_t>(atoi(key.c_str()));
}

Mode ValidateCryptMode(const std::string & mode)
{
	if (mode == "crypt")
	{
		return Mode::Crypt;
	}
	else if (mode == "decrypt")
	{
		return Mode::Decrypt;
	}
	else
	{
		throw std::runtime_error("<mode> must be \"crypt\" or \"decrypt\"");
	}
}

class Crypter
{
public:
	void operator()(const std::string inputFileName, const std::string outputFileName, const Mode cryptMode, const uint8_t key)
	{
		switch (cryptMode)
		{
		case Mode::Crypt:
			Crypt(inputFileName, outputFileName, [=](uint8_t byte) {
				byte ^= key;
				byte = MixBits(byte);
				return byte;
			});
			break;
		case Mode::Decrypt:
			Crypt(inputFileName, outputFileName, [=](uint8_t byte) {
				byte = MixBitsBack(byte);
				byte ^= key;
				return byte;
			});
			break;
		default:
			throw std::logic_error("Unknown crypt mode");
		}
	}
};

}

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "crypt.exe <mode> <input file> <output file> <key>" << std::endl;
		return 1;
	}
	
	try
	{
		const Mode cryptMode = ValidateCryptMode(argv[1]);
		const uint8_t key = ValidateKey(argv[4]);
		Crypter crypter;
		crypter(argv[2], argv[3], cryptMode, key);
	}
	catch (std::exception & exception)
	{
		std::cerr << exception.what() << std::endl;
		return 1;
	}
	return 0;
}
