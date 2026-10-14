#pragma once
#include "ItemFactory.h"

#include <vector>

namespace ChestData
{
	enum class ChestType
	{
		OneItemUnlocked,
		TwoItemUnlocked,
		CountOrRandom
	};
	const int CHEST_TYPE_SIZE = static_cast<int>(ChestType::CountOrRandom);

	struct ChestCreationData
	{
		int itemCount;
	};

	struct ChestInstance
	{
		const ChestCreationData& data;
		std::vector<Item> items;
	};

	extern ChestCreationData globalChestDataCollection[];
	extern bool globalChestDataCollectedAtIndex[];

	const ChestCreationData& GetChestData(ChestType aType);
	ChestCreationData& CreateNewChestData(ChestType aType);

	ChestInstance& CreateNewChest(ItemFactory& aItemFactory, ChestCreationData& aChestData);
	std::vector<ChestInstance*> GenerateWeightedChestVector(ItemFactory& aItemFactory, float aChestLikelyhood = ItemType::ROOM_CHEST_SPAWN_CHANCE, int aChestMax = 1);
}