#pragma once
#include "Data.h"
#include "Player.h"

class CoinflipGame
{
public:
	CoinflipGame();
	CoinflipGame(Data::TableMoneyStruct aTableMoneyStruct, float aVictoryMultiplier = 1.9f);

	int Play(Player& aPlayer);

	const Data::TableMoneyStruct& GetTableMoneyStruct() const;

private:
	Data::TableMoneyStruct myTableMoneyStruct;
	float myVictoryMultiplier;
};