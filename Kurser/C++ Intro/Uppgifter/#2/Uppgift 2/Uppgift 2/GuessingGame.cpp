#include "GuessingGame.h"
#include "GenericFunctions.h"
#include "InputController.h"
#include "StatTracker.h"
#include <iostream>

namespace GuessingGame
{
	int Play(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct)
	{
		VictoryData victoryData = {
			.multiplier = 5
		};

		system("cls");

		int bet = GenericFunctions::GetBet(aProfitStruct);

		std::cout << "Your guess:";
		int guess = InputController::IntegerMinMaxRange(12,2);

		int die1 = GenericFunctions::RollDice();
		int die2 = GenericFunctions::RollDice();
		int total = die1 + die2;

		std::cout << "\nThe dice rolled " << die1 << " & " << die2 << " for a total of: " << total << "!\n";

		if (total != guess)
		{
			StatTracker::AddGame(aWinStruct, false);
			std::cout << "\nOoh! Wrong guess! You loose!\n";
			return -bet;
		}
		else
		{
			StatTracker::AddGame(aWinStruct, true);
			std::cout << "\n******************************************************************************" << (total > 9 ? "*\n" : "\n");
			std::cout << "*        Correct! You did it! Woohoo! The dice rolled " << total << "! You win " << bet * victoryData.multiplier << "$!        *\n";
			std::cout << "******************************************************************************" << (total > 9 ? "*\n\n" : "\n\n");
			aProfitStruct.money += bet * victoryData.multiplier;
			return bet * victoryData.multiplier - bet;
		}
	}
}