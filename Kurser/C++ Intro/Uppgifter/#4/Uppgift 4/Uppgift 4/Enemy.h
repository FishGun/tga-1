#pragma once
#include "EnemyType.h"

class Enemy
{
public:
	Enemy(EnemyType aEntity);

	const int GetStrength() const;
	const int GetDexterity() const;
	const int GetPhysique() const;

	const int GetAttack() const;
	const int GetMaxHP() const;
	const int GetCarryingCapacity() const;
	const int GetDefense() const;

	void TakeDamage(int aValue);
	const int GetCurrentHP() const;
	const bool IsDead() const;
	const EnemyType& GetTypeData() const;

private:
	EnemyType myTypeData;
	int myCurrentHP;
};