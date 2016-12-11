#pragma once

#include <array>

struct SEquationRoot2
{
	unsigned numRoots = 0;
	std::array<double, 2> roots = { NAN, NAN };
};

struct SEquationRoot3
{
	unsigned numRoots = 0;
	std::array<double, 3> roots = { NAN, NAN, NAN };
};

/// ax^2 + bx^ + c = 0
/// Solve2() return sorted roots from low to high
SEquationRoot2 Solve2(double a, double b, double c);

/// ax^3 + bx^2 + cx + d = 0
/// Solve3() return sorted roots from low to high
SEquationRoot3 Solve3(double a, double b, double c, double d);
