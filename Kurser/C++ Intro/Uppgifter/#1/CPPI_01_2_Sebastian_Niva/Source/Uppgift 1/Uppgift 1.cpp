#include <iostream>
#include <random>



enum class GameType
{
	Guess,
	OddOrEven
};

int globalMoney = 100;
int globalWins = 0;



// Useful Functions for multiple games.
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

/// <summary>
/// Asks for player input & chooses which game to play based on it.
/// </summary>
/// <returns>Returns False if Exit was selected, otherwhise returns True.</returns>
int IntegerRangeInputController(int aMinValue, int aMaxValue)
{
	int input = 0;

	while (true)
	{
		std::cin >> input;

		if (std::cin.fail() || input < aMinValue || input > aMaxValue)
		{
			std::cout << "Invalid input. Please try again.\n";
			std::cin.clear();
			std::cin.ignore(INT_MAX, '\n');
		}
		else
		{
			return input;
		}
	}
}

void DisplayMoney()
{
	std::cout << "You currently have " << globalMoney << "$ left.\n";
}

int GetBet()
{
	std::cout << "How much would you like to bet?\n";
	DisplayMoney();
	std::cout << "$";
	int bet = IntegerRangeInputController(1, globalMoney);
	globalMoney -= bet;

	if (globalMoney == 0) {
		std::cout << "Woah! Going all-in, huh? Good luck...\n\n";
	}

	return bet;
}



//Menu & Selection Functions

/// <summary>
/// Handles the game logic for the Guessing game.
/// </summary>
/// <param name="aType"></param>
void PlayGuessGame()
{
	int victoryMultiplier = 5;
	system("cls");

	int bet = GetBet();

	std::cout << "Your guess:";
	int guess = IntegerRangeInputController(2, 12);

	int die1 = RollDie();
	int die2 = RollDie();
	int total = die1 + die2;

	std::cout << "\nThe dice rolled " << die1 << " & " << die2 << " for a total of: " << total << "!\n";

	if (total != guess)
	{
		std::cout << "\nOoh! Wrong guess! You loose!\n";
	}
	else
	{
		globalWins++;

		std::cout << "\n******************************************************************************" << (total > 9 ? "*\n" : "\n");
		std::cout << "*        Correct! You did it! Woohoo! The dice rolled " << total << "! You win " << bet * victoryMultiplier << "$!        *\n";
		std::cout << "******************************************************************************" << (total > 9 ? "*\n\n" : "\n\n");
	}
}

/// <summary>
/// Handles the game logic for the Odd or Even game.
/// </summary>
/// <param name="aType"></param>
void PlayOddEvenGame()
{
	int victoryMultiplier = 3;

	int bet = GetBet();

	std::cout <<
		"\n"
		"So, do you think the dice will be:\n"
		"(1): Odd\n"
		"(2): Even\n";

	std::cin.clear();
	int boundedInput = IntegerRangeInputController(1, 2) % 2;


	int die1 = RollDie();
	int die2 = RollDie();

	std::cout <<
		"\n"
		"The first die, rolled " << die1 << "\n"
		"The second die, rolled " << die2 << "\n";

	if ((die1 % 2 == die2 % 2) && (die1 % 2 == boundedInput))
	{
		globalWins++;
		globalMoney += bet * victoryMultiplier;
		std::cout <<
			"\nYou got it right! You win " << bet * victoryMultiplier << "$!\n";
	}
	else
	{
		std::cout <<
			"\nAlas, you lost.\n";
	}
}

void ShowRules(GameType aType)
{
	system("cls");
	switch (aType)
	{
	case GameType::Guess:
		std::cout <<
			"To play the Guessing Game is simple.\n"
			"First, you place your bet.\n"
			"Then, you guess a number between 2-12.\n"
			"Then, you roll two six sided dice.\n"
			"If they show what you guessed, you win five (5) times your bet!\n"
			"If they don't, you loose your bet.\n"
			"\n";
		break;
	case GameType::OddOrEven:
		std::cout <<
			"To play Odd or Even is simple.\n"
			"First, you place your bet.\n"
			"Then, pick either Odd or Even.\n"
			"Then, you roll two six sided dice.\n"
			"If they both show what you guessed, you win three (3) times your bet!\n"
			"If they don't, you loose your bet.\n"
			"\n";
		break;
	default:
		break;
	}
	system("pause");
	system("cls");
}

