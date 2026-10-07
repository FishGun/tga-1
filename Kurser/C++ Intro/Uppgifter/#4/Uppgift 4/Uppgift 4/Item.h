#pragma once
#include "EntityData.h"
#include "ItemType.h"

#include <vector>

class Item
{
public:
	Item() = delete;
	Item(ItemType* aTypeData);

	const ItemType& GetItemType() const;
private:
	ItemType* myItemType;
};