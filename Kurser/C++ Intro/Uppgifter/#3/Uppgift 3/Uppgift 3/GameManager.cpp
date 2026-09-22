#include "GameManager.h"
#include "DisplayManager.h"
#include "InputController.h"
#include "Data.h"
#include "GenericFunctions.h"

#include "GuessingGame.h"
#include "OddOrEvenGame.h"
#include "SkyHighGame.h"
#include "CoinflipGame.h"
#include "Roulette.h"

#include "player.h"

#include <iostream>
#include <assert.h>

GameManager::GameManager(Player& aPlayer) : myPlayer(aPlayer),
myGuessingGameHighStakes(Data::GenerateTableMoneyStruct(500, 5000))
//myGuessingGameLowStakes(Data::TableMoneyStruct{.currentProfits = 0, .banValue = 200, .highValue = 50, .lowValue = -50, .minBet = 0, .maxBet = 200}, 100)
{

}

void GameManager::StartPlaying()
{
	Enter();

	while (true)
	{
		system("cls");
		DisplayManager::DisplayMoney(myPlayer);
		std::cout <<
			std::endl <<
			"Which game would you like to play?\n"
			"(1): Guess the number\n"
			"(2): Guess the number (High Rollers)\n"
			"(3): Odd or Even?\n"
			"(4): Sky High!\n"
			"(5): Coinflip.\n"
			"(6): Roulette\n"
			"(7): See Game History\n"
			"(8): Leave\n";

		Data::GameOptions chosenOption = static_cast<Data::GameOptions>(InputController::IntegerRange(static_cast<int>(Data::GameOptions::Count)) - 1);
		switch (chosenOption)
		{
			case Data::GameOptions::Guess:
			case Data::GameOptions::GuessHigh:
			case Data::GameOptions::OddOrEven:
			case Data::GameOptions::SkyHigh:
			case Data::GameOptions::Coinflip:
			case Data::GameOptions::Roulette:
				StartAGame(chosenOption);
				break;
			case Data::GameOptions::History:
				system("cls");
				DisplayManager::DisplayHistory(myPlayer, false);
				break;
			case Data::GameOptions::Exit:
				Exit();
				return;
			default:
				assert(false && "Unexpected main menu choice.");
				break;
		}
		if (myPlayer.GetMoney() <= 0)
		{
			Exit();
			return;
		}
		system("pause");
	}
};

void GameManager::ShowRules(Data::GameOptions aType, bool aClear)
{
	if (aClear)
	{
		system("cls");
	}
	switch (aType)
	{
		case Data::GameOptions::Guess:
		case Data::GameOptions::GuessHigh:
		{
			std::cout <<
				"To play the Guessing Game is simple.\n"
				"First, you place your bet.\n"
				"Then, you guess a number between 2-12.\n"
				"Then, you roll two six sided dice.\n"
				"If they show what you guessed, you win five (5) times your bet!\n"
				"If they don't, you loose your bet.\n"
				"\n";
			break;
		}
		case Data::GameOptions::OddOrEven:
		{
			std::cout <<
				"To play Odd or Even is simple.\n"
				"First, you place your bet.\n"
				"Then, pick either Odd or Even.\n"
				"Then, you roll two six sided dice.\n"
				"If they both show what you guessed, you win three (3) times your bet!\n"
				"If they don't, you loose your bet.\n"
				"\n";
			break;
		}
		case Data::GameOptions::SkyHigh:
		{
			std::cout <<
				"To play Sky High is simple.\n"
				"First, you place your bet.\n"
				"Then, you either loose (50%), or incrase your possible earnings (50%).\n"
				"You may then decide to cash out, or go again.\n"
				"The increases are as follows:\n"
				"x1.2 | x1.5 | x2 | x3 | x5 | x8 | x12 | x20!\n"
				"\n";
			break;
		}
		case Data::GameOptions::Coinflip:
		{
			std::cout <<
				"To play Coinflip is simple.\n"
				"First, you place your bet.\n"
				"Then, you call heads or tails.\n"
				"Then, you flip The Coin.\n"
				"If it matches your call, you win one point nine (1.9) times your bet.\n"
				"If it doesn't, you loose your bet.\n";
			break;
		}
		case Data::GameOptions::Roulette:
		{
			std::cout <<
				"To play Roulette is simple.\n"
				"First, you decide how you want to bet.\n"
				"Then, you place your bet.\n"
				"You may keep doing this, untill all your bets are placed.\n"
				"Then, you spin the ball.\n"
				"If the ball lands on your bet, you win!\n"
				"If it doesn't, you loose your bet,\n"
				"\n"
				"The winnings are multiplied thusly:\n"
				"Straight: x36 | Red/Black: x2 | Odd/Even: x2 | Column: x3\n";
			break;
		}
		default:
			break;
	}
	system("pause");
	system("cls");
};

