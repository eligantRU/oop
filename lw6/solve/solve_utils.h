#pragma once

#include <array>

struct SEquationRoot3
{
	unsigned numRoots = 0;
	std::array<double, 3> roots = { NAN, NAN, NAN };
};

SEquationRoot3 Solve3(double a, double b, double c, double d);
