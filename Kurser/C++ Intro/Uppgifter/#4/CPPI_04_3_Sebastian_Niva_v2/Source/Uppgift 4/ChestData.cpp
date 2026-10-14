#include "ChestData.h"
#include "RandomController.h"

#include <assert.h>

namespace ChestData
{
	const ChestCreationData& GetChestData(ChestType aType)
	{
		if (aType == ChestType::CountOrRandom)
		{
			aType = static_cast<ChestType>(RandomController::GenerateNumber(0, static_cast<int>(ChestType::CountOrRandom) - 1));
		}
		const int index = static_cast<int>(aType);

		assert(index < CHEST_TYPE_SIZE && "Fatal Error: Attempted to get an item reference outside valid index");

		if (!globalChestDataCollectedAtIndex[index])
		{
			globalChestDataCollection[index] = CreateNewChestData(aType);
			globalChestDataCollectedAtIndex[index] = true;
		}
		return globalChestDataCollection[index];
	}
	ChestCreationData& CreateNewChestData(ChestType aType)
	{
		switch (aType)
		{
			default:
				assert(false && "Fatal Error: A new item was attempted to be made without specifying its type");
			case ChestData::ChestType::OneItemUnlocked: return *new ChestCreationData
			{
				1
			};
			case ChestData::ChestType::TwoItemUnlocked: return *new ChestCreationData
			{
				2
			};
		}
	}

	ChestInstance& CreateNewChest(ItemFactory& aItemFactory, const ChestCreationData& aChestData)
	{
		return *new ChestInstance(aChestData, aItemFactory.CreateWeightedVector(1, aChestData.itemCount));
	}
	std::vector<ChestInstance*> GenerateWeightedChestVector(ItemFactory& aItemFactory, float aChestLikelyhood, int aChestMax)
	{
		std::vector<ChestInstance*> toReturn;
		toReturn.reserve(aChestMax);
		const int chestLikelyhoodWeight = static_cast<int>(1.0f / aChestLikelyhood);
		for (int i = 0; i < aChestMax; i++)
		{
			if (RandomController::GenerateNumber(1, chestLikelyhoodWeight) <= 1)
			{
				toReturn.push_back(&CreateNewChest(aItemFactory, GetChestData(ChestType::CountOrRandom)));
			}
		}
		return toReturn;
	}

	ChestCreationData globalChestDataCollection[CHEST_TYPE_SIZE];
	bool globalChestDataCollectedAtIndex[CHEST_TYPE_SIZE] = { false };
}