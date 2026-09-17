#pragma once
#include "StatTracker.h"

namespace GameManager
{
	enum class GameOptions;

	enum class SpecificGameMenuOptions;

	void StartPlaying();
	void ShowRules(GameOptions aType, bool aClear = true);
	void StartAGame(GameOptions aType, StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct);

	void Enter();
	void Exit(StatTracker::Profits& aProfitStruct, StatTracker::Wins& aWinStruct);

}