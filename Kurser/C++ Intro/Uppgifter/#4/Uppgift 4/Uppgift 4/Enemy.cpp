#include "Enemy.h"

Enemy::Enemy(EnemyType aEntity) : myTypeData(aEntity), myCurrentHP(GetMaxHP()) {}

const int Enemy::GetStrength() const
{
	return myTypeData.GetBaseStats().strength;
}
const int Enemy::GetDexterity() const
{
	return myTypeData.GetBaseStats().dexterity;
}
const int Enemy::GetPhysique() const
{
	return myTypeData.GetBaseStats().physique;
}

const int Enemy::GetAttack() const
{
	return GetStrength() * GetDexterity();
}
const int Enemy::GetMaxHP() const
{
	return GetPhysique() * 4 + GetStrength() * 6 + GetDexterity() * 3;
}
const int Enemy::GetCarryingCapacity() const
{
	return GetStrength() + GetDexterity() / 3;
}
const int Enemy::GetDefense() const
{
	return GetPhysique() * GetDexterity();
}

void Enemy::TakeDamage(int aValue)
{
	const int maxHP = GetMaxHP();
	myCurrentHP -= myTypeData.DamageCalculator(aValue, GetDefense());
	if (myCurrentHP > maxHP)
	{
		myCurrentHP = maxHP;
	}
	else if (myCurrentHP < 0)
	{
		myCurrentHP = 0;
	}
}
const int Enemy::GetCurrentHP() const
{
	return myCurrentHP;
}
const bool Enemy::IsDead() const
{
	return myCurrentHP <= 0;
}
const EnemyType& Enemy::GetTypeData() const
{
	return myTypeData;
}