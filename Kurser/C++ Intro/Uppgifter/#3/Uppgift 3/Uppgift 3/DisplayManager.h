#pragma once
#include "Player.h"
#include "Data.h"

namespace DisplayManager
{
	void DisplayMoney(const Player& aPlayer);
	void DisplayHistory(Player& aPlayer, const bool aInitialEmptyLine = true);
	void SayMoneyStructData(const Data::TableMoneyStruct& aTableMoneyStruct);

}