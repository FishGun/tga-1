#pragma once
#include "Data.h"
#include "Player.h"

class SkyHighGame
{
public:
	SkyHighGame();
	SkyHighGame(Data::TableMoneyStruct aTableMoneyStruct);

	int Play(Player& aPlayer);

	const Data::TableMoneyStruct& GetTableMoneyStruct() const;
private:
	Data::TableMoneyStruct myTableMoneyStruct;
	static const int myMultiplierArraySize = 8;
	float myMultiplierArray[myMultiplierArraySize];
public:
	//SkyHighGame(Data::TableMoneyStruct aTableMoneyStruct, float aVictoryMultiplierArray[SkyHighGame::myMultiplierArraySize]);
};