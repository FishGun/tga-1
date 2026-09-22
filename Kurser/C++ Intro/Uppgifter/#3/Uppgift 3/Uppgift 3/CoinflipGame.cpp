#include "CoinflipGame.h"
#include "InputController.h"
#include "GenericFunctions.h"
#include "DisplayManager.h"
#include "Data.h"
#include "Player.h"
#include <iostream>

CoinflipGame::CoinflipGame() : CoinflipGame::CoinflipGame(Data::GenerateTableMoneyStruct())
{

}
CoinflipGame::CoinflipGame(Data::TableMoneyStruct aTableMoneyStruct, float aVictoryMultiplier) : myTableMoneyStruct(aTableMoneyStruct)
{
	myVictoryMultiplier = aVictoryMultiplier;
}

int CoinflipGame::Play(Player& aPlayer)
{
	system("cls");
	DisplayManager::SayMoneyStructData(myTableMoneyStruct);

	int bet = GenericFunctions::BetHandler(aPlayer, myTableMoneyStruct);

	std::cout <<
		"(1) Heads\n"
		"or\n"
		"(2) Tails\n"
		"Guess:";

	enum class HeadsOrTails
	{
		Heads,
		Tails,
		Count
	};

	HeadsOrTails guess = static_cast<HeadsOrTails>(InputController::IntegerRange(static_cast<int>(HeadsOrTails::Count)) - 1);

	HeadsOrTails coin = static_cast<HeadsOrTails>(GenericFunctions::RollDice(static_cast<int>(HeadsOrTails::Count)) - 1);

	std::cout << "\nThe coin shows...\n";
	system("pause");

	std::cout << "\n" << (coin == HeadsOrTails::Heads ? "Heads" : "Tails");

	if (guess == coin)
	{
		std::cout <<
			"!\n"
			"You win!!!\n";
		int winnings = static_cast<int>(bet * myVictoryMultiplier);
		aPlayer += winnings;
		system("pause");
		system("cls");
		myTableMoneyStruct.currentProfits += winnings - bet;
		return winnings - bet;
	}
	else
	{
		std::cout <<
			".\n"
			"You lose.\n";
		system("pause");
		system("cls");
		myTableMoneyStruct.currentProfits -= bet;
		return -bet;
	}
}
const Data::TableMoneyStruct& CoinflipGame::GetTableMoneyStruct() const
{
	return myTableMoneyStruct;
}