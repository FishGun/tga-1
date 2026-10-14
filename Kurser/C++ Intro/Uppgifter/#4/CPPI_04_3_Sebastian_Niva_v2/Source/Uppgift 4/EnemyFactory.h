#pragma once
#include "Enemy.h"

class EnemyFactory
{
public:
	enum class Type
	{
		Skeleton,
		Spider,
		Negation,
		TearGolem,
		CountOrRandom
	};
	static constexpr int TYPE_SIZE = static_cast<int>(Type::CountOrRandom);

	const Enemy& Create(Type aType);

private:
	Enemy* myEnemyDataCollection[TYPE_SIZE]{};
	bool myEnemyDataCollectedAtIndex[TYPE_SIZE]{ false };
	Enemy* CreateToArray(Type aType);
};