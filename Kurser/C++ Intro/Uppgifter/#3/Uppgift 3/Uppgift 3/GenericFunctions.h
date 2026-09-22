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
	int BetHandler(Player& aPlayer, Data::TableMoneyStruct& aTableMoneyStruct, int aAlreadyMadeBetTotal = 0);

	bool CheckIfPoorOrBanned(const Player& aPlayer, const Data::TableMoneyStruct& aTableMoneyStruct, const bool aSayQuipOtherwhise);
	bool CheckIfTooPoor(const Player& aPlayer, const Data::TableMoneyStruct& aTableMoneyStruct);
	bool CheckIfProfitedTooMuch(const Data::TableMoneyStruct& aTableMoneyStruct, const bool aSayQuipOtherwhise);
}