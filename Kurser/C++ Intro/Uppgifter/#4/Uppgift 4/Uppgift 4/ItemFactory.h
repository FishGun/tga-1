#pragma once
#include "Item.h"

class ItemFactory
{
public:
	enum class Type
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
	static constexpr int TYPE_SIZE = static_cast<int>(Type::CountOrRandom);

	const Item Create(Type aType);
	std::vector<Item> CreateWeightedVector(float aItemLikelyhood = ItemType::ROOM_DROP_SPAWN_CHANCE, int aItemMax = ItemType::ROOM_DROP_SPAWN_TRIES);

private:
	ItemType* myItemDataCollection[TYPE_SIZE]{};
	bool myItemDataCollectedAtIndex[TYPE_SIZE]{ false };
	ItemType* DefineItemTypeData(Type aType);
};