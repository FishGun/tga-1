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

	const Item& Create(Types aType);
	std::vector<const Item*> CreateWeightedVector(float aItemLikelyhood = Item::ROOM_DROP_SPAWN_CHANCE, int aItemMax = Item::ROOM_DROP_SPAWN_TRIES);

private:
	Item* myItemDataCollection[TYPES_SIZE]{};
	bool myItemDataCollectedAtIndex[TYPES_SIZE]{ false };
	Item* CreateToArray(Types aType);
};