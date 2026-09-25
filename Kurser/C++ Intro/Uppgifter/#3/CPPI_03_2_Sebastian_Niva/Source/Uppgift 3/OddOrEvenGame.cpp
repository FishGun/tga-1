#include "OddOrEvenGame.h"
#include "GenericFunctions.h"
#include "InputController.h"
#include "DisplayManager.h"
#include "Data.h"
#include "Player.h"
#include <iostream>

OddOrEvenGame::OddOrEvenGame() : OddOrEvenGame::OddOrEvenGame(Data::GenerateTableMoneyStruct())
{

}
OddOrEvenGame::OddOrEvenGame(Data::TableMoneyStruct aTableMoneyStruct, int aVictoryMultiplier) : myTableMoneyStruct(aTableMoneyStruct)
{
	myVictoryMultiplier = aVictoryMultiplier;
}

int OddOrEvenGame::Play(Player& aPlayer)
{
	system("cls");
	DisplayManager::SayMoneyStructData(myTableMoneyStruct);

	int bet = GenericFunctions::BetHandler(aPlayer, myTableMoneyStruct);

	std::cout <<
		"\n"
		"So, do you think the dice will be:\n"
		"(1): Odd\n"
		"(2): Even\n";

	std::cin.clear();

	enum class OddOrEven
	{
		Even,
		Odd,
		Count
	};
	OddOrEven guess = static_cast<OddOrEven>(InputController::IntegerRange(static_cast<int>(OddOrEven::Count)) % 2);


	int die2 = GenericFunctions::RollDice();
	int die1 = GenericFunctions::RollDice();
	OddOrEven die1Enumerated = static_cast<OddOrEven>(die1 % 2);
	OddOrEven die2Enumerated = static_cast<OddOrEven>(die2 % 2);

	std::cout <<
		"\n"
		"The first die, rolled " << die1 << "\n"
		"The second die, rolled " << die2 << "\n";

	if ((die1Enumerated == die2Enumerated) && (die1Enumerated == guess))
	{
		const int winnings = bet * myVictoryMultiplier;
		aPlayer += winnings;
		std::cout <<
			"\nYou got it right! You win " << winnings << "$!\n";
		myTableMoneyStruct.currentProfits += winnings - bet;
		return winnings - bet;
	}
	else
	{
		std::cout <<
			"\nAlas, you lost.\n";
		myTableMoneyStruct.currentProfits -= bet;
		return -bet;
	}
}
const Data::TableMoneyStruct& OddOrEvenGame::GetTableMoneyStruct() const
{
	return myTableMoneyStruct;
}