/// <summary>
/// Performs generic game logic (play, rules, exit options), and hooks into specif game function when relevant.
/// </summary>
/// <param name="aType"></param>
void InitAGame(GameType aType)
{
	std::cout << "Welcome to the " << (aType == GameType::Guess ? "Guessing Game" : "Odd or Even") << " table.\n";
	ShowRules(aType);

	while (true)
	{
		if (globalMoney < 1)
		{
			return;
		}
		switch (aType)
		{
		case GameType::Guess:
		{
			DisplayMoney();
			std::cout << std::endl;
			std::cout <<
				"You are at the guessing game table. Would you like to:\n"
				"(1): Play a round.\n"
				"(2): Learn the rules.\n"
				"(3): Leave the table.\n";
			switch (IntegerRangeInputController(1, 3))
			{
			case 1:
				system("cls");
				PlayGuessGame();
				DisplayMoney();
				system("pause");
				system("cls");
				break;
			case 2:
				ShowRules(aType);
				break;
			default:
				std::cout << "\nAlright, come back any time.\n";
				return;
			}
		}
		break;
		case GameType::OddOrEven:
		{
			DisplayMoney();
			std::cout << std::endl;
			std::cout <<
				"You are at the Odd or Even table. Would you like to:\n"
				"(1): Play a round.\n"
				"(2): Learn the rules.\n"
				"(3): Leave the table.\n";
			switch (IntegerRangeInputController(1, 3))
			{
			case 1:
				system("cls");
				PlayOddEvenGame();
				DisplayMoney();
				system("pause");
				system("cls");
				break;
			case 2:
				ShowRules(aType);
				break;
			default:
				std::cout << "\nAlright, come back any time.\n";
				return;
			}
		}
		break;
		default:
			break;
		}
	}
}

/// <summary>
/// Starts up the game system itself without wrapping.
/// </summary>
void GameManager()
{
	while (true)
	{
		system("cls");
		DisplayMoney();
		std::cout << std::endl;
		std::cout <<
			"Which game would you like to play?\n"
			"(1): Guess the number\n"
			"(2): Odd or Even?\n"
			"(3): Leave\n";

		switch (IntegerRangeInputController(1, 3))
		{
		case 1:
			InitAGame(GameType::Guess);
			break;
		case 2:
			InitAGame(GameType::OddOrEven);
			break;
		case 3:
			return;
		default:
			break;
		}
		if (globalMoney <= 0)
		{
			return;
		}
		system("pause");
	}
}

//Init & Exit Functions.
void Enter()
{
	std::cout << "  ____________________________________________________________________________________________________________________\n";
	std::cout << " /                                                                                                                    \\\n";
	std::cout << "|   Welcome to Silver Sebastian's Casino! We are more than happy to take you to a rare state of economic possession!   |\n";
	std::cout << "|                                                Please, ENTER                                                         |\n";
	std::cout << " \\____________________________________________________________________________________________________________________/\n";
	system("pause");
	system("cls");
}

void Exit()
{
	system("cls");

	if (globalMoney <= 0)
	{
		std::cout <<
			"Looks like this is the end of the road bud. You had a good run, you even won " << globalWins << " time(s), but now it's time to get out.\n"
			"Cheer up, you played your hand as good as you could. Its just that, well...\n"
			"The house always wins.\n"
			"\n"
			"Ending 1: Bankruptcy.\n";
	}
	else if (globalWins < 1)
	{
		std::cout <<
			"Nothing ventured nothing gained, huh? Well, in your case, the only thing certian is the latter.\n"
			"Ya should have stayed home, punk. The bettin' world 'aint for the feint of heart, and your short an ace.\n"
			"\n"
			"Ending 0: Betting Bad.\n";
	}
	else if (globalMoney < 100)
	{
		std::cout <<
			"Cutting your losses & counting your victories, you know when it's time to get out, and move past the grand silver doors, into the cool evening air & busy streets\n"
			"You may not be a milionare, but you atleast have " << globalMoney << "$ left, and won a total of " << globalWins << " time(s), and that counts for something.\n"
			"\n"
			"Ending 2: Know when to fold 'em.\n";
	}
	else if (globalMoney == 100)
	{
		std::cout <<
			"That place tried something, and you ain't givin it nothing. Sure, ya didn't win. What do you want me to say?\n"
			"Ya got out, and kept your wallet while you were at it. Could be worse, a lot worse.\n"
			"And ya had some fun too, eh? Won \n" << globalWins << " time(s)."
			"\n"
			"Ending 3: Even Steven.\n";
	}
	std::cout << std::endl;
	system("pause");
}

int main()
{
	Enter();

	GameManager();

	Exit();
}