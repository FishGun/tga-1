#include "GameManager.h"
#include "DisplayManager.h"
#include "InputController.h"
#include "StatTracker.h"
#include "GenericFunctions.h"

#include "GuessingGame.h"
#include "OddOrEvenGame.h"
#include "SkyHighGame.h"
#include "CoinflipGame.h"

#include <iostream>

namespace GameManager
{
	enum class GameOptions
	{
		Guess = 0,
		OddOrEven = 1,
		SkyHigh = 2,
		Coinflip = 3,
		History = 4,
		Exit = 5,
		Length = 6
	};

	enum class SpecificGameMenuOptions
	{
		Play = 0,
		Rules = 1,
		Exit = 2,
		Length = 3
	};

	void StartPlaying()
	{
		Enter();

		StatTracker::Profits profits =
		{
			.profitArray = {0},
			.money = 100
		};

		StatTracker::Wins wins =
		{
			.gameHistory = {0},
			.total = 0,
			.gameHistoryArraySize = 5
		};

		while (true)
		{
			system("cls");
			DisplayManager::DisplayMoney(profits);
			std::cout <<
				std::endl <<
				"Which game would you like to play?\n"
				"(1): Guess the number\n"
				"(2): Odd or Even?\n"
				"(3): Sky High!\n"
				"(4): Coinflip.\n"
				"(5): See Game History\n"
				"(6): Leave\n";

			switch (static_cast<GameOptions>(InputController::IntegerRange(static_cast<int>(GameOptions::Length))-1))
			{
				case GameOptions::Guess:
					StartAGame(GameOptions::Guess, profits, wins);
					break;
				case GameOptions::OddOrEven:
					StartAGame(GameOptions::OddOrEven, profits, wins);
					break;
				case GameOptions::SkyHigh:
					StartAGame(GameOptions::SkyHigh, profits, wins);
					break;
				case GameOptions::Coinflip:
					StartAGame(GameOptions::Coinflip, profits, wins);
					break;
				case GameOptions::History:
					system("cls");
					DisplayManager::DisplayHistory(wins, false);
					break;
				case GameOptions::Exit:
					Exit(profits, wins);
					return;
				default:
					break;
			}
			if (profits.money <= 0)
			{
				Exit(profits, wins);
				return;
			}
			system("pause");
		}
	}

	void ShowRules(GameOptions aType, bool aClear)
	{
		if (aClear)
		{
			system("cls");
		}
		switch (aType)
		{
			case GameOptions::Guess:
				std::cout <<
					"To play the Guessing Game is simple.\n"
					"First, you place your bet.\n"
					"Then, you guess a number between 2-12.\n"
					"Then, you roll two six sided dice.\n"
					"If they show what you guessed, you win five (5) times your bet!\n"
					"If they don't, you loose your bet.\n"
					"\n";
				break;
			case GameOptions::OddOrEven:
				std::cout <<
					"To play Odd or Even is simple.\n"
					"First, you place your bet.\n"
					"Then, pick either Odd or Even.\n"
					"Then, you roll two six sided dice.\n"
					"If they both show what you guessed, you win three (3) times your bet!\n"
					"If they don't, you loose your bet.\n"
					"\n";
				break;
			case GameOptions::SkyHigh:
				std::cout <<
					"To play Sky High is simple.\n"
					"First, you place your bet.\n"
					"Then, you either loose (50%), or incrase your possible earnings (50%).\n"
					"You may then decide to cash out, or go again.\n"
					"The increases are as follows:\n"
					"x1.2 | x1.5 | x2 | x3 | x5 | x8 | x12 | x20!\n"
					"\n";
				break;
			case GameOptions::Coinflip:
				std::cout <<
					"To play Coinflip is simple.\n"
					"First, you place your bet.\n"
					"Then, you call heads or tails.\n"
					"Then, you flip The Coin.\n"
					"If it matches your call, you win one point nine (1.9) times your bet.\n"
					"If it doesn't, you loose your bet.\n";
				break;
			default:
				break;
		}
		system("pause");
		system("cls");
	}

