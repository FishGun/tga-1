#pragma once
#include "EntityData.h"

#include <vector>

namespace ItemData
{
	const float ENEMY_KILLED_DROP_CHANCE = 0.25f;
	const float ROOM_DROP_SPAWN_CHANCE = 0.5f;
	const int ROOM_DROP_SPAWN_TRIES = 2;
	const float ROOM_CHEST_SPAWN_CHANCE = 0.34f;
	const float ROOM_SPELL_SPAWN_CHANCE = 0.5f;

	enum class ItemTypes
	{
		Knife,
		Longsword,
		Greatsword,
		LeatherChestplate,
		MetalChestplate,
		CobbledBoots,
		NobleBoots,
		CountOrRandom,
	};
	const int ITEM_TYPES_SIZE = static_cast<int>(ItemTypes::CountOrRandom);

	struct ItemInstanceData
	{
		const EntityData::BaseData baseModifiers {0};
		const EntityData::DerivedData derivedModifiers {0};
	};

	extern ItemInstanceData* globalItemDataCollection[];
	extern bool globalItemDataCollectedAtIndex[];

	const ItemInstanceData& GetItemData(ItemTypes aType);
	ItemInstanceData* CreateNewItemData(ItemTypes aType);

	std::vector<const ItemData::ItemInstanceData*> GenerateWeightedItemVector(float aItemLikelyhood, int aItemMax);
}