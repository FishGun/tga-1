#pragma once
#include "Enemy.h"

class EnemyFactory
{
public:
	enum class Types
	{
		Skeleton,
		Spider,
		Negation,
		TearGolem,
		CountOrRandom
	};
	static constexpr int TYPES_SIZE = static_cast<int>(Types::CountOrRandom);

	const Enemy& Create(Types aType);
	//std::vector<const Enemy*> CreateWeightedVector(float aItemLikelyhood = Item::ROOM_DROP_SPAWN_CHANCE, int aItemMax = Item::ROOM_DROP_SPAWN_TRIES);

private:
	Enemy* myEnemyDataCollection[TYPES_SIZE]{};
	bool myEnemyDataCollectedAtIndex[TYPES_SIZE]{ false };
	Enemy* CreateToArray(Types aType);
};