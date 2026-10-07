#include "Enemy.h"
#include "InputController.h"
#include "DisplayManager.h"

EnemyType::EnemyType(EntityData::BaseData aBaseData) : myBaseData(aBaseData)
{

}

int EnemyType::DamageCalculator(int aAttackValue, int aDefenseValue)
{
	int toReturn = aAttackValue - (aDefenseValue / EntityData::DEFENSE_DIVIDER);
	if (toReturn < 0)
	{
		toReturn = 0;
	}
	return toReturn;
}

const EntityData::BaseData& EnemyType::GetBaseStats() const
{
	return myBaseData;
}
const char* EnemyType::GetName() const
{
	return myBaseData.name;
}
const char* EnemyType::SetName()
{
	InputController::AskForName(myBaseData.name, EntityData::MIN_NAME_LENGTH, EntityData::MAX_NAME_LENGTH - 1);
	return myBaseData.name;
}

const int EnemyType::ChangeStat(EntityData::BaseStatsEnum aBaseStat, int aValue)
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