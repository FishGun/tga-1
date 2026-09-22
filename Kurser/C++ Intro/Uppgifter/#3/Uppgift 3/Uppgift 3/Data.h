#pragma once

namespace Data
{
	enum class GameOptions
	{
		//Games
		Guess,
		GuessHigh,
		OddOrEven,
		SkyHigh,
		Coinflip,
		Roulette,
		//Extra
		History,
		Exit,
		Count
	};

	enum class SpecificGameMenuOptions
	{
		Play,
		Rules,
		Exit,
		Count
	};

	struct CasinoData
	{
		static const int gameHistoryArraySize = 5;
		int gameHistory[gameHistoryArraySize];
		int totalWins;

		/*
		const GuessingGame::PlayData guessingPD;
		const OddOrEvenGame::PlayData oddOrEvenPD;
		const SkyHighGame::PlayData skyHighPD;
		const CoinflipGame::PlayData coinflipPD;
		const RouletteGame::PlayData roulettePD;
		*/
	};

	struct TableMoneyStruct
	{
		int currentProfits;
		const int banValue;
		const int highValue;
		const int lowValue;
		const int minBet;
		const int maxBet;
	};

	TableMoneyStruct GenerateTableMoneyStruct(const int aMinBet = 1, const int aMaxBet = 100);
}