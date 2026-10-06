#include "EnemyFactory.h"
#include "RandomController.h"

#include <assert.h>

const Enemy& EnemyFactory::Create(EnemyFactory::Types aType)
{
	if (aType == EnemyFactory::Types::CountOrRandom)
	{
		aType = static_cast<EnemyFactory::Types>(RandomController::GenerateNumber(0, static_cast<int>(EnemyFactory::Types::CountOrRandom) - 1));
	}
	const int index = static_cast<int>(aType);

	assert(index < EnemyFactory::TYPES_SIZE && "Fatal Error: Attempted to get an item reference outside valid index");

	if (!myEnemyDataCollectedAtIndex[index])
	{
		myEnemyDataCollection[index] = CreateToArray(aType);
		myEnemyDataCollectedAtIndex[index] = true;
	}
	return *myEnemyDataCollection[index];
}

Enemy* EnemyFactory::CreateToArray(EnemyFactory::Types aType)
{
	switch (aType)
	{
		default:
			assert(false && "Fatal Error: A new item was attempted to be made without specifying its type");
		case EnemyFactory::Types::Skeleton: return new Enemy
		{
			Entity
			{
				EntityData::BaseData
				{
					.name = "Skeleton",
					.strength = 5,
					.dexterity = 8,
					.physique = 8
				}
			}
		};
		case EnemyFactory::Types::Spider: return new Enemy
		{
			Entity
			{
				EntityData::BaseData
				{
					.name = "Spider",
					.strength = 1,
					.dexterity = 30,
					.physique = 3
				}
			}
		};
		case EnemyFactory::Types::Negation: return new Enemy
		{
			Entity
			{
				EntityData::BaseData
				{
					.name = "Negation",
					.strength = 13,
					.dexterity = 4,
					.physique = 1
				}
			}
		};
		case EnemyFactory::Types::TearGolem: return new Enemy
		{
			Entity
			{
				EntityData::BaseData
				{
					.name = "Tear Golem",
					.strength = 6,
					.dexterity = 7,
					.physique = 9
				}
			}
		};
	}
}
