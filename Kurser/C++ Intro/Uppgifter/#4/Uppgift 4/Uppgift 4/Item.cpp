#include "Item.h"

Item::Item(const EntityData::BaseData aBaseModifiers, const EntityData::DerivedData aDerivedModifiers) :
	myBaseModifiers(aBaseModifiers),
	myDerivedModifiers(aDerivedModifiers) {}

const EntityData::BaseData& Item::GetBaseData() const
{
	return myBaseModifiers;
}

const EntityData::DerivedData& Item::GetDerivedData() const
{
	return myDerivedModifiers;
}
