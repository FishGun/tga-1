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

	void DisplayHistory(const Data::CasinoData& aCasinoData, const bool aInitialEmptyLine)
	{
		if (aInitialEmptyLine)
		{
			std::cout << "\n";
		}
		std::cout <<
			"Your last " << aCasinoData.gameHistoryArraySize << " games went like this:\n";

		for (int i = 0; i < aCasinoData.gameHistoryArraySize; i++)
		{
			if (aCasinoData.gameHistory[i] == 1)
			{
				std::cout << "Win!\n";
			}
			else if (aCasinoData.gameHistory[i] == -1)
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
}