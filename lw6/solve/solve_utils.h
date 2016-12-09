#pragma once

#include <array>

struct SEquationRoot3
{
	unsigned numRoots = 0;
	std::array<double, 3> roots = { NAN, NAN, NAN };
};

/// x^3 + ax^2 + bx + c = 0
/// Solve3() return sorted roots from low to high
SEquationRoot3 Solve3(double a, double b, double c, double d);
