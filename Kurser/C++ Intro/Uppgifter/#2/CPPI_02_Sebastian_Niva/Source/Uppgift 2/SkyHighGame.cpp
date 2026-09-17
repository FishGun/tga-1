#include "SkyHighGame.h"
#include "GenericFunctions.h"
#include "StatTracker.h"
#include "DisplayManager.h"
#include "InputController.h"
#include <iostream>

namespace SkyHighGame
{
	int Play(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct)
	{
		VictoryData victoryData =
		{
			.multiplierArray = { 1.2f, 1.5f, 2.0f, 3.0f, 5.0f, 8.0f ,12.0f ,20.0f },
			.multiplierArraySize = 8
		};

		int bet = GenericFunctions::GetBet(aProfitStruct);

		for (int i = 0; i < victoryData.multiplierArraySize; i++)
		{
			bool coinFlip = static_cast<bool>(GenericFunctions::RollDice(2) - 1);
			if (coinFlip)
			{
				int theoreticalWinnings = static_cast<int>(bet * victoryData.multiplierArray[i]);
				if (i >= victoryData.multiplierArraySize - 1)
				{
					StatTracker::AddGame(aWinStruct, true);
					aProfitStruct.money += theoreticalWinnings;
					std::cout <<
						"\nYou make it to your desination and get x20 your bet!!!\n"
						"You win " << theoreticalWinnings << "$! \n";
					DisplayManager::DisplayMoney(aProfitStruct);
					DisplayManager::DisplayHistory(aWinStruct);
					system("pause");
					return theoreticalWinnings - bet;
				}

				std::cout <<
					"\nThe plane didn't crash!\n"
					"The current multiplier is: " << victoryData.multiplierArray[i] << "x\n"
					"Do you want to:\n"
					"(1): Keep going\n"
					"(2): Jump out\n";

				std::cin.clear();

				enum class StayOrLeave
				{
					Stay,
					Leave,
					Length
				};
				switch (static_cast<StayOrLeave>(InputController::IntegerRange(static_cast<int>(StayOrLeave::Length)) - 1))
				{
					case StayOrLeave::Stay:
					{
						std::cout <<
							"You stay a little longer...\n";
						break;
					}
					case StayOrLeave::Leave:
					{
						StatTracker::AddGame(aWinStruct, true);
						aProfitStruct.money += theoreticalWinnings;

						std::cout <<
							"You get out in time, keeping a total of " << theoreticalWinnings << "$\n";
						DisplayManager::DisplayMoney(aProfitStruct);
						DisplayManager::DisplayHistory(aWinStruct);
						system("pause");
						return theoreticalWinnings - bet;
					}
					default:
						break;
				}
			}
			else
			{
				StatTracker::AddGame(aWinStruct, false);
				std::cout << static_cast<char>(7) <<
					"OH NO! The plane crashes! You loose it all!\n";
				DisplayManager::DisplayHistory(aWinStruct);
				system("pause");
				return -bet;
			}
			system("pause");
		}
		return -1;
	}
}