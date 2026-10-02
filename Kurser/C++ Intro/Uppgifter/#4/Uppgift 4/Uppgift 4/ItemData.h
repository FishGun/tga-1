#pragma once
#include "EntityData.h"

#include <vector>

namespace ItemData
{
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
		const EntityData::BaseData baseModifiers = {0};
		const EntityData::DerivedData derivedModifiers;
	};

	extern ItemInstanceData* globalItemDataCollection[];
	extern bool globalItemDataCollectedAtIndex[];

	const ItemInstanceData& GetItemData(ItemTypes aType);
	ItemInstanceData* CreateNewItemData(ItemTypes aType);

	std::vector<const ItemData::ItemInstanceData*> GenerateWeightedItemVector(float aItemLikelyhood, int aItemMax);
}