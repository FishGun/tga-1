#include "Roulette.h"
#include "InputController.h"
#include "GenericFunctions.h"
#include "DisplayManager.h"
#include "Data.h"
#include "Player.h"
#include <iostream>
#include <array>

RouletteGame::RouletteGame() : RouletteGame::RouletteGame(Data::GenerateTableMoneyStruct(), RouletteGame::GenerateBoardStruct())
{

}
RouletteGame::RouletteGame(Data::TableMoneyStruct aTableMoneyStruct, const RouletteGame::BoardStruct aBoardStruct, RouletteGame::VictoryMultipliers aVictoryMultipliersStruct) : myTableMoneyStruct(aTableMoneyStruct), myBoardStruct(aBoardStruct)
{
	myVictoryMultipliersStruct = aVictoryMultipliersStruct;
}

int RouletteGame::Play(Player& aPlayer)
{
	system("cls");
	DisplayManager::SayMoneyStructData(myTableMoneyStruct);

	myBets =
	{
		.straight = {0},
		.redBlack = {0},
		.oddEven = {0},
		.column = {0},
		.straightTotal = 0,
		.redBlackTotal = 0,
		.oddEvenTotal = 0,
		.columnTotal = 0,
		.total = 0
	};

	do
	{
		BetLogicHandler(aPlayer);

		if (myBets.total >= myTableMoneyStruct.maxBet)
		{
			std::cout << "As you have reached the bet limit, you will have to let it roll!!!\n";
			system("pause");
			break;
		}
		if (aPlayer.GetMoney() < 1)
		{
			std::cout << "As you have no more money to bet, you will have to let it roll!!!\n";
			system("pause");
			break;
		}

		std::cout <<
			"\nWould you like to make another bet, or let it roll!?\n"
			"(1) Bet again!\n"
			"(2) Let it Roll!!!\n"
			"Awnser:";

	} while (InputController::IntegerRange(2) == 1);

	std::cout << "\nThe ball rolls...\n\n";
	system("pause");
	std::cout << std::endl;

	int result = GenericFunctions::RollDice(myBoardStruct.boardSize) - 1;

	return WinningsLogicHandler(aPlayer, result);
}

void RouletteGame::BetLogicHandler(Player& aPlayer)
{
	std::cout <<
		"What sort of bet would you like to make?\n"
		"(1) Straight number\n"
		"(2) Red or Black\n"
		"(3) Odd or Even\n"
		"(4) A column\n"
		"Awnser:";

	RouletteGame::BetTypes betType = static_cast<RouletteGame::BetTypes>(InputController::IntegerRange(static_cast<int>(RouletteGame::BetTypes::Count)) - 1);

	int betIndex;
	int bet = 0;
	switch (betType)
	{
		case RouletteGame::BetTypes::Straight:
		{
			std::cout <<
				"\nAlright! Which number are you betting on? (0-" << static_cast<int>(myBoardStruct.boardSize - 1) << ")\n"
				"Awnser:";
			betIndex = InputController::IntegerRange(myBoardStruct.boardSize, 0);
			bet = GenericFunctions::BetHandler(aPlayer, myTableMoneyStruct, myBets.total);
			myBets.straight[betIndex] += bet;
			myBets.straightTotal += bet;
			break;
		}
		case RouletteGame::BetTypes::RedBlack:
		{
			std::cout <<
				"\nAlright! Which color are you betting on?\n"
				"(1) Red\n"
				"(2) Black\n"
				"Awnser:";
			betIndex = InputController::IntegerRange(2) - 1;
			bet = GenericFunctions::BetHandler(aPlayer, myTableMoneyStruct, myBets.total);
			myBets.redBlack[betIndex] += bet;
			myBets.redBlackTotal += bet;
			break;
		}
		case RouletteGame::BetTypes::OddEven:
		{
			std::cout <<
				"\nAlright! Are you betting on odd, or even?\n"
				"(1) Odd\n"
				"(2) Even\n"
				"Awnser:";
			betIndex = InputController::IntegerRange(2) - 1;
			bet = GenericFunctions::BetHandler(aPlayer, myTableMoneyStruct, myBets.total);
			myBets.oddEven[betIndex] += bet;
			myBets.oddEvenTotal += bet;
			break;
		}
		case RouletteGame::BetTypes::Column:
		{
			std::cout <<
				"\nAlright! Which column are you betting on? (1-3)\n"
				"Awnser:";
			betIndex = InputController::IntegerRange(3) - 1;
			bet = GenericFunctions::BetHandler(aPlayer, myTableMoneyStruct, myBets.total);
			myBets.column[betIndex] += bet;
			myBets.columnTotal += bet;
			break;
		}
		default:
			break;
	}
	myBets.total += bet;
}

