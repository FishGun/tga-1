#include "Roulette.h"
#include "InputController.h"
#include "GenericFunctions.h"
#include "StatTracker.h"
#include <iostream>
#include <array>

namespace RouletteGame
{
	int Play(StatTracker::Stats& aStats, const PlayData& aPlayData)
	{
		PlayerBets bets =
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

		system("cls");

		do
		{
			BetLogicHandler(aStats.profits, aPlayData.boardSize, bets);

			if (aStats.profits.money < 1)
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

		int result = GenericFunctions::RollDice(aPlayData.boardSize) - 1;

		return WinningsLogicHandler(aStats, aPlayData, bets, result);
	}

	void BetLogicHandler(StatTracker::Profits& aProfitStruct, const int& aBoardSize, PlayerBets& aBets)
	{
		std::cout <<
			"What sort of bet would you like to make?\n"
			"(1) Straight number\n"
			"(2) Red or Black\n"
			"(3) Odd or Even\n"
			"(4) A column\n"
			"Awnser:";

		BetTypes betType = static_cast<BetTypes>(InputController::IntegerRange(static_cast<int>(BetTypes::Length)) - 1);

		int betIndex;
		int bet = 0;
		switch (betType)
		{
			case BetTypes::Straight:
			{
				std::cout <<
					"\nAlright! Which number are you betting on? (0-" << static_cast<int>(aBoardSize - 1) << ")\n"
					"Awnser:";
				betIndex = InputController::IntegerRange(aBoardSize, 0);
				bet = GenericFunctions::GetBet(aProfitStruct);
				aBets.straight[betIndex] += bet;
				aBets.straightTotal += bet;
				break;
			}
			case BetTypes::RedBlack:
			{
				std::cout <<
					"\nAlright! Which color are you betting on?\n"
					"(1) Red\n"
					"(2) Black\n"
					"Awnser:";
				betIndex = InputController::IntegerRange(2) - 1;
				bet = GenericFunctions::GetBet(aProfitStruct);
				aBets.redBlack[betIndex] += bet;
				aBets.redBlackTotal += bet;
				break;
			}
			case BetTypes::OddEven:
			{
				std::cout <<
					"\nAlright! Are you betting on odd, or even?\n"
					"(1) Odd\n"
					"(2) Even\n"
					"Awnser:";
				betIndex = InputController::IntegerRange(2) - 1;
				bet = GenericFunctions::GetBet(aProfitStruct);
				aBets.oddEven[betIndex] += bet;
				aBets.oddEvenTotal += bet;
				break;
			}
			case BetTypes::Column:
			{
				std::cout <<
					"\nAlright! Which column are you betting on? (1-3)\n"
					"Awnser:";
				betIndex = InputController::IntegerRange(3) - 1;
				bet = GenericFunctions::GetBet(aProfitStruct);
				aBets.column[betIndex] += bet;
				aBets.columnTotal += bet;
				break;
			}
			default:
				break;
		}
		aBets.total += bet;
	}

	int WinningsLogicHandler(StatTracker::Stats& aStats, const PlayData& aPlayData, const PlayerBets& aBets, const int& aRolledNumber)
	{
		RouletteColor color = aPlayData.colorArray[aRolledNumber];
		int column = 0;
		if (color != RouletteColor::Green)
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

		const VictoryMultipliers victoryMultipliers = aPlayData.victoryMultipliers;

		const int straightProfit = static_cast<int>(aBets.straight[aRolledNumber] * victoryMultipliers.straight);
		const int redBlackProfit = color == RouletteColor::Green ? 0 : static_cast<int>(aBets.redBlack[static_cast<int>(color) - 1] * victoryMultipliers.redBlack);
		const int oddEvenProfit = color == RouletteColor::Green ? 0 : static_cast<int>(aBets.oddEven[(aRolledNumber + 1) % 2] * victoryMultipliers.oddEven);
		const int columnProfit = color == RouletteColor::Green ? 0 : static_cast<int>(aBets.column[column - 1] * victoryMultipliers.column);

		std::cout << "The ball landed on #" << aRolledNumber << (color == RouletteColor::Green ? " (green" : (color == RouletteColor::Black ? " (black" : " (red")) << ", column #" << column << (column == 0 ? "-it was green" : "") << ")\n";
		if (aBets.straightTotal > 0)
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

		if (aBets.redBlackTotal > 0)
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

		if (aBets.oddEvenTotal > 0)
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

		if (aBets.columnTotal > 0)
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
		const int totalProfits = totalWinnings - aBets.total;

		std::cout << "From the total " << aBets.total << "$ you bet, you won " << totalWinnings << "$";
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
		StatTracker::AddGame(aStats.wins, totalProfits >= 0);

		aStats.profits.money += totalWinnings;
		return totalWinnings;
	}
}