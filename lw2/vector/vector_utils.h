#pragma once

#include <vector>
#include <iostream>

void PrintVector(std::ostream & output, const std::vector<double> & vec, unsigned precision);

std::vector<double> GetNums(std::istream & input);

void Div(std::vector<double> & vec, const double divider);

void ProcessVector(std::vector<double> & vec);
