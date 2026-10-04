#include "ChestData.h"
#include "RandomController.h"

#include <assert.h>

namespace ChestData
{
	const ChestCreationData& GetChestData(ChestTypes aType)
	{
		if (aType == ChestTypes::CountOrRandom)
		{
			aType = static_cast<ChestTypes>(RandomController::GenerateNumber(0, static_cast<int>(ChestTypes::CountOrRandom) - 1));
		}
		const int index = static_cast<int>(aType);

		assert(index < CHEST_TYPES_SIZE && "Fatal Error: Attempted to get an item reference outside valid index");

		if (!globalChestDataCollectedAtIndex[index])
		{
			globalChestDataCollection[index] = CreateNewChestData(aType);
			globalChestDataCollectedAtIndex[index] = true;
		}
		return globalChestDataCollection[index];
	}
	ChestCreationData& CreateNewChestData(ChestTypes aType)
	{
		switch (aType)
		{
			default:
				assert(false && "Fatal Error: A new item was attempted to be made without specifying its type");
			case ChestData::ChestTypes::OneItemUnlocked: return *new ChestCreationData
			{
				1
			};
			case ChestData::ChestTypes::TwoItemUnlocked: return *new ChestCreationData
			{
				2
			};
		}
	}

	ChestInstance& CreateNewChest(const ChestCreationData& aChestData)
	{
		return *new ChestInstance(aChestData);
	}
	std::vector<ChestInstance*> GenerateWeightedChestVector(float aChestLikelyhood, int aChestMax)
	{
		std::vector<ChestInstance*> toReturn;
		toReturn.reserve(aChestMax);
		const int chestLikelyhoodWeight = static_cast<int>(1.0f / aChestLikelyhood);
		for (int i = 0; i < aChestMax; i++)
		{
			if (RandomController::GenerateNumber(1, chestLikelyhoodWeight) <= 1)
			{
				toReturn.push_back(&CreateNewChest(GetChestData(ChestTypes::CountOrRandom)));
			}
		}
		return toReturn;
	}

	ChestCreationData globalChestDataCollection[CHEST_TYPES_SIZE];
	bool globalChestDataCollectedAtIndex[CHEST_TYPES_SIZE] = { false };
}