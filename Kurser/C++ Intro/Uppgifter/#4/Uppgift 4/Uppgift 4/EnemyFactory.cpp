#include "EnemyFactory.h"
#include "RandomController.h"

#include <assert.h>

const Enemy& EnemyFactory::Create(EnemyFactory::Type aType)
{
	if (aType == EnemyFactory::Type::CountOrRandom)
	{
		aType = static_cast<EnemyFactory::Type>(RandomController::GenerateNumber(0, static_cast<int>(EnemyFactory::Type::CountOrRandom) - 1));
	}
	const int index = static_cast<int>(aType);

	assert(index < EnemyFactory::TYPE_SIZE && "Fatal Error: Attempted to get an item reference outside valid index");

	if (!myEnemyDataCollectedAtIndex[index])
	{
		myEnemyDataCollection[index] = CreateToArray(aType);
		myEnemyDataCollectedAtIndex[index] = true;
	}
	return *myEnemyDataCollection[index];
}

Enemy* EnemyFactory::CreateToArray(EnemyFactory::Type aType)
{
	switch (aType)
	{
		default:
			assert(false && "Fatal Error: A new item was attempted to be made without specifying its type");
		case EnemyFactory::Type::Skeleton: return new Enemy
		{
			EnemyType
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
		case EnemyFactory::Type::Spider: return new Enemy
		{
			EnemyType
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
		case EnemyFactory::Type::Negation: return new Enemy
		{
			EnemyType
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
		case EnemyFactory::Type::TearGolem: return new Enemy
		{
			EnemyType
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