int RouletteGame::WinningsLogicHandler(Player& aPlayer, const int& aRolledNumber)
{
	RouletteGame::RouletteColor color = myBoardStruct.board[aRolledNumber];
	int column = 0;
	if (color != RouletteGame::RouletteColor::Green)
	{
		if (aRolledNumber % 3 == 0)
		{
			column = 3;
		}
		else
		{
			column = aRolledNumber % 3;
		}
	}

	const int straightProfit = static_cast<int>(myBets.straight[aRolledNumber] * myVictoryMultipliersStruct.straight);
	const int redBlackProfit = color == RouletteGame::RouletteColor::Green ? 0 : static_cast<int>(myBets.redBlack[static_cast<int>(color) - 1] * myVictoryMultipliersStruct.redBlack);
	const int oddEvenProfit = color == RouletteGame::RouletteColor::Green ? 0 : static_cast<int>(myBets.oddEven[(aRolledNumber + 1) % 2] * myVictoryMultipliersStruct.oddEven);
	const int columnProfit = color == RouletteGame::RouletteColor::Green ? 0 : static_cast<int>(myBets.column[column - 1] * myVictoryMultipliersStruct.column);

	std::cout << "The ball landed on #" << aRolledNumber << (color == RouletteGame::RouletteColor::Green ? " (green" : (color == RouletteGame::RouletteColor::Black ? " (black" : " (red")) << ", column #" << column << (column == 0 ? "-it was green" : "") << ")\n";
	if (myBets.straightTotal > 0)
	{
		if (straightProfit > 0)
		{
			std::cout << "You won " << straightProfit << "$ from your Staight bet!\n";
		}
		else
		{
			std::cout << "You didn't win from your Staight bet!\n";
		}
	}

	if (myBets.redBlackTotal > 0)
	{
		if (redBlackProfit > 0)
		{
			std::cout << "You won " << redBlackProfit << "$ from your Red/Black bet!\n";
		}
		else
		{
			std::cout << "You didn't win from your Red/Black bet!\n";
		}
	}

	if (myBets.oddEvenTotal > 0)
	{
		if (oddEvenProfit > 0)
		{
			std::cout << "You won " << oddEvenProfit << "$ from your Odd/Even bet!\n";
		}
		else
		{
			std::cout << "You didn't win from your Odd/Even bet!\n";
		}
	}

	if (myBets.columnTotal > 0)
	{
		if (columnProfit > 0)
		{
			std::cout << "You won " << columnProfit << "$ from your Column bet!\n";
		}
		else
		{
			std::cout << "You didn't win from your Column bet!\n";
		}
	}

	const int totalWinnings = straightProfit + redBlackProfit + oddEvenProfit + columnProfit;
	const int totalProfits = totalWinnings - myBets.total;

	std::cout << "From the total " << myBets.total << "$ you bet, you won " << totalWinnings << "$";
	if (totalProfits > 0)
	{
		std::cout << "! That's a nice profit of " << totalProfits << "$!\n";
	}
	else if (totalProfits < 0)
	{
		std::cout << ". You lost " << -totalProfits << "$\n";
	}
	else
	{
		std::cout << ". You ended up breaking even. Could be worse. We'll count that as a win.\n";
	}

	aPlayer += totalWinnings;
	myTableMoneyStruct.currentProfits += totalWinnings;
	return totalWinnings;
}

RouletteGame::BoardStruct RouletteGame::GenerateBoardStruct() const
{
	return BoardStruct
	{
		.board =
		{
			RouletteGame::RouletteColor::Green,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			//index #10 above.
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			//index #20 above.
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			//index #30 above.
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red,
			RouletteGame::RouletteColor::Black,
			RouletteGame::RouletteColor::Red
		}
	};
}
const Data::TableMoneyStruct& RouletteGame::GetTableMoneyStruct() const
{
	return myTableMoneyStruct;
}