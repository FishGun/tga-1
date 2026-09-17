#include "InputController.h"
#include <iostream>

namespace InputController
{
	int IntegerRange(int aRange, int aMinValue)
	{
		int maxValue = aMinValue + aRange - 1;
		int input = 0;

		while (true)
		{
			std::cin >> input;

			if (std::cin.fail())
			{
				std::cout << "Invalid input. Please try again.\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
			else if (input < aMinValue || input > maxValue)
			{
				std::cout << "Input outside allowed range. Min:" << aMinValue << " Max:" << maxValue << ". Please try again.\n";
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
			else
			{
				return input;
			}
		}
	}
	int IntegerMinMaxRange(int aMaxValue, int aMinValue)
	{
		return IntegerRange(aMaxValue-aMinValue+1, aMinValue);
	}
}