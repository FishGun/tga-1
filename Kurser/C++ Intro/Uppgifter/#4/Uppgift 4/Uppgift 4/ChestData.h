#pragma once
#include "ItemData.h"

#include <vector>

namespace ChestData
{
	enum class ChestTypes
	{
		OneItemUnlocked,
		TwoItemUnlocked,
		//OneItemEasyLock,
		//ThreeItemEasyLock,
		//TwoItemHardLock,
		CountOrRandom
	};
	const int CHEST_TYPES_SIZE = static_cast<int>(ChestTypes::CountOrRandom);

	struct ChestCreationData
	{
		int itemCount;
	};

	struct ChestInstance
	{
		const ChestCreationData& data;
		std::vector<const ItemData::ItemInstanceData*> items = ItemData::GenerateWeightedItemVector(1, data.itemCount);
	};

	extern ChestCreationData globalChestDataCollection[];
	extern bool globalChestDataCollectedAtIndex[];

	const ChestCreationData& GetChestData(ChestTypes aType);
	ChestCreationData& CreateNewChestData(ChestTypes aType);

	ChestInstance& CreateNewChest(ChestCreationData& aChestData);
	std::vector<ChestInstance*> GenerateWeightedChestVector(float aChestLikelyhood, int aChestMax);
}