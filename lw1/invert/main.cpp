#include "stdafx.h"

namespace
{

typedef std::array<std::array<float, 3>, 3> matrix3;
typedef std::array<std::array<float, 2>, 2> matrix2;

float GetDeterminant(const matrix3 & matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2] + 
		   matrix[0][2] * matrix[1][0] * matrix[2][1] +
		   matrix[0][1] * matrix[1][2] * matrix[2][0] -
		   matrix[0][2] * matrix[1][1] * matrix[2][0] -
		   matrix[0][0] * matrix[1][2] * matrix[2][1] -
		   matrix[0][1] * matrix[1][0] * matrix[2][2];
}

float GetDeterminant(const matrix2 & matrix)
{
	return matrix[0][0] * matrix[1][1] -
		   matrix[0][1] * matrix[1][0];
}

matrix3 GetMatrix3FromFile(std::ifstream & input, bool & error) // TODO: need to be refactored
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
			result[i][k] = static_cast<float>(atoi(num.c_str()));
			++j;
			++k;
		}
		++i;
	}
	return result;
}

template <class T>
void PrintMatrix(const T & matrix, unsigned precision = 3)
{
	for (const auto row : matrix)
	{
		for (const auto element : row)
		{
			std::cout << std::fixed << std::setprecision(precision) << element << " ";
		}
		std::cout << std::endl;
	}
}

matrix2 GetMinor(const matrix3 & matrix, const unsigned row, const unsigned column)
{
	matrix2 minor = {
		{
			{ 0, 0 },
			{ 0, 0 }
		}
	};

	unsigned k = 0;
	for (unsigned i = 0; i < 3; ++i)
	{
		unsigned n = 0;
		if (i == row)
		{
			continue;
		}
		for (unsigned j = 0; j < 3; ++j)
		{
			if (j == column)
			{
				continue;
			}
			minor[k][n] = matrix[i][j];
			++n;
		}
		++k;
	}
	return minor;
}

matrix3 GetMinorMatrix(const matrix3 & matrix)
{
	matrix3 minorMatrix = {
		{
			{ 0, 0, 0 },
			{ 0, 0, 0 },
			{ 0, 0, 0 }
		}
	};
	for (unsigned i = 0; i < 3; ++i)
	{
		for (unsigned j = 0; j < 3; ++j)
		{
			minorMatrix[i][j] = GetDeterminant(GetMinor(matrix, i, j));
		}
	}
	return minorMatrix;
}

matrix3 GetCofactorMatrix(const matrix3 & matrix)
{
	return {
		{
			{ matrix[0][0], -matrix[0][1], matrix[0][2] },
			{ -matrix[1][0], matrix[1][1], -matrix[1][2] },
			{ matrix[2][0], -matrix[2][1], matrix[2][2] }
		}
	};
}

matrix3 GetTransposeMatrix(const matrix3 & matrix)
{
	matrix3 transposeMatrix = {
		{
			{ 0, 0, 0 },
			{ 0, 0, 0 },
			{ 0, 0, 0 }
		}
	};

	for (unsigned i = 0; i < 3; ++i)
	{
		for (unsigned j = 0; j < 3; ++j)
		{
			transposeMatrix[i][j] = matrix[j][i];
		}
	}
	return transposeMatrix;
}

matrix3 MultMatrix(const matrix3 & matrix, const float scalar)
{
	return {
		{
			{ scalar * matrix[0][0], scalar * matrix[0][1], scalar * matrix[0][2] },
			{ scalar * matrix[1][0], scalar * matrix[1][1], scalar * matrix[1][2] },
			{ scalar * matrix[2][0], scalar * matrix[2][1], scalar * matrix[2][2] }
		}
	};
}

matrix3 GetInvertMatrix(const matrix3 & matrix)
{
	const float multiplier = 1.f / GetDeterminant(matrix);
	const auto minorMatrix = GetMinorMatrix(matrix);
	const auto cofactorMatrix = GetCofactorMatrix(minorMatrix);
	const auto transposeMatrix = GetTransposeMatrix(cofactorMatrix);

	return MultMatrix(transposeMatrix, multiplier);
}

}

int main(int argc, char * argv[])
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

	if (GetDeterminant(matrix) != 0)
	{
		PrintMatrix(GetInvertMatrix(matrix));
	}
	else
	{
		std::cout << "The inverse matrix does not exist" << std::endl;
	}

    return 0;
}
