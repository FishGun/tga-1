#pragma once
#include "ItemFactory.h"

#include <vector>

namespace ChestData
{
	enum class ChestTypes
	{
		OneItemUnlocked,
		TwoItemUnlocked,
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
		std::vector<const Item*> items;
	};

	extern ChestCreationData globalChestDataCollection[];
	extern bool globalChestDataCollectedAtIndex[];

	const ChestCreationData& GetChestData(ChestTypes aType);
	ChestCreationData& CreateNewChestData(ChestTypes aType);

	ChestInstance& CreateNewChest(ItemFactory& aItemFactory, ChestCreationData& aChestData);
	std::vector<ChestInstance*> GenerateWeightedChestVector(ItemFactory& aItemFactory, float aChestLikelyhood = Item::ROOM_CHEST_SPAWN_CHANCE, int aChestMax = 1);
}