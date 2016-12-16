#pragma once

template <class T, class Less>
bool FindMax(const std::vector<T> & arr, T & maxValue, const Less & less)
{
	if (arr.empty())
	{
		return false;
	}
	maxValue = arr[0];
	for (const auto &element : arr)
	{
		if (less(maxValue, element))
		{
			maxValue = element;
		}
	}
	return true;
}
