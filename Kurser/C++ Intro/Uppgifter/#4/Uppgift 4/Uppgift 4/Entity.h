#pragma once
#include "EntityData.h"

class Entity
{
public:
	Entity() = delete;
	Entity(EntityData::BaseData aBaseStats);

	static int DamageCalculator(int aAttackValue, int aDefenseValue);

	const EntityData::BaseData& GetBaseStats() const;
	const int GetAttack() const;
	const int GetMaxHP() const;
	const int GetCarryingCapacity() const;
	const int GetDefense() const;
	const int GetHP() const;
	const bool IsDead() const;
	const char* GetName() const;
	const char* SetName();

	//void ChangeHP(int aValue);
	void TakeDamage(int aValue);
	void Heal(int aValue);
	const int ChangeStat(EntityData::BaseStatsEnum aBaseStat, int aValue);

	Entity& operator += (int rValue);
private:
	EntityData::BaseData myBaseData;
	int myHitPoints;
};