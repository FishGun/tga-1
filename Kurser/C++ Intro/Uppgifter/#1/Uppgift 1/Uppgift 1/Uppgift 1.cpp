#include <iostream>
#include <random>



const int globalAmountOfGames = 3;
enum class GameType
{
	Guess,
	OddOrEven,
	SkyHigh
};

const int globalGameHistoryArraySize = 5;
int globalGameHistory[globalGameHistoryArraySize] = { 0 };

int globalMoney = 100;

int globalWins = 0;




int RollDice(int aSides = 6, int aAmount = 1)
{
	int toReturn = 0;

	static std::random_device rDev;
	static std::mt19937 rng(rDev());
	std::uniform_int_distribution < std::mt19937::result_type> dist(1, aSides);

	for (int i = 0; i < aAmount; i++)
	{
		toReturn += dist(rng);
	}

	return toReturn;
}

int IntegerRangeInputController(int aMinValue, int aMaxValue)
{
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
		else if (input < aMinValue || input > aMaxValue)
		{
			std::cout << "Input outside allowed range. Min:" << aMinValue << " Max:" << aMaxValue << ". Please try again.\n";
			std::cin.clear();
			std::cin.ignore(10000, '\n');
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

	if (globalMoney == 0)
	{
		std::cout << "Woah! Going all-in, huh? Good luck...\n\n";
	}

	return bet;
}

void GameEndStatTracker(bool aDidWin)
{
	for (int i = globalGameHistoryArraySize - 1; i > 0; i--)
	{
		globalGameHistory[i] = globalGameHistory[i - 1];
	}
	globalGameHistory[0] = (aDidWin ? 1 : -1);

	if (aDidWin)
	{
		globalWins++;
	}
}

bool CheckIfProfitedTooMuch(int aProfit, bool aSayQuipOtherwhise = true)
{
	if (aProfit >= 100)
	{
		return true;
	}
	if (aSayQuipOtherwhise)
	{
		if (aProfit >= 20)
		{
			std::cout << "Hey, it's big winner! Carefull now, wouldn't wanna make too much, eh?\n\n";
		}
		else if (aProfit <= -20)
		{
			std::cout << "Coming back here huh? Let's see if you have better luck this time...\n\n";
		}
		else
		{
			std::cout << "You aren't good enough for anyone to notice your presence. But not bad enough either, so there is that.\n\n";
		}
	}
	return false;
}

void DisplayHistory(bool aInitialEmptyLine = true)
{
	if (aInitialEmptyLine)
	{
		std::cout << "\n";
	}
	std::cout <<
		"Your last " << globalGameHistoryArraySize << " games went like this:\n";

	for (int i = 0; i < globalGameHistoryArraySize; i++)
	{
		if (globalGameHistory[i] == 1)
		{
			std::cout << "Win!\n";
		}
		else if (globalGameHistory[i] == -1)
		{
			std::cout << "Loss!\n";
		}
		else
		{
			std::cout << "N/A\n";
		}
	}
	std::cout << "\n";
}

int PlayGuessGame()
{
	int victoryMultiplier = 5;
	system("cls");

	int bet = GetBet();

	std::cout << "Your guess:";
	int guess = IntegerRangeInputController(2, 12);

	int die1 = RollDice();
	int die2 = RollDice();
	int total = die1 + die2;

	std::cout << "\nThe dice rolled " << die1 << " & " << die2 << " for a total of: " << total << "!\n";

	if (total != guess)
	{
		GameEndStatTracker(false);
		std::cout << "\nOoh! Wrong guess! You loose!\n";
		return -bet;
	}
	else
	{
		GameEndStatTracker(true);
		std::cout << "\n******************************************************************************" << (total > 9 ? "*\n" : "\n");
		std::cout << "*        Correct! You did it! Woohoo! The dice rolled " << total << "! You win " << bet * victoryMultiplier << "$!        *\n";
		std::cout << "******************************************************************************" << (total > 9 ? "*\n\n" : "\n\n");
		globalMoney += bet * victoryMultiplier;
		return bet * victoryMultiplier - bet;
	}
}

int PlayOddEvenGame()
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


	int die1 = RollDice();
	int die2 = RollDice();

	std::cout <<
		"\n"
		"The first die, rolled " << die1 << "\n"
		"The second die, rolled " << die2 << "\n";

	if ((die1 % 2 == die2 % 2) && (die1 % 2 == boundedInput))
	{
		GameEndStatTracker(true);
		globalMoney += bet * victoryMultiplier;
		std::cout <<
			"\nYou got it right! You win " << bet * victoryMultiplier << "$!\n";
		return bet * victoryMultiplier - bet;
	}
	else
	{
		GameEndStatTracker(false);
		std::cout <<
			"\nAlas, you lost.\n";
		return -bet;
	}
}

