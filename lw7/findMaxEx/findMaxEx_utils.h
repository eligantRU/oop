#pragma once

#include <vector>

template <class T, class Less = std::less<T>>
bool FindMax(const std::vector<T> & arr, T & maxValue, const Less & less = std::less<T>())
{
	if (arr.empty())
	{
		return false;
	}
	
	const T * max = &arr[0];
	for (const auto &element : arr)
	{
		if (less(*max, element))
		{
			max = &element;
		}
	}
	maxValue = *max;
	return true;
}
