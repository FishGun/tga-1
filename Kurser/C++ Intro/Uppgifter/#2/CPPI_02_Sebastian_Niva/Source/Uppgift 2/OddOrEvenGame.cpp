#include "OddOrEvenGame.h"
#include "GenericFunctions.h"
#include "InputController.h"
#include "StatTracker.h"
#include <iostream>

namespace OddOrEvenGame
{
	int Play(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct)
	{
		VictoryData victoryData =
		{
			.multiplier = 3
		};

		int bet = GenericFunctions::GetBet(aProfitStruct);

		std::cout <<
			"\n"
			"So, do you think the dice will be:\n"
			"(1): Odd\n"
			"(2): Even\n";

		std::cin.clear();

		enum class OddOrEven
		{
			Even,
			Odd,
			Length
		};
		OddOrEven guess = static_cast<OddOrEven>(InputController::IntegerRange(static_cast<int>(OddOrEven::Length)) % 2);


		int die2 = GenericFunctions::RollDice();
		int die1 = GenericFunctions::RollDice();
		OddOrEven die1Enumerated = static_cast<OddOrEven>(die1 % 2);
		OddOrEven die2Enumerated = static_cast<OddOrEven>(die2 % 2);

		std::cout <<
			"\n"
			"The first die, rolled " << die1 << "\n"
			"The second die, rolled " << die2 << "\n";

		if ((die1Enumerated == die2Enumerated) && (die1Enumerated == guess))
		{
			StatTracker::AddGame(aWinStruct, true);
			aProfitStruct.money += bet * victoryData.multiplier;
			std::cout <<
				"\nYou got it right! You win " << bet * victoryData.multiplier << "$!\n";
			return bet * victoryData.multiplier - bet;
		}
		else
		{
			StatTracker::AddGame(aWinStruct, false);
			std::cout <<
				"\nAlas, you lost.\n";
			return -bet;
		}
	}
}