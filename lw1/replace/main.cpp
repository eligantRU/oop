#include "stdafx.h"

int main(int argc, char * argv[])
{
	if (argc != 5)
	{
		std::cerr << "Invalid params. Use this:" << std::endl;
		std::cerr << "replace.exe <input file> <output file> <search string> <replace string>" << std::endl;
		std::exit(-1);
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[1] << " for reading" << std::endl;
		std::exit(-2);
	}

	std::ofstream output(argv[2]);
	if (!output.is_open())
	{
		std::cerr << "Failed to open " << argv[2] << " for writing" << std::endl;
		std::exit(-3);
	}

	std::string inputData((std::istreambuf_iterator<char>(input)),
						   std::istreambuf_iterator<char>());

	std::string searchingStr = argv[3];
	std::string replacingStr = argv[4];

	int it = inputData.find(searchingStr);
	while (it != std::string::npos)
	{
		inputData.replace(it, searchingStr.length(), replacingStr);
		it = inputData.find(searchingStr);
	}
	output << inputData;

	if (!output.flush())
	{
		std::cerr << "Failed to save data on disk" << std::endl;
		std::exit(-4);
	}
	return 0;
}
