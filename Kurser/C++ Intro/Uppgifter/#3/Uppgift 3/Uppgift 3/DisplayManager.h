#pragma once
#include "StatTracker.h"

namespace DisplayManager
{
	void DisplayMoney(StatTracker::Profits& aProfitStruct);
	void DisplayHistory(StatTracker::Wins& aWinStruct, bool aInitialEmptyLine = true);
}