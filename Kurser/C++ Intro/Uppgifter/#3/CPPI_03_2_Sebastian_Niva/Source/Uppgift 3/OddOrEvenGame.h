#pragma once
#include "Data.h"
#include "Player.h"

class OddOrEvenGame
{
public:
	OddOrEvenGame();
	OddOrEvenGame(Data::TableMoneyStruct aTableMoneyStruct, int aVictoryMultiplier = 3);

	int Play(Player& aPlayer);

	const Data::TableMoneyStruct& GetTableMoneyStruct() const;
private:
	Data::TableMoneyStruct myTableMoneyStruct;
	int myVictoryMultiplier;
};