void GameManager::StartAGame(Data::GameOptions aType)
{
	system("cls");

	int gameTypeCastedToArrayIndex = static_cast<int>(aType);
	const Data::TableMoneyStruct* tableMoneyStructPointer;

	switch (aType)
	{
		case Data::GameOptions::Guess:
			std::cout << "Welcome to the Guessing Game table.\n\n";
			tableMoneyStructPointer = &myGuessingGameLowStakes.GetTableMoneyStruct();
			break;
		case Data::GameOptions::GuessHigh:
			std::cout << "Welcome to the High Roller's Guessing Game table.\n\n";
			tableMoneyStructPointer = &myGuessingGameHighStakes.GetTableMoneyStruct();
			break;
		case Data::GameOptions::OddOrEven:
			std::cout << "Welcome to the Odd or Even table.\n\n";
			tableMoneyStructPointer = &myOddOrEvenGame.GetTableMoneyStruct();
			break;
		case Data::GameOptions::SkyHigh:
			std::cout << "Welcome to the Sky High table!\n\n";
			tableMoneyStructPointer = &mySkyHighGame.GetTableMoneyStruct();
			break;
		case Data::GameOptions::Coinflip:
			std::cout << "Welcome. To the Coinflip table.\n\n";
			tableMoneyStructPointer = &myCoinflipGame.GetTableMoneyStruct();
			break;
		case Data::GameOptions::Roulette:
			std::cout << "Welcome toooo- the Roulette table!\n\n";
			tableMoneyStructPointer = &myRouletteGame.GetTableMoneyStruct();
			break;
		default:
			assert(false && "Game outside the games index");
			return;
	}
	const Data::TableMoneyStruct& tableMoneyStruct = *tableMoneyStructPointer;

	if (GenericFunctions::CheckIfPoorOrBanned(myPlayer, tableMoneyStruct, false))
	{
		return;
	}

	ShowRules(aType, false);

	bool isFirstLoop = true;
	while (true)
	{
		if (GenericFunctions::CheckIfPoorOrBanned(myPlayer, tableMoneyStruct, isFirstLoop))
		{
			return;
		}

		DisplayManager::DisplayMoney(myPlayer);
		std::cout << std::endl;

		const char* uniqueIntroSection[] =
		{
			"You are at the Low Stakes Guessing Game table. Would you like to:\n",
			"You are at the High Rollers Guessing Game table. Would you like to:\n",
			"You are at the Odd or Even table. Would you like to:\n",
			"You are at the Sky High table. Would you like to:\n",
			"You are at the Coinflip table. Would you like to:\n",
			"You are at the Roulette table. Would you like to:\n"
		};
		std::cout <<
			uniqueIntroSection[gameTypeCastedToArrayIndex] <<
			"(1): Play a round.\n"
			"(2): Learn the rules.\n"
			"(3): Leave the table.\n";
		switch (static_cast<Data::SpecificGameMenuOptions>(InputController::IntegerRange(static_cast<int>(Data::SpecificGameMenuOptions::Count)) - 1))
		{
			case Data::SpecificGameMenuOptions::Play:
			{
				system("cls");
				int currentPlayMoneyDifference = 0;
				switch (aType)
				{
					case Data::GameOptions::Guess:
						currentPlayMoneyDifference += myGuessingGameLowStakes.Play(myPlayer);
						break;
					case Data::GameOptions::GuessHigh:
						currentPlayMoneyDifference += myGuessingGameHighStakes.Play(myPlayer);
						break;
					case Data::GameOptions::OddOrEven:
						currentPlayMoneyDifference += myOddOrEvenGame.Play(myPlayer);
						break;
					case Data::GameOptions::SkyHigh:
						currentPlayMoneyDifference += mySkyHighGame.Play(myPlayer);
						break;
					case Data::GameOptions::Coinflip:
						currentPlayMoneyDifference += myCoinflipGame.Play(myPlayer);
						break;
					case Data::GameOptions::Roulette:
						currentPlayMoneyDifference += myRouletteGame.Play(myPlayer);
						break;
					default:
						assert(false && "Game outside the games index");
						break;
				}
				AddGame(currentPlayMoneyDifference >= 0);
				DisplayManager::DisplayMoney(myPlayer);
				DisplayManager::DisplayHistory(myPlayer);
				system("pause");
				system("cls");
				break;
			}
			case Data::SpecificGameMenuOptions::Rules:
			{
				ShowRules(aType);
				break;
			}
			case Data::SpecificGameMenuOptions::Exit:
			default:
				std::cout << "\nAlright, come back any time.\n";
				return;
		}
		isFirstLoop = false;
	}
};

