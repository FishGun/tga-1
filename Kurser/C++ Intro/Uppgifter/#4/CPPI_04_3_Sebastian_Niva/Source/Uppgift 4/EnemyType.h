#pragma once
#include "EntityData.h"

#include <vector>

class EnemyType
{
public:
	EnemyType() = delete;
	EnemyType(EntityData::BaseData aBaseStats);

	static int DamageCalculator(int aAttackValue, int aDefenseValue);

	const EntityData::BaseData& GetBaseStats() const;

	const char* GetName() const;
	const char* SetName();

	const int ChangeStat(EntityData::BaseStatsEnum aBaseStat, int aValue);
private:


	EntityData::BaseData myBaseData;
};