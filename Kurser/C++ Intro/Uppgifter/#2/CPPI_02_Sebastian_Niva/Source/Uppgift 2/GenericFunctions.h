#pragma once
#include "StatTracker.h"
#include <random>

namespace GenericFunctions
{
	struct ProfitThresholds
	{
		int banValue;
		int highValue;
		int lowValue;
	};
	int RollDice(int aSides = 6, int aAmount = 1);
	int GetBet(StatTracker::Profits& aProfitStruct);
	bool CheckIfProfitedTooMuch(const int aProfit, bool aSayQuipOtherwhise = true);
}