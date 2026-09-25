#include "GenericFunctions.h"
#include "DisplayManager.h"
#include "InputController.h"
#include "Player.h"
#include "Data.h"
#include <random>
#include <iostream>

namespace GenericFunctions
{

	int RollDice(const int aSides, const int aAmount)
	{
		int toReturn = 0;

		std::random_device rDev;
		std::mt19937 rng(rDev());
		std::uniform_int_distribution < std::mt19937::result_type> dist(1, aSides);

		for (int i = 0; i < aAmount; i++)
		{
			toReturn += dist(rng);
		}

		return toReturn;
	}

	int BetHandler(Player& aPlayer, Data::TableMoneyStruct& aTableMoneyStruct, int aAlreadyMadeBetTotal)
	{
		std::cout << "How much would you like to bet, " << aPlayer.GetName() << "?\n";
		DisplayManager::DisplayMoney(aPlayer);
		std::cout << "$";
		const int& money = aPlayer.GetMoney();
		const int unboundedRealMaxBet = aTableMoneyStruct.maxBet - aAlreadyMadeBetTotal;
		const int boundedMaxBet = (aPlayer.NameIsJoel() ? money : money < unboundedRealMaxBet ? money : unboundedRealMaxBet);
		int bet = InputController::IntegerMinMaxRange(boundedMaxBet, aTableMoneyStruct.minBet);
		aPlayer -= bet;

		if (money == 0)
		{
			std::cout << "Woah! Going all-in, huh? Good luck...\n\n";
		}

		return bet;
	}

	bool CheckIfPoorOrBanned(const Player& aPlayer, const Data::TableMoneyStruct& aTableMoneyStruct, const bool aSayQuipOtherwhise)
	{
		return CheckIfTooPoor(aPlayer, aTableMoneyStruct) || CheckIfProfitedTooMuch(aTableMoneyStruct, aSayQuipOtherwhise);
	}

	bool CheckIfTooPoor(const Player& aPlayer, const Data::TableMoneyStruct& aTableMoneyStruct)
	{
		if (aPlayer.GetMoney() < aTableMoneyStruct.minBet || aPlayer.GetMoney() <= 0)
		{
			system("cls");
			std::cout << "You're too poor to play here!\n";
			return true;
		}
		return false;
	}

	// Should use StatTracker::Profits.profitArray (instead of "aProfit"), and have ProfitThresholds be in the StatTracker::Profits struct.
	// Could even have a custom profitThreashold for each game, by implementing another array in the StatTracker::Profits struct.
	// casinoData.gameStats.profits could then be passed in, along with a GameOptions enum for which game is being played.
	// Or maybe better, each PlayData could hold both local game profits, and profitThresholds, and then be passed.
	bool CheckIfProfitedTooMuch(const Data::TableMoneyStruct& aTableMoneyStruct, const bool aSayQuipOtherwhise)
	{
		const int profits = aTableMoneyStruct.currentProfits;

		if (profits >= aTableMoneyStruct.banValue)
		{
			system("cls");
			std::cout << "Hey! You're too good at this game! Go play somewhere else!\n";
			return true;
		}
		if (aSayQuipOtherwhise)
		{
			if (profits >= aTableMoneyStruct.highValue)
			{
				std::cout << "Hey, it's big winner! Carefull now, wouldn't wanna make too much, eh?\n\n";
			}
			else if (profits <= aTableMoneyStruct.lowValue)
			{
				std::cout << "Coming back here huh? Let's see if you have better luck this time...\n\n";
			}
			else
			{
				std::cout << "You aren't good enough for anyone to notice your presence. But not bad enough either, so there is that.\n\n";
			}
		}
		return false;
	}
}