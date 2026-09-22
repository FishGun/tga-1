#pragma once
#include "Player.h"
#include "Data.h"

namespace DisplayManager
{
	void DisplayMoney(const Player& aPlayer);
	void DisplayHistory(const Data::CasinoData& aCasinoData, const bool aInitialEmptyLine = true);
}