#pragma once
#include "StatTracker.h"
#include "MenuEnums.h"
#include "GuessingGame.h"
#include "OddOrEvenGame.h"
#include "SkyHighGame.h"
#include "CoinflipGame.h"
#include "Roulette.h"

namespace GameManager
{
	struct GameData
	{
		StatTracker::Stats gameStats;

		const GuessingGame::PlayData guessingPD;
		const OddOrEvenGame::PlayData oddOrEvenPD;
		const SkyHighGame::PlayData skyHighPD;
		const CoinflipGame::PlayData coinflipPD;
		const RouletteGame::PlayData roulettePD;
	};

	enum class GameDataTypes
	{
		Default,
		BigWinner,
		FavourableOdds,
		RichBoyNoLimits
	};

	void StartPlaying();
	void ShowRules(MenuEnums::GameOptions aType, GameData& aGameData, bool aClear = true);
	void StartAGame(MenuEnums::GameOptions aType, GameData& aGameStats);

	void Enter();
	void Exit(StatTracker::Stats& aStats);
	GameData GenerateGameData(GameDataTypes gameDataType);
}