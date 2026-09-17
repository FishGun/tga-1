#include "GameManager.h"
#include "DisplayManager.h"
#include "InputController.h"
#include "StatTracker.h"
#include "GenericFunctions.h"
#include "MenuEnums.h"

#include "GuessingGame.h"
#include "OddOrEvenGame.h"
#include "SkyHighGame.h"
#include "CoinflipGame.h"
#include "Roulette.h"

#include <iostream>

namespace GameManager
{
	void StartPlaying()
	{
		Enter();

		GameData gameData = GenerateGameData(GameDataTypes::Default);

		while (true)
		{
			system("cls");
			DisplayManager::DisplayMoney(gameData.gameStats.profits);
			std::cout <<
				std::endl <<
				"Which game would you like to play?\n"
				"(1): Guess the number\n"
				"(2): Odd or Even?\n"
				"(3): Sky High!\n"
				"(4): Coinflip.\n"
				"(5): Roulette\n"
				"(6): See Game History\n"
				"(7): Leave\n";

			MenuEnums::GameOptions chosenOption = static_cast<MenuEnums::GameOptions>(InputController::IntegerRange(static_cast<int>(MenuEnums::GameOptions::Length)) - 1);
			switch (chosenOption)
			{
				case MenuEnums::GameOptions::Guess:
				case MenuEnums::GameOptions::OddOrEven:
				case MenuEnums::GameOptions::SkyHigh:
				case MenuEnums::GameOptions::Coinflip:
				case MenuEnums::GameOptions::Roulette:
					StartAGame(chosenOption, gameData);
					break;
				case MenuEnums::GameOptions::History:
					system("cls");
					DisplayManager::DisplayHistory(gameData.gameStats.wins, false);
					break;
				case MenuEnums::GameOptions::Exit:
					Exit(gameData.gameStats);
					return;
				default:
					break;
			}
			if (gameData.gameStats.profits.money <= 0)
			{
				Exit(gameData.gameStats);
				return;
			}
			system("pause");
		}
	}

