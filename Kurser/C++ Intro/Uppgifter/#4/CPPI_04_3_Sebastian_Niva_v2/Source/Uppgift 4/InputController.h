#pragma once
#include <iostream>

namespace InputController
{
	void AskForName(char* aNameVar, int aMinLetterLength, int aMaxLetterLength);
	int IntegerRange(const int aRange, const int aMinValue = 1);
	int IntegerMinMaxRange(const int aMaxValue, const int aMinValue = 1);
}