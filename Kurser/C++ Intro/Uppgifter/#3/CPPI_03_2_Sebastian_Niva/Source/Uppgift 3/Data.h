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