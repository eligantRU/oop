#include "stdafx.h"

int main(int argc, char * argv[])
{
	std::ifstream input(argv[1]);
	std::ofstream output(argv[2]);
	std::string inputData((std::istreambuf_iterator<char>(input)),
						   std::istreambuf_iterator<char>());

	std::string searchingStr = argv[3];
	std::string replacingSubstr = argv[4];

	int it = inputData.find(searchingStr);
	while (it != std::string::npos)
	{
		inputData.replace(it, searchingStr.length(), replacingSubstr);
		it = inputData.find(searchingStr);
	}

	output << inputData << std::endl;

	return 0;
}
