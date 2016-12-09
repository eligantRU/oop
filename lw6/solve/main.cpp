#include "stdafx.h"

#include "solve_utils.h"

int main()
{
	double a, b, c, d;
	while ((std::cin >> a) && (std::cin >> b) && (std::cin >> c) && (std::cin >> d))
	{
		try
		{
			const auto roots = Solve3(a, b, c, d);
			std::cout << std::fixed << std::setprecision(3);
			for (unsigned i = 0; i < roots.numRoots; ++i)
			{
				std::cout << "x = " << roots.roots[i] << std::endl;
			}
			std::cout << std::endl;
		}
		catch (const std::exception & ex)
		{
			std::cerr << ex.what() << std::endl << std::endl;
		}
	}
	return 0;
}
