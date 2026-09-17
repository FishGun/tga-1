#include "GenericFunctions.h"
#include "DisplayManager.h"
#include "InputController.h"
#include "StatTracker.h"
#include <random>
#include <iostream>

namespace GenericFunctions
{

	int RollDice(const int aSides, const int aAmount)
	{
		int toReturn = 0;

		std::random_device rDev;
		std::mt19937 rng(rDev());
		std::uniform_int_distribution < std::mt19937::result_type> dist(1, aSides);

		for (int i = 0; i < aAmount; i++)
		{
			toReturn += dist(rng);
		}

		return toReturn;
	}

	int GetBet(StatTracker::Profits& aProfitStruct)
	{
		std::cout << "How much would you like to bet?\n";
		DisplayManager::DisplayMoney(aProfitStruct);
		std::cout << "$";
		int bet = InputController::IntegerMinMaxRange(aProfitStruct.money);
		aProfitStruct.money -= bet;

		if (aProfitStruct.money == 0)
		{
			std::cout << "Woah! Going all-in, huh? Good luck...\n\n";
		}

		return bet;
	}

	// Should use StatTracker::Profits.profitArray (instead of "aProfit"), and have ProfitThresholds be in the StatTracker::Profits struct.
	// Could even have a custom profitThreashold for each game, by implementing another array in the StatTracker::Profits struct.
	// gameData.gameStats.profits could then be passed in, along with a GameOptions enum for which game is being played.
	// Or maybe better, each PlayData could hold both local game profits, and profitThresholds, and then be passed.
	bool CheckIfProfitedTooMuch(const int aProfit, const bool aSayQuipOtherwhise)
	{
		ProfitThresholds profitThresholds =
		{
			.banValue = 100,
			.highValue = 20,
			.lowValue = -20
		};

		if (aProfit >= profitThresholds.banValue)
		{
			return true;
		}
		if (aSayQuipOtherwhise)
		{
			if (aProfit >= profitThresholds.highValue)
			{
				std::cout << "Hey, it's big winner! Carefull now, wouldn't wanna make too much, eh?\n\n";
			}
			else if (aProfit <= profitThresholds.lowValue)
			{
				std::cout << "Coming back here huh? Let's see if you have better luck this time...\n\n";
			}
			else
			{
				std::cout << "You aren't good enough for anyone to notice your presence. But not bad enough either, so there is that.\n\n";
			}
		}
		return false;
	}
}