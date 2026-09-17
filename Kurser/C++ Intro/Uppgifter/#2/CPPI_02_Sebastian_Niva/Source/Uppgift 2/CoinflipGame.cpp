#include "CoinflipGame.h"
#include "InputController.h"
#include "GenericFunctions.h"
#include "StatTracker.h"
#include <iostream>

namespace CoinflipGame
{
	int Play(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct)
	{
		VictoryData victoryData =
		{
			.multiplier = 1.9f
		};

		system("cls");

		int bet = GenericFunctions::GetBet(aProfitStruct);

		std::cout <<
			"(1) Heads\n"
			"or\n"
			"(2) Tails\n"
			"Guess:";

		enum class HeadsOrTails
		{
			Heads,
			Tails,
			Length
		};

		HeadsOrTails guess = static_cast<HeadsOrTails>(InputController::IntegerRange(static_cast<int>(HeadsOrTails::Length))-1);

		HeadsOrTails coin = static_cast<HeadsOrTails>(GenericFunctions::RollDice(static_cast<int>(HeadsOrTails::Length))-1);

		std::cout << "\nThe coin shows...\n";
		system("pause");

		std::cout << "\n" << (coin == HeadsOrTails::Heads ? "Heads" : "Tails");

		if (guess == coin)
		{
			StatTracker::AddGame(aWinStruct, true);
			std::cout <<
				"!\n"
				"You win!!!\n";
			aProfitStruct.money += static_cast<int>(bet * victoryData.multiplier);
			system("pause");
			system("cls");
			return static_cast<int>(bet * victoryData.multiplier) - bet;
		}
		else
		{
			StatTracker::AddGame(aWinStruct, false);
			std::cout <<
				".\n"
				"You lose.\n";
			system("pause");
			system("cls");
			return -bet;
		}
	}
}