	void ShowRules(MenuEnums::GameOptions aType, GameData& aGameData, bool aClear)
	{
		if (aClear)
		{
			system("cls");
		}
		switch (aType)
		{
			case MenuEnums::GameOptions::Guess:
			{
				std::cout <<
					"To play the Guessing Game is simple.\n"
					"First, you place your bet.\n"
					"Then, you guess a number between 2-12.\n"
					"Then, you roll two six sided dice.\n"
					"If they show what you guessed, you win " << aGameData.guessingPD.victoryMultiplier << " times your bet!\n"
					"If they don't, you loose your bet.\n"
					"\n";
				break;
			}
			case MenuEnums::GameOptions::OddOrEven:
			{
				std::cout <<
					"To play Odd or Even is simple.\n"
					"First, you place your bet.\n"
					"Then, pick either Odd or Even.\n"
					"Then, you roll two six sided dice.\n"
					"If they both show what you guessed, you win " << aGameData.oddOrEvenPD.victoryMultiplier << " times your bet!\n"
					"If they don't, you loose your bet.\n"
					"\n";
				break;
			}
			case MenuEnums::GameOptions::SkyHigh:
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
			case MenuEnums::GameOptions::Coinflip:
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
			case MenuEnums::GameOptions::Roulette:
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
	}

	void StartAGame(MenuEnums::GameOptions aType, GameData& aGameData)
	{
		system("cls");

		int gameTypeCastedToArrayIndex = static_cast<int>(aType);

		StatTracker::Stats& stats = aGameData.gameStats;
		StatTracker::Profits& profitStruct = stats.profits;
		int& localGameProfits = profitStruct.profitArray[gameTypeCastedToArrayIndex];
		int& money = profitStruct.money;


		if (GenericFunctions::CheckIfProfitedTooMuch(localGameProfits, false))
		{
			system("cls");
			std::cout << "Hey! You're too good at this game! Go play somewhere else!\n";
			return;
		}

		switch (aType)
		{
			case MenuEnums::GameOptions::Guess:
				std::cout << "Welcome to the Guessing Game table.\n\n";
				break;
			case MenuEnums::GameOptions::OddOrEven:
				std::cout << "Welcome to the Odd or Even table.\n\n";
				break;
			case MenuEnums::GameOptions::SkyHigh:
				std::cout << "Welcome to the Sky High table!\n\n";
				break;
			case MenuEnums::GameOptions::Coinflip:
				std::cout << "Welcome. To the Coinflip table.\n\n";
				break;
			case MenuEnums::GameOptions::Roulette:
				std::cout << "Welcome toooo- the Roulette table!\n\n";
				break;
			default:
				break;
		}
		ShowRules(aType, aGameData, false);

		bool isFirstLoop = true;
		while (true)
		{
			if (money < 1)
			{
				return;
			}
			else if (GenericFunctions::CheckIfProfitedTooMuch(localGameProfits, isFirstLoop))
			{
				std::cout << "Hey! You're too good at this game! Go play somewhere else!\n";
				return;
			}

			DisplayManager::DisplayMoney(profitStruct);
			std::cout << std::endl;

			const char* uniqueIntroSection[] =
			{
				"You are at the Guessing Game table. Would you like to:\n",
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
			switch (static_cast<MenuEnums::SpecificGameMenuOptions>(InputController::IntegerRange(static_cast<int>(MenuEnums::SpecificGameMenuOptions::Length)) - 1))
			{
				case MenuEnums::SpecificGameMenuOptions::Play:
				{
					system("cls");
					switch (aType)
					{
						case MenuEnums::GameOptions::Guess:
							localGameProfits += GuessingGame::Play(stats, aGameData.guessingPD);
							break;
						case MenuEnums::GameOptions::OddOrEven:
							localGameProfits += OddOrEvenGame::Play(stats, aGameData.oddOrEvenPD);
							break;
						case MenuEnums::GameOptions::SkyHigh:
							localGameProfits += SkyHighGame::Play(stats, aGameData.skyHighPD);
							break;
						case MenuEnums::GameOptions::Coinflip:
							localGameProfits += CoinflipGame::Play(stats, aGameData.coinflipPD);
							break;
						case MenuEnums::GameOptions::Roulette:
							localGameProfits += RouletteGame::Play(stats, aGameData.roulettePD);
						default:
							break;
					}
					DisplayManager::DisplayMoney(profitStruct);
					DisplayManager::DisplayHistory(stats.wins);
					system("pause");
					system("cls");
					break;
				}
				case MenuEnums::SpecificGameMenuOptions::Rules:
				{
					ShowRules(aType, aGameData);
					break;
				}
				case MenuEnums::SpecificGameMenuOptions::Exit:
				default:
					std::cout << "\nAlright, come back any time.\n";
					return;
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

	void Exit(StatTracker::Stats& aStats)
	{
		system("cls");
		const int money = aStats.profits.money;
		const int wins = aStats.wins.total;

		if (money == 100 && wins == 0)
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
		else if (money < 100)
		{
			std::cout <<
				"Cutting your losses & counting your victories, you know when it's time to get out, and move past the grand silver doors, into the cool evening air & busy streets\n"
				"You may not be a milionare, but you atleast have " << money << "$ left, and won a total of " << wins << " time(s), and that counts for something.\n"
				"\n"
				"Ending 2: Know when to fold 'em.\n";
		}
		else if (money == 100)
		{
			std::cout <<
				"That place tried something, and you ain't givin it nothing. Sure, ya didn't profit. What do you want me to say?\n"
				"Ya got out, and kept your wallet while you were at it. Could be worse, a lot worse.\n"
				"And ya had some fun too, eh? Won " << wins << " time(s).\n"
				"\n"
				"Ending 3: Even Steven.\n";
		}
		else if (money > 100)
		{
			std::cout <<
				"Damn, you did it. You went in expecting nothing, and left with more than you bargained for.\n"
				"Now? You go celebrate, in style. And you won " << wins << " time(s), too. That's nifty, eh?\n"
				"\n"
				"Ending 4: Undeniable victory.\n";
		}
		std::cout << std::endl;
		system("pause");
	}

	GameData GenerateGameData(GameDataTypes gameDataType)
	{
		switch (gameDataType)
		{
			//Standard GameData
			default:
			case GameDataTypes::Default:
				return
				{
					.gameStats =
					{
						.profits =
						{
							.profitArray = {0},
							.money = 100
						},
						.wins =
						{
							.gameHistory = {0},
							.total = 0,
						}
					},
					.guessingPD =
					{
						.victoryMultiplier = 5
					},
					.oddOrEvenPD =
					{
						.victoryMultiplier = 3
					},
					.skyHighPD =
					{
						.multiplierArray = { 1.2f, 1.5f, 2.0f, 3.0f, 5.0f, 8.0f ,12.0f ,20.0f }
					},
					.coinflipPD =
					{
						.victoryMultiplier = 1.9f
					},
					.roulettePD =
					{
						.colorArray =
						{
							RouletteGame::RouletteColor::Green,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							//index #10 above.
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							//index #20 above.
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							//index #30 above.
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red
						},
						.victoryMultipliers =
						{
							.straight = 36.0f,
							.redBlack = 2.0f,
							.oddEven = 2.0f,
							.column = 3.0f
						}
					}
				};
				//Big Winner GameData
			case GameDataTypes::BigWinner:
				return
				{
					.gameStats =
					{
						.profits =
						{
							.profitArray = {100,100,100,100,100},
							.money = 1000
						},
						.wins =
						{
							.gameHistory = {1,1,1,1,1},
							.total = 10,
						}
					},
					.guessingPD =
					{
						.victoryMultiplier = 5
					},
					.oddOrEvenPD =
					{
						.victoryMultiplier = 3
					},
					.skyHighPD =
					{
						.multiplierArray = { 1.2f, 1.5f, 2.0f, 3.0f, 5.0f, 8.0f ,12.0f ,20.0f }
					},
					.coinflipPD =
					{
						.victoryMultiplier = 1.9f
					},
					.roulettePD =
					{
						.colorArray =
						{
							RouletteGame::RouletteColor::Green,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							//index #10 above.
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							//index #20 above.
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							//index #30 above.
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red
						},
						.victoryMultipliers =
						{
							.straight = 36.0f,
							.redBlack = 2.0f,
							.oddEven = 2.0f,
							.column = 3.0f
						}
					}
				};
				//Favourable Casino GameData
			case GameDataTypes::FavourableOdds:
				return
				{
				.gameStats =
				{
					.profits =
					{
						.profitArray = {0},
						.money = 100
					},
					.wins =
					{
						.gameHistory = {0},
						.total = 0,
					}
				},
				.guessingPD =
				{
					.victoryMultiplier = 10
				},
				.oddOrEvenPD =
				{
					.victoryMultiplier = 5
				},
				.skyHighPD =
				{
					.multiplierArray = { 2.0f, 4.0f, 8.0f, 16.0f, 32.0f, 64.0f ,128.0f ,256.0f }
				},
				.coinflipPD =
				{
					.victoryMultiplier = 2.1f
				},
				.roulettePD =
				{
					.colorArray =
					{
						RouletteGame::RouletteColor::Green,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						//index #10 above.
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						//index #20 above.
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						//index #30 above.
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red,
						RouletteGame::RouletteColor::Black,
						RouletteGame::RouletteColor::Red
					},
					.victoryMultipliers =
					{
						.straight = 40.0f,
						.redBlack = 3.0f,
						.oddEven = 3.0f,
						.column = 4.0f
					}
				}
				};
			case GameDataTypes::RichBoyNoLimits:
				return
				{
				.gameStats =
				{
					.profits =
					{
						.profitArray = {-10000000,-10000000,-10000000,-10000000, -10000000},
						.money = 10000000
					},
					.wins =
					{
						.gameHistory = {0},
						.total = 0,
					}
				},
				.guessingPD =
					{
						.victoryMultiplier = 5
					},
					.oddOrEvenPD =
					{
						.victoryMultiplier = 3
					},
					.skyHighPD =
					{
						.multiplierArray = { 1.2f, 1.5f, 2.0f, 3.0f, 5.0f, 8.0f ,12.0f ,20.0f }
					},
					.coinflipPD =
					{
						.victoryMultiplier = 1.9f
					},
					.roulettePD =
					{
						.colorArray =
						{
							RouletteGame::RouletteColor::Green,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							//index #10 above.
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							//index #20 above.
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							//index #30 above.
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red,
							RouletteGame::RouletteColor::Black,
							RouletteGame::RouletteColor::Red
						},
						.victoryMultipliers =
						{
							.straight = 36.0f,
							.redBlack = 2.0f,
							.oddEven = 2.0f,
							.column = 3.0f
						}
					}
				};
		}
	}
}