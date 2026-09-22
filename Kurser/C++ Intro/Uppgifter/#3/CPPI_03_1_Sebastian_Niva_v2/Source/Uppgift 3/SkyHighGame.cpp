#include "SkyHighGame.h"
#include "GenericFunctions.h"
#include "StatTracker.h"
#include "DisplayManager.h"
#include "InputController.h"
#include <iostream>

namespace SkyHighGame
{
	int Play(StatTracker::Stats& aStats, const PlayData& aPlayData)
	{
		int bet = GenericFunctions::GetBet(aStats.profits);

		for (int i = 0; i < aPlayData.multiplierArraySize; i++)
		{
			bool coinflip = 1 == GenericFunctions::RollDice(2);
			if (coinflip)
			{
				int theoreticalWinnings = static_cast<int>(bet * aPlayData.multiplierArray[i]);
				if (i >= aPlayData.multiplierArraySize - 1)
				{
					StatTracker::AddGame(aStats.wins, true);
					aStats.profits.money += theoreticalWinnings;
					std::cout <<
						"\nYou make it to your desination and get x " << aPlayData.multiplierArray[i] << " your bet!!!\n"
						"You win " << theoreticalWinnings << "$! \n";
					return theoreticalWinnings - bet;
				}

				std::cout <<
					"\nThe plane didn't crash!\n"
					"The current multiplier is: " << aPlayData.multiplierArray[i] << "x\n"
					"Do you want to:\n"
					"(1): Keep going\n"
					"(2): Jump out\n";

				std::cin.clear();

				enum class StayOrLeave
				{
					Stay,
					Leave,
					Count
				};
				switch (static_cast<StayOrLeave>(InputController::IntegerRange(static_cast<int>(StayOrLeave::Count)) - 1))
				{
					case StayOrLeave::Stay:
					{
						std::cout <<
							"You stay a little longer...\n";
						break;
					}
					case StayOrLeave::Leave:
					{
						StatTracker::AddGame(aStats.wins, true);
						aStats.profits.money += theoreticalWinnings;

						std::cout <<
							"\nYou get out in time, keeping a total of " << theoreticalWinnings << "$\n";
						return theoreticalWinnings - bet;
					}
					default:
						break;
				}
			}
			else
			{
				StatTracker::AddGame(aStats.wins, false);
				std::cout << static_cast<char>(7) <<
					"\nOH NO! The plane crashes! You loose it all!\n";
				return -bet;
			}
			system("pause");
		}
		//Not accessible, assuming the multiplier array is inputed correctly.
		return -1;
	}
}