int PlaySkyHighGame()
{
	static float victoryMultiplierArray[] = { 1.2f, 1.5f, 2.0f, 3.0f, 5.0f, 8.0f ,12.0f ,20.0f };
	const int victoryArraySize = 8;

	int bet = GetBet();

	for (int i = 0; i < victoryArraySize; i++)
	{
		int coinFlip = RollDice(2);
		if (coinFlip == 1)
		{
			int theoreticalWinnings = static_cast<int>(bet * victoryMultiplierArray[i]);
			if (i >= victoryArraySize - 1)
			{
				GameEndStatTracker(true);
				globalMoney += theoreticalWinnings;
				std::cout <<
					"\nYou make it to your desination and get x20 your bet!!!\n"
					"You win " << theoreticalWinnings << "$! \n";
				DisplayMoney();
				DisplayHistory();
				system("pause");
				return theoreticalWinnings - bet;
			}

			std::cout <<
				"\nThe plane didn't crash!\n"
				"The current multiplier is: " << victoryMultiplierArray[i] << "x\n"
				"Do you want to:\n"
				"(1): Keep going\n"
				"(2): Jump out\n";

			std::cin.clear();
			switch (IntegerRangeInputController(1, 2))
			{
				case 1:
					std::cout <<
						"You stay a little longer...\n";
					break;
				case 2:
					GameEndStatTracker(true);
					globalMoney += theoreticalWinnings;

					std::cout <<
						"You get out in time, keeping a total of " << theoreticalWinnings << "$\n";
					DisplayMoney();
					DisplayHistory();
					system("pause");
					return theoreticalWinnings - bet;
				default:
					break;
			}
		}
		else
		{
			GameEndStatTracker(false);
			std::cout << static_cast<char>(7) <<
				"OH NO! The plane crashes! You loose it all!\n";
			DisplayHistory();
			system("pause");
			return -bet;
		}
		system("pause");
	}
	return -1;
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
		case GameType::SkyHigh:
			std::cout <<
				"To play Sky High is simple.\n"
				"First, you place your bet.\n"
				"Then, you either loose (50%), or incrase your possible earnings (50%).\n"
				"You may then decide to cash out, or go again.\n"
				"The increases are as follows:\n"
				"x1.2 | x1.5 | x2 | x3 | x5 | x8 | x12 | x20!\n"
				"\n";
			break;
		default:
			break;
	}
	system("pause");
	system("cls");
}

void StartAGame(GameType aType)
{
	static int profitArray[globalAmountOfGames] = { 0 };
	int gameTypeCastedToInt = static_cast<int>(aType);

	if (CheckIfProfitedTooMuch(profitArray[gameTypeCastedToInt], false))
	{
		system("cls");
		std::cout << "Hey! You're too good at this game! Go play somewhere else!\n";
		return;
	}

	switch (aType)
	{
		case GameType::Guess:
			std::cout << "Welcome to the Guessing Game table.\n";
			break;
		case GameType::OddOrEven:
			std::cout << "Welcome to the Odd or Even table.\n";
			break;
		case GameType::SkyHigh:
			std::cout << "Welcome to the Whell of Fortune!\n";
			break;
		default:
			break;
	}
	ShowRules(aType);

	bool isFirstLoop = true;
	while (true)
	{
		if (globalMoney < 1)
		{
			return;
		}
		else if (CheckIfProfitedTooMuch(profitArray[gameTypeCastedToInt], isFirstLoop))
		{
			std::cout << "Hey! You're too good at this game! Go play somewhere else!\n";
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
						profitArray[gameTypeCastedToInt] += PlayGuessGame();
						DisplayMoney();
						DisplayHistory();
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
						profitArray[static_cast<int>(aType)] += PlayOddEvenGame();
						DisplayMoney();
						DisplayHistory();
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
			case GameType::SkyHigh:
			{
				DisplayMoney();
				std::cout << std::endl;
				std::cout <<
					"You are at the Sky High table. Would you like to:\n"
					"(1): Play a round.\n"
					"(2): Learn the rules.\n"
					"(3): Leave the table.\n";
				switch (IntegerRangeInputController(1, 3))
				{
					case 1:
						system("cls");
						profitArray[static_cast<int>(aType)] += PlaySkyHighGame();
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
		isFirstLoop = false;
	}
}

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
			"(3): Sky High!\n"
			"(4): See Game History\n"
			"(5): Leave\n";

		switch (IntegerRangeInputController(1, 5))
		{
			case 1:
				StartAGame(GameType::Guess);
				break;
			case 2:
				StartAGame(GameType::OddOrEven);
				break;
			case 3:
				StartAGame(GameType::SkyHigh);
				break;
			case 4:
				system("cls");
				DisplayHistory(false);
				break;
			case 5:
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

	if (globalMoney == 100 && globalWins == 0)
	{
		std::cout <<
			"Did you take a wrong turn? That's alright, just head on out. The chicken bar is right around the corner.\n"
			"\n"
			"Ending -1: Unplayed\n";
	}
	else if (globalWins > 10)
	{
		std::cout <<
			"Money? Sure, you got some. You left with " << globalMoney << "$, but that's not whats important here, what is, is victory."
			"And that? You have plenty of. " << globalWins << " times. That's your glory, your pride. That, is life.\n"
			"\n"
			"Ending 5: Hardened Winner\n";
	}
	else if (globalMoney <= 0)
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
			"Nothing ventured nothing gained, huh? Well, in your case, the only thing certian is the latter. That, and the remaining " << globalMoney << "$ in your pocket.\n"
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
			"That place tried something, and you ain't givin it nothing. Sure, ya didn't profit. What do you want me to say?\n"
			"Ya got out, and kept your wallet while you were at it. Could be worse, a lot worse.\n"
			"And ya had some fun too, eh? Won " << globalWins << " time(s).\n"
			"\n"
			"Ending 3: Even Steven.\n";
	}
	else if (globalMoney > 100)
	{
		std::cout <<
			"Damn, you did it. You went in expecting nothing, and left with more than you bargained for.\n"
			"Now? You go celebrate, in style. And you won " << globalWins << " time(s), too. That's nifty, eh?\n"
			"\n"
			"Ending 4: Undeniable victory.\n";
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