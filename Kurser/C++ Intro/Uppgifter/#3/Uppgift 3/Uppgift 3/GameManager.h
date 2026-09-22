#pragma once
#include "Data.h"
#include "GuessingGame.h"
#include "OddOrEvenGame.h"
#include "SkyHighGame.h"
#include "CoinflipGame.h"
#include "Roulette.h"
#include "Player.h"

class GameManager
{
public:
	GameManager() = delete;
	GameManager(Player& aPlayer);



	enum class CasinoDataTypes
	{
		Default,
		BigWinner,
		FavourableOdds,
		RichBoyNoLimits
	};

	void StartPlaying();
	void ShowRules(Data::GameOptions aType, bool aClear = true);
	void StartAGame(Data::GameOptions aType);
	void AddGame(const bool aDidWin);

	void Enter();
	void Exit();
private:
	Player& myPlayer;

	GuessingGame myGuessingGameLowStakes;
	GuessingGame myGuessingGameHighStakes;
	OddOrEvenGame myOddOrEvenGame;
	SkyHighGame mySkyHighGame;
	CoinflipGame myCoinflipGame;
	RouletteGame myRouletteGame;
};