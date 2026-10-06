#include "ItemFactory.h"
#include "RandomController.h"
#include "EntityData.h"

#include <assert.h>

const Item& ItemFactory::Create(ItemFactory::Types aType)
{
	if (aType == ItemFactory::Types::CountOrRandom)
	{
		aType = static_cast<ItemFactory::Types>(RandomController::GenerateNumber(0, static_cast<int>(ItemFactory::Types::CountOrRandom) - 1));
	}
	const int index = static_cast<int>(aType);

	assert(index <ItemFactory::TYPES_SIZE && "Fatal Error: Attempted to get an item reference outside valid index");

	if (!myItemDataCollectedAtIndex[index])
	{
		myItemDataCollection[index] = CreateToArray(aType);
		myItemDataCollectedAtIndex[index] = true;
	}
	return *myItemDataCollection[index];
}
Item* ItemFactory::CreateToArray(ItemFactory::Types aType)
{
	switch (aType)
	{
		default:
			assert(false && "Fatal Error: A new item was attempted to be made without specifying its type");
		case ItemFactory::Types::Knife: return new Item
		{
			EntityData::BaseData
			{
				.name = "Knife"
			},
			EntityData::DerivedData
			{
				.attack = 5,
				.defense = 1
			}
		};
		case ItemFactory::Types::Longsword: return new Item
		{
			EntityData::BaseData
			{
				.name = "Longsword",
				.dexterity = -1
			},
			EntityData::DerivedData
			{
				.attack = 10,
				.defense = 5,
			}
		};
		case ItemFactory::Types::Greatsword: return new Item
		{
			EntityData::BaseData
			{
				.name = "Greatsword",
				.dexterity = -1
			},
			EntityData::DerivedData
			{
				.attack = 20
			}
		};
		case ItemFactory::Types::LeatherChestplate: return new Item
		{
			EntityData::BaseData
			{
				.name = "Leather Chestplate",
			},
			EntityData::DerivedData
			{
				.defense = 5,
				.hitPointMax = 10
			}
		};
		case ItemFactory::Types::MetalChestplate: return new Item
		{
			EntityData::BaseData
			{
				.name = "Metal Chestplate",
				.dexterity = -2
			},
			EntityData::DerivedData
			{
				.attack = -2,
				.defense = 30,
				.hitPointMax = 50
			}
		};
		case ItemFactory::Types::CobbledBoots: return new Item
		{
			EntityData::BaseData
			{
				.name = "Cobbled Boots",
				.dexterity = 1
			},
			EntityData::DerivedData
			{
				.defense = 2,
				.carryingCapacity = 1
			}
		};
		case ItemFactory::Types::NobleBoots: return new Item
		{
			EntityData::BaseData
			{
				.name = "Noble Boots",
				.dexterity = 2,
				.physique = 1
			},
			EntityData::DerivedData
			{
				.defense = 5,
				.carryingCapacity = 2
			}
		};
	}
}

std::vector<const Item*> ItemFactory::CreateWeightedVector(float aItemLikelyhood, int aItemMax)
{
	std::vector<const Item*> toReturn;
	toReturn.reserve(aItemMax);
	const int itemLikelyhoodWeight = static_cast<int>(1.0f / aItemLikelyhood);
	for (int i = 0; i < aItemMax; i++)
	{
		if (RandomController::GenerateNumber(1, itemLikelyhoodWeight) <= 1)
		{
			toReturn.push_back(&Create(ItemFactory::Types::CountOrRandom));
		}
	}
	return toReturn;
}