	void StartAGame(GameOptions aType, StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct)
	{
		system("cls");
		int gameTypeCastedToArrayIndex = static_cast<int>(aType) - 1;

		if (GenericFunctions::CheckIfProfitedTooMuch(aProfitStruct.profitArray[gameTypeCastedToArrayIndex], false))
		{
			system("cls");
			std::cout << "Hey! You're too good at this game! Go play somewhere else!\n";
			return;
		}

		switch (aType)
		{
			case GameOptions::Guess:
				std::cout << "Welcome to the Guessing Game table.\n\n";
				break;
			case GameOptions::OddOrEven:
				std::cout << "Welcome to the Odd or Even table.\n\n";
				break;
			case GameOptions::SkyHigh:
				std::cout << "Welcome to the Sky High table!\n\n";
				break;
			case GameOptions::Coinflip:
				std::cout << "Welcome. To the Coinflip table.\n\n";
				break;
			default:
				break;
		}
		ShowRules(aType, false);

		bool isFirstLoop = true;
		while (true)
		{
			if (aProfitStruct.money < 1)
			{
				return;
			}
			else if (GenericFunctions::CheckIfProfitedTooMuch(aProfitStruct.profitArray[gameTypeCastedToArrayIndex], isFirstLoop))
			{
				std::cout << "Hey! You're too good at this game! Go play somewhere else!\n";
				return;
			}

			switch (aType)
			{
				case GameOptions::Guess:
				{
					DisplayManager::DisplayMoney(aProfitStruct);
					std::cout << std::endl;
					std::cout <<
						"You are at the guessing game table. Would you like to:\n"
						"(1): Play a round.\n"
						"(2): Learn the rules.\n"
						"(3): Leave the table.\n";
					switch (static_cast<SpecificGameMenuOptions>(InputController::IntegerRange(static_cast<int>(SpecificGameMenuOptions::Length)) - 1))
					{
						case SpecificGameMenuOptions::Play:
							system("cls");
							aProfitStruct.profitArray[gameTypeCastedToArrayIndex] += GuessingGame::Play(aProfitStruct, aWinStruct);
							DisplayManager::DisplayMoney(aProfitStruct);
							DisplayManager::DisplayHistory(aWinStruct);
							system("pause");
							system("cls");
							break;
						case SpecificGameMenuOptions::Rules:
							ShowRules(aType);
							break;
						case SpecificGameMenuOptions::Exit:
						default:
							std::cout << "\nAlright, come back any time.\n";
							return;
					}
				}
				break;
				case GameOptions::OddOrEven:
				{
					DisplayManager::DisplayMoney(aProfitStruct);
					std::cout << std::endl;
					std::cout <<
						"You are at the Odd or Even table. Would you like to:\n"
						"(1): Play a round.\n"
						"(2): Learn the rules.\n"
						"(3): Leave the table.\n";
					switch (static_cast<SpecificGameMenuOptions>(InputController::IntegerRange(static_cast<int>(SpecificGameMenuOptions::Length)) - 1))
					{
						case SpecificGameMenuOptions::Play:
							system("cls");
							aProfitStruct.profitArray[gameTypeCastedToArrayIndex] += OddOrEvenGame::Play(aProfitStruct, aWinStruct);
							DisplayManager::DisplayMoney(aProfitStruct);
							DisplayManager::DisplayHistory(aWinStruct);
							system("pause");
							system("cls");
							break;
						case SpecificGameMenuOptions::Rules:
							ShowRules(aType);
							break;
						case SpecificGameMenuOptions::Exit:
						default:
							std::cout << "\nAlright, come back any time.\n";
							return;
					}
				}
				break;
				case GameOptions::SkyHigh:
				{
					DisplayManager::DisplayMoney(aProfitStruct);
					std::cout << std::endl;
					std::cout <<
						"You are at the Sky High table. Would you like to:\n"
						"(1): Play a round.\n"
						"(2): Learn the rules.\n"
						"(3): Leave the table.\n";
					switch (static_cast<SpecificGameMenuOptions>(InputController::IntegerRange(static_cast<int>(SpecificGameMenuOptions::Length)) - 1))
					{
						case SpecificGameMenuOptions::Play:
							system("cls");
							aProfitStruct.profitArray[gameTypeCastedToArrayIndex] += SkyHighGame::Play(aProfitStruct, aWinStruct);
							system("cls");
							break;
						case SpecificGameMenuOptions::Rules:
							ShowRules(aType);
							break;
						case SpecificGameMenuOptions::Exit:
						default:
							std::cout << "\nAlright, come back any time.\n";
							return;
					}
				}
				break;
				case GameOptions::Coinflip:
				{
					DisplayManager::DisplayMoney(aProfitStruct);
					std::cout << std::endl;
					std::cout <<
						"You are at the Coinflip table. Would you like to:\n"
						"(1): Play a round.\n"
						"(2): Learn the rules.\n"
						"(3): Leave the table.\n";
					switch (static_cast<SpecificGameMenuOptions>(InputController::IntegerRange(static_cast<int>(SpecificGameMenuOptions::Length))-1))
					{
						case SpecificGameMenuOptions::Play:
							aProfitStruct.profitArray[gameTypeCastedToArrayIndex] += CoinflipGame::Play(aProfitStruct, aWinStruct);
							break;
						case SpecificGameMenuOptions::Rules:
							ShowRules(aType);
							break;
						case SpecificGameMenuOptions::Exit:
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

	void Exit(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct)
	{
		system("cls");

		if (aProfitStruct.money == 100 && aWinStruct.total == 0)
		{
			std::cout <<
				"Did you take a wrong turn? That's alright, just head on out. The chicken bar is right around the corner.\n"
				"\n"
				"Ending -1: Unplayed\n";
		}
		else if (aWinStruct.total > 10)
		{
			std::cout <<
				"Money? Sure, you got some. You left with " << aProfitStruct.money << "$, but that's not whats important here, what is, is victory."
				"And that? You have plenty of. " << aWinStruct.total << " times. That's your glory, your pride. That, is life.\n"
				"\n"
				"Ending 5: Hardened Winner\n";
		}
		else if (aProfitStruct.money <= 0)
		{
			std::cout <<
				"Looks like this is the end of the road bud. You had a good run, you even won " << aWinStruct.total << " time(s), but now it's time to get out.\n"
				"Cheer up, you played your hand as good as you could. Its just that, well...\n"
				"The house always wins.\n"
				"\n"
				"Ending 1: Bankruptcy.\n";
		}
		else if (aWinStruct.total < 1)
		{
			std::cout <<
				"Nothing ventured nothing gained, huh? Well, in your case, the only thing certian is the latter. That, and the remaining " << aProfitStruct.money << "$ in your pocket.\n"
				"Ya should have stayed home, punk. The bettin' world 'aint for the feint of heart, and your short an ace.\n"
				"\n"
				"Ending 0: Betting Bad.\n";
		}
		else if (aProfitStruct.money < 100)
		{
			std::cout <<
				"Cutting your losses & counting your victories, you know when it's time to get out, and move past the grand silver doors, into the cool evening air & busy streets\n"
				"You may not be a milionare, but you atleast have " << aProfitStruct.money << "$ left, and won a total of " << aWinStruct.total << " time(s), and that counts for something.\n"
				"\n"
				"Ending 2: Know when to fold 'em.\n";
		}
		else if (aProfitStruct.money == 100)
		{
			std::cout <<
				"That place tried something, and you ain't givin it nothing. Sure, ya didn't profit. What do you want me to say?\n"
				"Ya got out, and kept your wallet while you were at it. Could be worse, a lot worse.\n"
				"And ya had some fun too, eh? Won " << aWinStruct.total << " time(s).\n"
				"\n"
				"Ending 3: Even Steven.\n";
		}
		else if (aProfitStruct.money > 100)
		{
			std::cout <<
				"Damn, you did it. You went in expecting nothing, and left with more than you bargained for.\n"
				"Now? You go celebrate, in style. And you won " << aWinStruct.total << " time(s), too. That's nifty, eh?\n"
				"\n"
				"Ending 4: Undeniable victory.\n";
		}
		std::cout << std::endl;
		system("pause");
	}
}