#include "GuessingGame.h"
#include "GenericFunctions.h"
#include "InputController.h"
#include "StatTracker.h"
#include <iostream>

namespace GuessingGame
{
	int Play(StatTracker::Stats& aStats, const PlayData &aPlayData)
	{
		system("cls");

		int bet = GenericFunctions::GetBet(aStats.profits);

		std::cout << "Your guess:";
		int guess = InputController::IntegerMinMaxRange(12,2);

		int die1 = GenericFunctions::RollDice();
		int die2 = GenericFunctions::RollDice();
		int total = die1 + die2;

		std::cout << "\nThe dice rolled " << die1 << " & " << die2 << " for a total of: " << total << "!\n";

		if (total != guess)
		{
			StatTracker::AddGame(aStats.wins, false);
			std::cout << "\nOoh! Wrong guess! You loose!\n";
			return -bet;
		}
		else
		{
			StatTracker::AddGame(aStats.wins, true);
			std::cout << "\n******************************************************************************" << (total > 9 ? "*\n" : "\n");
			std::cout << "*        Correct! You did it! Woohoo! The dice rolled " << total << "! You win " << bet * aPlayData.victoryMultiplier << "$!        *\n";
			std::cout << "******************************************************************************" << (total > 9 ? "*\n\n" : "\n\n");
			aStats.profits.money += bet * aPlayData.victoryMultiplier;
			return bet * aPlayData.victoryMultiplier - bet;
		}
	}
}