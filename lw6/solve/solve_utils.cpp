#include "stdafx.h"

#include "solve_utils.h"

namespace
{

int Sign(const double num)
{
	return (num > 0) - (num < 0);
}

/// ax^2 + bx^ + c = 0
SEquationRoot2 Solve2ByDiscriminant(double a, double b, double c)
{
	if (a == 0)
	{
		throw std::invalid_argument("The equation of the second degree cannot have zero at the leading coefficient");
	}
	const auto d = pow(b, 2) - 4 * a *c;

	SEquationRoot2 roots;
	if (d < 0)
	{
		throw std::domain_error("All roots belongs to the set of complex numbers");
	}
	else if (d == 0)
	{
		roots.numRoots = 1;
		roots.roots[0] = -b / (2 * a);
	}
	else if (d > 0)
	{
		roots.numRoots = 2;
		roots.roots[0] = (-b - sqrt(d))/ (2 * a);
		roots.roots[1] = (-b + sqrt(d)) / (2 * a);
	}
	return roots;
}

/// x^3 + ax^2 + bx + c = 0
SEquationRoot3 Solve3ByViete(double a, double b, double c)
{
	const auto q = (pow(a, 2) - 3 * b) / 9;
	const auto r = (2 * pow(a, 3) - 9 * a * b + 27 * c) / 54;
	const auto s = pow(q, 3) - pow(r, 2);

	SEquationRoot3 roots;
	if (s > 0)
	{
		const auto phi = acos(r / sqrt(pow(q, 3))) / 3;
		roots.numRoots = 3;
		roots.roots[0] = -2 * sqrt(q) * cos(phi) - a / 3;
		roots.roots[1] = -2 * sqrt(q) * cos(phi + 2 * M_PI / 3) - a / 3;
		roots.roots[2] = -2 * sqrt(q) * cos(phi - 2 * M_PI / 3) - a / 3;
	}
	else if (s < 0)
	{
		if (q > 0)
		{
			const auto phi = acosh(abs(r) / sqrt(pow(q, 3))) / 3;
			roots.numRoots = 1;
			roots.roots[0] = -2 * Sign(r) * sqrt(q) * cosh(phi) - a / 3;
		}
		else if (q < 0)
		{
			const auto phi = asinh(abs(r) / sqrt(pow(abs(q), 3))) / 3;
			roots.numRoots = 1;
			roots.roots[0] = -2 * Sign(r) * sqrt(abs(q)) * cosh(phi) - a / 3;
		}
		else
		{
			roots.numRoots = 1;
			roots.roots[0] = -cbrt(c - pow(a, 3) / 27) - a / 3;
		}
	}
	else
	{
		roots.numRoots = 2;
		roots.roots[0] = -2 * cbrt(r) - a / 3;
		roots.roots[1] = cbrt(r) - a / 3;
	}
	return roots;
}

}

/// ax^2 + bx^ + c = 0
/// Solve2() return sorted roots from low to high
SEquationRoot2 Solve2(double a, double b, double c)
{
	try
	{
		auto roots = Solve2ByDiscriminant(a, b, c);
		std::sort(roots.roots.begin(), roots.roots.end());
		return roots;
	}
	catch (const std::exception &)
	{
		throw;
	}
}

/// ax^3 + bx^2 + cx + d = 0
/// Solve3() return sorted roots from low to high
SEquationRoot3 Solve3(double a, double b, double c, double d)
{
	if (a == 0)
	{
		throw std::invalid_argument("The equation of the third degree cannot have zero at the leading coefficient");
	}
	auto roots = Solve3ByViete(b / a, c / a, d / a);
	std::sort(roots.roots.begin(), roots.roots.end());
	return roots;
}
