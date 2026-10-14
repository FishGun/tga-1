#include "ItemFactory.h"
#include "RandomController.h"
#include "EntityData.h"

#include <assert.h>

const Item ItemFactory::Create(Type aType)
{
	if (aType == Type::CountOrRandom)
	{
		aType = static_cast<Type>(RandomController::GenerateNumber(0, static_cast<int>(Type::CountOrRandom) - 1));
	}
	const int index = static_cast<int>(aType);

	assert(index <TYPE_SIZE && "Fatal Error: Attempted to get an item reference outside valid index");

	if (!myItemDataCollectedAtIndex[index])
	{
		myItemDataCollection[index] = DefineItemTypeData(aType);
		myItemDataCollectedAtIndex[index] = true;
	}
	return Item::Item(myItemDataCollection[index]);
}

std::vector<Item> ItemFactory::CreateWeightedVector(float aItemLikelyhood, int aItemMax)
{
	std::vector<Item> toReturn;
	toReturn.reserve(aItemMax);
	const int itemLikelyhoodWeight = static_cast<int>(1.0f / aItemLikelyhood);
	for (int i = 0; i < aItemMax; i++)
	{
		if (RandomController::GenerateNumber(1, itemLikelyhoodWeight) <= 1)
		{
			toReturn.push_back(Create(Type::CountOrRandom));
		}
	}
	return toReturn;
}

ItemType* ItemFactory::DefineItemTypeData(Type aType)
{
	switch (aType)
	{
		default:
			assert(false && "Fatal Error: A new item was attempted to be made without specifying its type");
		case ItemFactory::Type::Knife: return new ItemType
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
		case ItemFactory::Type::Longsword: return new ItemType
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
		case ItemFactory::Type::Greatsword: return new ItemType
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
		case ItemFactory::Type::LeatherChestplate: return new ItemType
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
		case ItemFactory::Type::MetalChestplate: return new ItemType
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
		case ItemFactory::Type::CobbledBoots: return new ItemType
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
		case ItemFactory::Type::NobleBoots: return new ItemType
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