#include "Event.h"
#include "RandomController.h"
#include "Player.h"
#include "DisplayManager.h"

Event::Event(EventData::GenerationTypes aEventType) : Event(GenerateData(aEventType)) {}
Event::Event(EventData::GenerationData aEventData) : myGenerationData(aEventData)
{
	GenerateEvent();
}

void Event::PlayRound()
{
	for (int i = 0; i < Player::GetPlayerCount(); i++)
	{
		Player& player = Player::GetPlayer(i);
		Event* event = player.GetRoom()->GetEvent();
		if (event != NULL)
		{
			event->TakeTurn(player.myEntityClass);
		}
	}
}

const bool Event::IsActive() const
{
	return GetCurrentEnemies() > 0;
}
const int Event::GetMagnitude() const
{
	return myGenerationData.magnitude;
}
const int Event::GetCurrentEnemies() const
{
	return static_cast<int>(myEnemies.size());
}
const Enemy& Event::GetEnemy(int aValue) const
{
	return myEnemies.at(aValue);
}

const bool Event::InjureEnemy(int aDamage, int aIndex)
{
	if (aIndex > GetCurrentEnemies())
	{
		return true;
	}
	Entity& enemyEntity = myEnemies.at(aIndex).myEntityClass;
	enemyEntity.TakeDamage(aDamage);
	const bool enemyDied = enemyEntity.IsDead();
	if (enemyDied)
	{
		DisplayManager::EntityDeathCry(enemyEntity);
		RemoveEnemy(aIndex);
	}
	return enemyDied;
}

const bool Event::EnemyIsDead(int aIndex)
{
	if (aIndex > GetCurrentEnemies())
	{
		return true;
	}
	return myEnemies.at(aIndex).myEntityClass.IsDead();
}

void Event::RemoveEnemy(int aIndex)
{
	myEnemies.erase(std::next(myEnemies.begin(), aIndex));
}

void Event::TakeTurn(Entity& aTargetEntity)
{
	for (int i = 0; i < GetCurrentEnemies(); i++)
	{
		Entity& enemyEntity = myEnemies.at(i).myEntityClass;
		if (!enemyEntity.IsDead())
		{
			aTargetEntity.TakeDamage(enemyEntity.GetAttack());
			DisplayManager::EntityAttackShout(enemyEntity, aTargetEntity);
		}
	}
}

const EventData::GenerationData Event::GenerateData(EventData::GenerationTypes aEventType)
{
	while (aEventType == EventData::GenerationTypes::Random)
	{
		aEventType = static_cast<EventData::GenerationTypes>(RandomController::GenerateNumber(0, EventData::globalTypesSize - 1));
	}
	switch (aEventType)
	{
		default:
		case EventData::GenerationTypes::EasyCombat:
		{
			return EventData::GenerationData
			{
				.eventType = aEventType,
				.magnitude = EventData::globalEasyMagnitude
			};
		}
		case EventData::GenerationTypes::MediumCombat:
		{
			return EventData::GenerationData
			{
				.eventType = aEventType,
				.magnitude = EventData::globalMediumMagnitude
			};
		}
		case EventData::GenerationTypes::HardCombat:
		{
			return EventData::GenerationData
			{
				.eventType = aEventType,
				.magnitude = EventData::globalHardMagnitude
			};
		}
	}
}
void Event::GenerateEvent()
{
	myEnemies.clear();

	for (int i = 0; i < myGenerationData.magnitude; i++)
	{
		EntityData::BaseData enemyStats =
		{
			.name = "Mob",
			.strength = myGenerationData.magnitude,
			.dexterity = myGenerationData.magnitude,
			.physique = myGenerationData.magnitude
		};
		myEnemies.push_back(Enemy(enemyStats));
	}
}