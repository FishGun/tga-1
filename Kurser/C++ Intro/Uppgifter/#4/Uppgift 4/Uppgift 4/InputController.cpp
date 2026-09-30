#include "InputController.h"

namespace InputController
{
	void AskForName(char* aNameVar, int aMinLetterLength, int aMaxLetterLength)
	{
		bool nameValid = false;
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		do
		{
			std::cout << "What is your name, traveler? (" << aMinLetterLength << "-" << aMaxLetterLength << " characters): ";
			std::cin.get(aNameVar, aMaxLetterLength + 1);
			std::cin.clear();
			std::cin.ignore(10000, '\n');

			for (int i = 0; i < 17; i++)
			{
				if (i >= aMinLetterLength && aNameVar[i] == '\0')
				{
					nameValid = true;
					break;
				}
				else if (aNameVar[i] == '\0')
				{
					std::cout << "\nError: Name too short. Please stick to " << aMinLetterLength << " character or more.\n\n";
					break;
				}
				else if (i >= 16)
				{
					std::cout << "\nError: Name too long. Please stick to " << aMaxLetterLength << " character or less.\n\n";
					break;
				}

				int nameIndexIntCasted = static_cast<int>(aNameVar[i]);
				if (i == 0 && !(nameIndexIntCasted >= 65 && nameIndexIntCasted <= 90))
				{
					std::cout << "\nError: The first input must be a capital letter.\n\n";
					break;
				}
				else if (i > 0 && !((nameIndexIntCasted >= 97 && nameIndexIntCasted <= 122) || (nameIndexIntCasted >= 65 && nameIndexIntCasted <= 90)))
				{
					std::cout << "\nError: Name may only consist of letters.\n\n";
					break;
				}
			}

		} while (!nameValid);
	}

	int IntegerRange(const int aRange, const int aMinValue)
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
	int IntegerMinMaxRange(const int aMaxValue, const int aMinValue)
	{
		return IntegerRange(aMaxValue - aMinValue + 1, aMinValue);
	}
}