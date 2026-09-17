#include <iostream>
#include <random>

int RollDie(int aSides = 6, int aAmount = 1)
{
	int toReturn = 0;

	std::random_device rDev;
	std::mt19937 rng(rDev());
	std::uniform_int_distribution < std::mt19937::result_type> dist(1, aSides);

	for (size_t i = 0; i < aAmount; i++)
	{
		toReturn += dist(rng);
	}

	return toReturn;
}

bool YesOrNoPrompt(bool aShouldCleanOnYes = false) {
	std::cout << " (y/n):";
	char playerInput = ' ';
	while (true)
	{
		std::cin >> playerInput;
		switch (playerInput)
		{
		case 'Y':
		case 'y':
			if (aShouldCleanOnYes)
			{
				system("clean");
			}
			return true;
		case 'N':
		case 'n':
			return false;
		default:
			std::cout << "Incorrect command. Please retry. (y/n):";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
			break;
		}
	}
}

int main()
{
	std::cout << "  ____________________________________________________________________________________________________________________\n";
	std::cout << " /                                                                                                                    \\\n";
	std::cout << "|   Welcome to Silver Sebastian's Casino! We are more than happy to take you to a rare state of economic possession!   |\n";
	//std::cout << "+                                                Please, ENTER                                                         +\n";
	std::cout << "|                                        Please, guess a number between 2-12.                                          |\n";
	std::cout << " \\____________________________________________________________________________________________________________________/\n";

	int guess = 0;
	int answer = -1;
	bool playerInterested = true;
	int wins = 0;

	do {
		do
		{
			std::cout << "Your guess:";
			std::cin >> guess;
			if (std::cin.fail())
			{
				std::cout << "That's not a number! Please try again, won't you?\n";

			}
			else if (guess < 2 || guess > 12)
			{
				std::cout << "That's not within the range! Please try again, won't you?\n";
			}
			else
			{
				int die1 = RollDie();
				int die2 = RollDie();
				answer = die1 + die2;
				if (answer != guess)
				{
					std::cout << "Ooh! Wrong guess! The dice rolled " << die1 << " & " << die2 << " for a total of: " << answer << "!\n";
					std::cout << "Would you like to play again?";
					std::cin.clear();
					std::cin.ignore(INT_MAX, '\n');
					playerInterested = YesOrNoPrompt();
				}
			}
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		} while (guess != answer && playerInterested);

		if (guess == answer)
		{
			system("cls");
			wins++;

			//std::cout << "\x1B[2J\x1B[H";
			std::cout << "******************************************************************************" << (answer > 9 ? "*\n" : "\n");
			std::cout << "*   Correct! You did it! Woohoo! The dice rolled " << answer << "! Take all our treasure!   *\n";
			std::cout << "******************************************************************************" << (answer > 9 ? "*\n" : "\n");

			std::cout << "Do you want to continue playing? You have" << (wins < 2 ? " only" : "") << " won " << wins << " time" << (wins < 2 ? "" : "s") << ".";
			playerInterested = YesOrNoPrompt();
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
	} while (playerInterested);
	std::cout << "Alright then, good bye! Don't let the door hit you on the way out!\n";

}