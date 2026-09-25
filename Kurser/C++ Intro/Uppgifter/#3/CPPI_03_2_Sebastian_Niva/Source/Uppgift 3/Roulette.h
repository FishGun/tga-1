#pragma once
#include "Data.h"
#include "Player.h"
#include <array>



class RouletteGame
{
public:
	enum class RouletteColor
	{
		Green,
		Red,
		Black,
		Count
	};
	const struct BoardStruct
	{
		const static int boardSize = 37;
		const RouletteColor board[boardSize];

	};

	const struct VictoryMultipliers
	{
		float straight;
		float redBlack;
		float oddEven;
		float column;
	};

	RouletteGame();
	RouletteGame(Data::TableMoneyStruct aTableMoneyStruct, const BoardStruct aBoardStruct, VictoryMultipliers aVictoryMultipliersStruct = { .straight = 36.0f, .redBlack = 2.0f,.oddEven = 2.0f,.column = 3.0f });

	int Play(Player& aPlayer);

	const Data::TableMoneyStruct& GetTableMoneyStruct() const;

	enum class BetTypes
	{
		Straight,
		RedBlack,
		OddEven,
		Column,
		Count
	};

	const struct PlayData
	{
		static const int boardSize = 37;
		RouletteColor colorArray[boardSize];
		VictoryMultipliers victoryMultipliers;
	};

	const struct PlayerBets
	{
		std::array<int, PlayData::boardSize> straight;
		std::array<int, 2> redBlack;
		std::array<int, 2> oddEven;
		std::array<int, 3> column;
		int straightTotal;
		int redBlackTotal;
		int oddEvenTotal;
		int columnTotal;
		int total;
	};

	void BetLogicHandler(Player& aPlayer);
	int WinningsLogicHandler(Player& aPlayer, const int& aRolledNumber);
	BoardStruct GenerateBoardStruct() const;
private:
	PlayerBets myBets;
	Data::TableMoneyStruct myTableMoneyStruct;
	const BoardStruct myBoardStruct;
	VictoryMultipliers myVictoryMultipliersStruct;
};