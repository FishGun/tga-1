#include "StatTracker.h"
#include "GameManager.h"

namespace StatTracker
{
	void AddGame(Wins& aWinStruct, bool aDidWin)
	{
		for (int i = aWinStruct.gameHistoryArraySize - 1; i > 0; i--)
		{
			aWinStruct.gameHistory[i] = aWinStruct.gameHistory[i - 1];
		}
		aWinStruct.gameHistory[0] = (aDidWin ? 1 : -1);

		if (aDidWin)
		{
			aWinStruct.total++;
		}
	}
}