#include "ItemData.h"
#include "RandomController.h"

#include <assert.h>

namespace ItemData
{
	const ItemInstanceData& GetItemData(ItemTypes aType)
	{
		if (aType == ItemTypes::CountOrRandom)
		{
			aType = static_cast<ItemTypes>(RandomController::GenerateNumber(0, static_cast<int>(ItemTypes::CountOrRandom)-1));
		}
		const int index = static_cast<int>(aType);

		assert(index < ITEM_TYPES_SIZE && "Fatal Error: Attempted to get an item reference outside valid index");

		if (!globalItemDataCollectedAtIndex[index])
		{
			globalItemDataCollection[index] = CreateNewItemData(aType);
			globalItemDataCollectedAtIndex[index] = true;
		}
		return *globalItemDataCollection[index];
	}
	ItemInstanceData* CreateNewItemData(ItemTypes aType)
	{
		switch (aType)
		{
			default:
				assert(false && "Fatal Error: A new item was attempted to be made without specifying its type");
			case ItemTypes::Knife: return new ItemInstanceData
			{
				EntityData::BaseData
				{
					.name = "Knife"
				},
				EntityData::DerivedData
				{
					.attack = 2,
					.defense = 1
				}
			};
			case ItemTypes::Longsword: return new ItemInstanceData
			{
				EntityData::BaseData
				{
					.name = "Longsword",
					.dexterity = -1
				},
				EntityData::DerivedData
				{
					.attack = 5,
					.defense = 2,
				}
			};
			case ItemTypes::Greatsword: return new ItemInstanceData
			{
				EntityData::BaseData
				{
					.name = "Greatsword",
					.dexterity = -5
				},
				EntityData::DerivedData
				{
					.attack = 15
				}
			};
			case ItemTypes::LeatherChestplate: return new ItemInstanceData
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
			case ItemTypes::MetalChestplate: return new ItemInstanceData
			{
				EntityData::BaseData
				{
					.name = "Metal Chestplate",
					.dexterity = -7
				},
				EntityData::DerivedData
				{
					.attack = -2,
					.defense = 15,
					.hitPointMax = 30
				}
			};
			case ItemTypes::CobbledBoots: return new ItemInstanceData
			{
				EntityData::BaseData
				{
					.name = "Cobbled Boots",
					.dexterity = 3
				},
				EntityData::DerivedData
				{
					.defense = 1,
					.carryingCapacity = 1
				}
			};
			case ItemTypes::NobleBoots: return new ItemInstanceData
			{
				EntityData::BaseData
				{
					.name = "Noble Boots",
					.dexterity = 7,
					.physique = 2
				},
				EntityData::DerivedData
				{
					.defense = 5,
					.carryingCapacity = 2
				}
			};
		}
	}

	std::vector<const ItemData::ItemInstanceData*> GenerateWeightedItemVector(float aItemLikelyhood, int aItemMax)
	{
		std::vector<const ItemData::ItemInstanceData*> toReturn;
		toReturn.reserve(aItemMax);
		const int itemLikelyhoodWeight = static_cast<int>(1.0f / aItemLikelyhood);
		for (int i = 0; i < aItemMax; i++)
		{
			if (RandomController::GenerateNumber(1, itemLikelyhoodWeight) == 1)
			{
				toReturn.push_back(&GetItemData(ItemTypes::CountOrRandom));
			}
		}
		return toReturn;
	}

	ItemInstanceData* globalItemDataCollection[ITEM_TYPES_SIZE];
	bool globalItemDataCollectedAtIndex[ITEM_TYPES_SIZE] = { false };
}