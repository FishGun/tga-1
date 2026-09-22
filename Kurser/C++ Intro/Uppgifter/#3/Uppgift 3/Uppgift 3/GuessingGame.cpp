#include "GuessingGame.h"
#include "GenericFunctions.h"
#include "InputController.h"
#include "DisplayManager.h"
#include "Data.h"
#include "Player.h"
#include <iostream>

GuessingGame::GuessingGame() : GuessingGame::GuessingGame(Data::GenerateTableMoneyStruct())
{

}
GuessingGame::GuessingGame(Data::TableMoneyStruct aTableMoneyStruct, int aVictoryMultiplier) : myTableMoneyStruct(aTableMoneyStruct)
{
	myVictoryMultiplier = aVictoryMultiplier;
}

int GuessingGame::Play(Player& aPlayer)
{
	system("cls");
	DisplayManager::SayMoneyStructData(myTableMoneyStruct);

	int bet = GenericFunctions::BetHandler(aPlayer, myTableMoneyStruct);

	std::cout << "Your guess:";
	int guess = InputController::IntegerMinMaxRange(12, 2);

	int die1 = GenericFunctions::RollDice();
	int die2 = GenericFunctions::RollDice();
	int total = die1 + die2;

	std::cout << "\nThe dice rolled " << die1 << " & " << die2 << " for a total of: " << total << "!\n";

	if (total != guess)
	{
		std::cout << "\nOoh! Wrong guess! You loose!\n";
		myTableMoneyStruct.currentProfits -= bet;
		return -bet;
	}
	else
	{
		const int winnings = bet * myVictoryMultiplier;
		std::cout << "\n******************************************************************************" << (total > 9 ? "*\n" : "\n");
		std::cout << "*        Correct! You did it! Woohoo! The dice rolled " << total << "! You win " << winnings << "$!        *\n";
		std::cout << "******************************************************************************" << (total > 9 ? "*\n\n" : "\n\n");
		aPlayer += winnings;
		myTableMoneyStruct.currentProfits += winnings - bet;
		return winnings - bet;
	}
}

const Data::TableMoneyStruct& GuessingGame::GetTableMoneyStruct() const
{
	return myTableMoneyStruct;
}
