#include "Entity.h"
#include "InputController.h"

Entity::Entity(EntityData::BaseData aBaseData) : myBaseData(aBaseData), myHitPoints(GetMaxHP()) {}

int Entity::DamageCalculator(int aAttackValue, int aDefenseValue)
{
	int toReturn = aAttackValue - (aDefenseValue / EntityData::DEFENSE_DIVIDER);
	if (toReturn < 0)
	{
		toReturn = 0;
	}
	return toReturn;
}

const EntityData::BaseData& Entity::GetBaseStats() const
{
	return myBaseData;
}
const int Entity::GetAttack() const
{
	return myBaseData.strength * myBaseData.dexterity;
}
const int Entity::GetMaxHP() const
{
	return myBaseData.physique * 4 + myBaseData.strength * 6 + myBaseData.dexterity * 3;
}
const int Entity::GetCarryingCapacity() const
{
	return myBaseData.strength + myBaseData.dexterity / 3;
}
const int Entity::GetDefense() const
{
	return myBaseData.physique * myBaseData.dexterity;
}
const int Entity::GetHP() const
{
	return myHitPoints;
}
const bool Entity::IsDead() const
{
	return myHitPoints <= 0;
}
const char* Entity::GetName() const
{
	return myBaseData.name;
}
const char* Entity::SetName()
{
	InputController::AskForName(myBaseData.name, EntityData::MIN_NAME_LENGTH, EntityData::MAX_NAME_LENGTH - 1);
	return myBaseData.name;
}

/*
void Entity::ChangeHP(int aValue)
{
	const int maxHP = GetMaxHP();
	myHitPoints += aValue;
	if (myHitPoints > maxHP)
	{
		myHitPoints = maxHP;
	}
	else if (myHitPoints < 0)
	{
		myHitPoints = 0;
	}
}
*/

void Entity::TakeDamage(int aValue)
{
	const int maxHP = GetMaxHP();
	myHitPoints -= DamageCalculator(aValue, GetDefense());
	if (myHitPoints > maxHP)
	{
		myHitPoints = maxHP;
	}
	else if (myHitPoints < 0)
	{
		myHitPoints = 0;
	}
}
void Entity::Heal(int aValue)
{
	const int maxHP = GetMaxHP();
	myHitPoints += aValue;
	if (myHitPoints > maxHP)
	{
		myHitPoints = maxHP;
	}
	else if (myHitPoints < 0)
	{
		myHitPoints = 0;
	}
}

const int Entity::ChangeStat(EntityData::BaseStatsEnum aBaseStat, int aValue)
{
	switch (aBaseStat)
	{
		case EntityData::BaseStatsEnum::Strength:
			myBaseData.strength += aValue;
			break;
		case EntityData::BaseStatsEnum::Dexterity:
			myBaseData.dexterity += aValue;
			break;
		case EntityData::BaseStatsEnum::Physique:
			myBaseData.physique += aValue;
			break;
		case EntityData::BaseStatsEnum::Length:
		default:
			return 0;
	}
	return aValue;
}

Entity& Entity::operator += (int rValue)
{
	this->myHitPoints += rValue;
	return *this;
}