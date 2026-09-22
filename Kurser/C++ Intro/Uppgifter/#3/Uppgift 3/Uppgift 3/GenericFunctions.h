#pragma once
#include "Player.h"
#include "Data.h"

namespace GenericFunctions
{
	struct ProfitThresholds
	{
		int banValue;
		int highValue;
		int lowValue;
	};
	int RollDice(const int aSides = 6, const int aAmount = 1);
	int BetHandler(Player& aPlayer);
	bool CheckIfProfitedTooMuch(const Data::TableMoneyStruct& aTableMoneyStruct, const bool aSayQuipOtherwhise);
}