#include "Event.h"
#include "RandomController.h"
#include "Player.h"
#include "DisplayManager.h"

Event::Event(ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, EventData::GenerationTypes aEventType) : Event(GenerateData(aEventType, aItemFactory, aEnemyFactory)) {}
Event::Event(EventData::GenerationData aEventData) : myGenerationData(aEventData)
{
	PopulateEvent();
}

void Event::PlayRound(int aRound)
{
	for (int i = 0; i < Player::GetPlayerCount(); i++)
	{
		Player& player = Player::GetPlayer(i);
		Event* event = player.GetRoom()->GetEvent();
		if (event != NULL)
		{
			event->TakeTurn(player.myEntityClass, aRound);
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
Enemy& Event::GetEnemy(int aValue)
{
	return myEnemies.at(aValue);
}

const bool Event::InjureEnemy(std::vector<Item>& aLootVector, int aDamage, int aIndex)
{
	if (aIndex > GetCurrentEnemies())
	{
		return true;
	}
	Enemy& enemy = myEnemies.at(aIndex);
	enemy.TakeDamage(aDamage);
	const bool enemyDied = enemy.IsDead();
	if (enemyDied)
	{
		DisplayManager::EntityDeathCry(enemy.GetTypeData());
		RemoveEnemy(aIndex);
		std::vector<Item> droppedItems = myGenerationData.itemFactory.CreateWeightedVector(ItemType::ENEMY_KILLED_DROP_CHANCE, 1);
		if (static_cast<int>(droppedItems.size()) > 0)
		{
			aLootVector.insert(aLootVector.end(), droppedItems.begin(), droppedItems.end());
			DisplayManager::ItemDropCallout();
		}
	}
	return enemyDied;
}

const bool Event::EnemyIsDead(int aIndex)
{
	if (aIndex > GetCurrentEnemies())
	{
		return true;
	}
	return myEnemies.at(aIndex).IsDead();
}

void Event::RemoveEnemy(int aIndex)
{
	myEnemies.erase(std::next(myEnemies.begin(), aIndex));
}

void Event::TakeTurn(EnemyType& aTargetEntity, int aRound)
{
	for (int i = 0; i < GetCurrentEnemies(); i++)
	{
		Enemy& enemy = myEnemies.at(i);
		if (!enemy.IsDead())
		{
			aTargetEntity.TakeDamage(enemy.GetAttack());
			DisplayManager::EntityAttackShout(enemy, aTargetEntity);
			enemy.CleanSpells(aRound);
		}
	}
}

const EventData::GenerationData Event::GenerateData(EventData::GenerationTypes aEventType, ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory)
{
	while (aEventType == EventData::GenerationTypes::Random)
	{
		aEventType = static_cast<EventData::GenerationTypes>(RandomController::GenerateNumber(0, EventData::TYPES_SIZE - 1));
	}
	int magnitude = 0;
	switch (aEventType)
	{
		default:
		case EventData::GenerationTypes::EasyCombat:
		{
			magnitude = EventData::EASY_MAGNITUDE;
			break;
		}
		case EventData::GenerationTypes::MediumCombat:
		{
			magnitude = EventData::MEDIUM_MAGNITUDE;
			break;
		}
		case EventData::GenerationTypes::HardCombat:
		{
			magnitude = EventData::HARD_MAGNITUDE;
			break;
		}
	}
	return EventData::GenerationData
	{
		.eventType = aEventType,
		.itemFactory = aItemFactory,
		.enemyFactory = aEnemyFactory,
		.magnitude = magnitude
	};
}
void Event::PopulateEvent()
{
	myEnemies.clear();

	EnemyFactory::Types enemyType = static_cast<EnemyFactory::Types>(myGenerationData.magnitude % (EnemyFactory::TYPES_SIZE));
	for (int i = 0; i < myGenerationData.magnitude; i++)
	{
		if (i % 3 == 0)
		{
			myEnemies.push_back(myGenerationData.enemyFactory.Create(EnemyFactory::Types::CountOrRandom));
		}
		else
		{
			myEnemies.push_back(myGenerationData.enemyFactory.Create(enemyType));
		}
	}
}