#pragma once
#include "Item.h"

class ItemFactory
{
public:
	enum class Types
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
	static constexpr int TYPES_SIZE = static_cast<int>(Types::CountOrRandom);

	const Item Create(Types aType);
	std::vector<Item> CreateWeightedVector(float aItemLikelyhood = ItemType::ROOM_DROP_SPAWN_CHANCE, int aItemMax = ItemType::ROOM_DROP_SPAWN_TRIES);

private:
	ItemType* myItemDataCollection[TYPES_SIZE]{};
	bool myItemDataCollectedAtIndex[TYPES_SIZE]{ false };
	ItemType* DefineItemTypeData(Types aType);
};