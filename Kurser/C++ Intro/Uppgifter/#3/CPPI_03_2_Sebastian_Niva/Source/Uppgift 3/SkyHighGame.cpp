#include "SkyHighGame.h"
#include "GenericFunctions.h"
#include "Data.h"
#include "DisplayManager.h"
#include "InputController.h"
#include <iostream>
#include <assert.h>

SkyHighGame::SkyHighGame() : SkyHighGame::SkyHighGame(Data::GenerateTableMoneyStruct())
{

}
SkyHighGame::SkyHighGame(Data::TableMoneyStruct aTableMoneyStruct) : myTableMoneyStruct(aTableMoneyStruct)
{
	float multiplier = 1.25f;
	for (int i = 0; i < myMultiplierArraySize; i++)
	{
		myMultiplierArray[i] = multiplier;
		multiplier *= multiplier;
	}
	//myVictoryMultiplierArray = aVictoryMultiplierArray;
}


int SkyHighGame::Play(Player& aPlayer)
{
	system("cls");
	DisplayManager::SayMoneyStructData(myTableMoneyStruct);

	int bet = GenericFunctions::BetHandler(aPlayer, myTableMoneyStruct);

	for (int i = 0; i < myMultiplierArraySize; i++)
	{
		bool coinflip = 1 == GenericFunctions::RollDice(2);
		if (coinflip)
		{
			int theoreticalWinnings = static_cast<int>(bet * myMultiplierArray[i]);
			if (i >= myMultiplierArraySize - 1)
			{
				aPlayer += theoreticalWinnings;
				std::cout <<
					"\nYou make it to your desination and get x " << myMultiplierArray[i] << " your bet!!!\n"
					"You win " << theoreticalWinnings << "$! \n";
				myTableMoneyStruct.currentProfits += theoreticalWinnings - bet;
				return theoreticalWinnings - bet;
			}

			std::cout <<
				"\nThe plane didn't crash!\n"
				"The current multiplier is: " << myMultiplierArray[i] << "x\n"
				"Do you want to:\n"
				"(1): Keep going\n"
				"(2): Jump out\n";

			std::cin.clear();

			enum class StayOrLeave
			{
				Stay,
				Leave,
				Count
			};
			switch (static_cast<StayOrLeave>(InputController::IntegerRange(static_cast<int>(StayOrLeave::Count)) - 1))
			{
				case StayOrLeave::Stay:
				{
					std::cout <<
						"You stay a little longer...\n";
					break;
				}
				case StayOrLeave::Leave:
				{
					aPlayer += theoreticalWinnings;

					std::cout <<
						"\nYou get out in time, keeping a total of " << theoreticalWinnings << "$\n";
					myTableMoneyStruct.currentProfits += theoreticalWinnings - bet;
					return theoreticalWinnings - bet;
				}
				default:
					break;
			}
		}
		else
		{
			std::cout << static_cast<char>(7) <<
				"\nOH NO! The plane crashes! You loose it all!\n";
			myTableMoneyStruct.currentProfits -= bet;
			return -bet;
		}
		system("pause");
	}
	assert(false && "SkyHighGame illegal for-loop pass through.");
	return -1;
}
const Data::TableMoneyStruct& SkyHighGame::GetTableMoneyStruct() const
{
	return myTableMoneyStruct;
}