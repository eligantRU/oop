#pragma once

#include <string>
#include <iostream>

std::string FindAndReplace(const std::string & inputStr, const std::string & searchStr, const std::string & replaceStr);

void Replace(std::istream & input, std::ostream & output, const std::string & searchStr, const std::string & replaceStr);
