#pragma once

#include "stdafx.h"

std::string FindAndReplace(const std::string & inputStr, const std::string & searchStr, const std::string & replaceStr);
void Replace(const std::string & inputFilePath, const std::string & outputFilePath, const std::string & searchStr, const std::string & replaceStr);
