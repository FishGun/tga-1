#include "Item.h"

Item::Item(ItemType* aTypeData) : myItemType(aTypeData) {}

const ItemType& Item::GetItemType() const
{
	return *myItemType;
}