void GameManager::AddGame(const bool aDidWin)
{
	Player::Wins& winsStruct = myPlayer.GetWinsStruct();
	for (int i = winsStruct.gameHistoryArraySize- 1; i > 0; i--)
	{
		winsStruct.gameHistory[i] = winsStruct.gameHistory[i - 1];
	}
	winsStruct.gameHistory[0] = (aDidWin ? 1 : -1);

	if (aDidWin)
	{
		winsStruct.total++;
	}
}

void GameManager::Enter()
{
	std::cout << "  ____________________________________________________________________________________________________________________\n";
	std::cout << " /                                                                                                                    \\\n";
	std::cout << "|   Welcome to Silver Sebastian's Casino! We are more than happy to take you to a rare state of economic possession!   |\n";
	std::cout << "|                                                Please, ENTER                                                         |\n";
	std::cout << " \\____________________________________________________________________________________________________________________/\n";
	std::cout << std::endl;
	system("pause");
};

void GameManager::Exit()
{
	system("cls");
	const int& money = myPlayer.GetMoney();
	const int& startingMoney = myPlayer.GetStartingMoney();
	const int& wins = myPlayer.GetWinsStruct().total;

	if (money == startingMoney && wins == 0)
	{
		std::cout <<
			"Did you take a wrong turn? That's alright, just head on out. The chicken bar is right around the corner.\n"
			"\n"
			"Ending -1: Unplayed\n";
	}
	else if (wins > 10)
	{
		std::cout <<
			"Money? Sure, you got some. You left with " << money << "$, but that's not whats important here, what is, is victory."
			"And that? You have plenty of. " << wins << " times. That's your glory, your pride. That, is life.\n"
			"\n"
			"Ending 5: Hardened Winner\n";
	}
	else if (money <= 0)
	{
		std::cout <<
			"Looks like this is the end of the road bud. You had a good run, you even won " << wins << " time(s), but now it's time to get out.\n"
			"Cheer up, you played your hand as good as you could. Its just that, well...\n"
			"The house always wins.\n"
			"\n"
			"Ending 1: Bankruptcy.\n";
	}
	else if (wins < 1)
	{
		std::cout <<
			"Nothing ventured nothing gained, huh? Well, in your case, the only thing certian is the latter. That, and the remaining " << money << "$ in your pocket.\n"
			"Ya should have stayed home, punk. The bettin' world 'aint for the feint of heart, and your short an ace.\n"
			"\n"
			"Ending 0: Betting Bad.\n";
	}
	else if (money < startingMoney)
	{
		std::cout <<
			"Cutting your losses & counting your victories, you know when it's time to get out, and move past the grand silver doors, into the cool evening air & busy streets\n"
			"You may not be a milionare, but you atleast have " << money << "$ left, and won a total of " << wins << " time(s), and that counts for something.\n"
			"\n"
			"Ending 2: Know when to fold 'em.\n";
	}
	else if (money == startingMoney)
	{
		std::cout <<
			"That place tried something, and you ain't givin it nothing. Sure, ya didn't profit. What do you want me to say?\n"
			"Ya got out, and kept your wallet while you were at it. Could be worse, a lot worse.\n"
			"And ya had some fun too, eh? Won " << wins << " time(s).\n"
			"\n"
			"Ending 3: Even Steven.\n";
	}
	else if (money > startingMoney)
	{
		std::cout <<
			"Damn, you did it. You went in expecting nothing, and left with more than you bargained for.\n"
			"Now? You go celebrate, in style. And you won " << wins << " time(s), too. That's nifty, eh?\n"
			"\n"
			"Ending 4: Undeniable victory.\n";
	}
	std::cout << std::endl;
	system("pause");
};