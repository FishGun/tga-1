#include "ItemType.h"

ItemType::ItemType(const EntityData::BaseData aBaseModifiers, const EntityData::DerivedData aDerivedModifiers) :
	myBaseModifiers(aBaseModifiers),
	myDerivedModifiers(aDerivedModifiers) {}

const EntityData::BaseData& ItemType::GetBaseData() const
{
	return myBaseModifiers;
}

const EntityData::DerivedData& ItemType::GetDerivedData() const
{
	return myDerivedModifiers;
}