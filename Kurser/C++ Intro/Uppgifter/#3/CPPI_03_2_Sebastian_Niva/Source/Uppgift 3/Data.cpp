#include "Data.h"

namespace Data
{
	TableMoneyStruct GenerateTableMoneyStruct(const int aMinBet, const int aMaxBet)
	{
		return TableMoneyStruct
		{
			.currentProfits = 0,
			.banValue = aMaxBet * 5,
			.highValue = aMaxBet * 2,
			.lowValue = -aMaxBet * 2,
			.minBet = aMinBet,
			.maxBet = aMaxBet
		};
	}
}