#pragma once
#include "Data.h"
#include "Player.h"

class GuessingGame
{
public:
	GuessingGame();
	GuessingGame(Data::TableMoneyStruct aTableMoneyStruct, int aVictoryMultiplier = 5);

	int Play(Player& aPlayer);

	const Data::TableMoneyStruct& GetTableMoneyStruct() const;

private:
	Data::TableMoneyStruct myTableMoneyStruct;
	int myVictoryMultiplier;
};