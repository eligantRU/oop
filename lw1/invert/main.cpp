#include "stdafx.h"

namespace
{

typedef std::array<std::array<int, 3>, 3> matrix3;

bool IsNumber(const std::string & str)
{
	return std::all_of(str.begin(), str.end(), std::isdigit);
}

matrix3 GetMatrix3FromFile(std::ifstream & input, bool & error)
{
	matrix3 result = {
		{ 
			{ 0, 0, 0 },
			{ 0, 0, 0 },
			{ 0, 0, 0 }
		}
	};

	std::string currentLine;
	int i = 0;
	while (std::getline(input, currentLine))
	{
		if (i >= 3)
		{
			std::cerr << "Something was wrong: " << "Too many lines in file" << std::endl;
			error = true;
			return matrix3();
		}
		int j = 0;
		int k = 0;
		while (j < currentLine.length())
		{
			if (k >= 3)
			{
				std::cerr << "Something was wrong: " << "Too many numbers in line" << std::endl;
				error = true;
				return matrix3();
			}
			std::string num;
			bool wasMinus = false;
			while (std::isdigit(currentLine[j]) || currentLine[j] == '-')
			{
				if (wasMinus && (currentLine[j] == '-'))
				{
					std::cerr << "Something was wrong: " << "Two consecutive minus" << std::endl;
					error = true;
					return matrix3();
				}
				if (currentLine[j] == '-')
				{
					wasMinus = true;
				}
				num += currentLine[j];
				++j;
			}
			result[i][k] = atoi(num.c_str());
			++j;
			++k;
		}
		++i;
	}
	return result;
}

void PrintMatrix(const matrix3 & matrix)
{
	for (const auto row : matrix)
	{
		for (const auto element : row)
		{
			std::cout << element << " ";
		}
		std::cout << std::endl;
	}
}

}

int main(int argc, char * argv[]) // NOTE: NOT FOR RELEASE
{
	if (argc != 2)
	{
		std::cerr << "Invalid arguments. Use:" << std::endl;
		std::cerr << "invert.exe <matrix file>" << std::endl;
		return 1;
	}

	std::ifstream input(argv[1]);
	if (!input.is_open())
	{
		std::cerr << "Failed to open " << argv[1] << " for reading" << std::endl;
		return 1;
	}

	bool error = false;
	auto matrix = GetMatrix3FromFile(input, error);
	if (error)
	{
		return 1;
	}

	PrintMatrix(matrix);

    return 0;
}
