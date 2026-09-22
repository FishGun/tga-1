#include "CoinflipGame.h"
#include "InputController.h"
#include "GenericFunctions.h"
#include "StatTracker.h"
#include <iostream>

namespace CoinflipGame
{
	int Play(StatTracker::Stats& aStats, const PlayData& aPlayData)
	{
		system("cls");

		int bet = GenericFunctions::GetBet(aStats.profits);

		std::cout <<
			"(1) Heads\n"
			"or\n"
			"(2) Tails\n"
			"Guess:";

		enum class HeadsOrTails
		{
			Heads,
			Tails,
			Count
		};

		HeadsOrTails guess = static_cast<HeadsOrTails>(InputController::IntegerRange(static_cast<int>(HeadsOrTails::Count))-1);

		HeadsOrTails coin = static_cast<HeadsOrTails>(GenericFunctions::RollDice(static_cast<int>(HeadsOrTails::Count))-1);

		std::cout << "\nThe coin shows...\n";
		system("pause");

		std::cout << "\n" << (coin == HeadsOrTails::Heads ? "Heads" : "Tails");

		if (guess == coin)
		{
			StatTracker::AddGame(aStats.wins, true);
			std::cout <<
				"!\n"
				"You win!!!\n";
			aStats.profits.money += static_cast<int>(bet * aPlayData.victoryMultiplier);
			system("pause");
			system("cls");
			return static_cast<int>(bet * aPlayData.victoryMultiplier) - bet;
		}
		else
		{
			StatTracker::AddGame(aStats.wins, false);
			std::cout <<
				".\n"
				"You lose.\n";
			system("pause");
			system("cls");
			return -bet;
		}
	}
}