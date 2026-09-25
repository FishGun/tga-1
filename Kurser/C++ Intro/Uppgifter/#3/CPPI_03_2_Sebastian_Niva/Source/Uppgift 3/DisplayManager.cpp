#include "DisplayManager.h"
#include "Player.h"
#include "Data.h"
#include <iostream>

namespace DisplayManager
{
	void DisplayMoney(const Player& aPlayer)
	{
		std::cout << "You currently have " << aPlayer.GetMoney() << "$ left.\n";
	}

	void DisplayHistory(Player& aPlayer, const bool aInitialEmptyLine)
	{
		Player::Wins& winsStruct = aPlayer.GetWinsStruct();
		if (aInitialEmptyLine)
		{
			std::cout << "\n";
		}
		std::cout <<
			"Your last " << winsStruct.gameHistoryArraySize << " games went like this:\n";

		for (int i = 0; i < winsStruct.gameHistoryArraySize; i++)
		{
			if (winsStruct.gameHistory[i] == 1)
			{
				std::cout << "Win!\n";
			}
			else if (winsStruct.gameHistory[i] == -1)
			{
				std::cout << "Loss!\n";
			}
			else
			{
				std::cout << "N/A\n";
			}
		}
		std::cout << "\n";
	}

	void SayMoneyStructData(const Data::TableMoneyStruct& aTableMoneyStruct)
	{
		std::cout << "The bet range is: " << aTableMoneyStruct.minBet << "$ to " << aTableMoneyStruct.maxBet << "$ You have profited " << aTableMoneyStruct.currentProfits << "/" << aTableMoneyStruct.banValue << "\n\n";
	}
}