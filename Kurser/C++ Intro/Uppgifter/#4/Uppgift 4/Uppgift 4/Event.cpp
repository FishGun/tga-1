#include "Event.h"
#include "RandomController.h"
#include "DisplayManager.h"

Event::Event(ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, EventData::GenerationType aEventType) : Event(GenerateData(aEventType, aItemFactory, aEnemyFactory)) {}
Event::Event(EventData::GenerationData aEventData) : myGenerationData(aEventData)
{
	PopulateEvent();
}

void Event::PlayRound()
{
	for (int i = 0; i < Player::GetPlayerCount(); i++)
	{
		Player& player = Player::GetPlayer(i);
		Event* event = player.GetRoom()->GetEvent();
		if (event != NULL)
		{
			event->TakeTurn(player);
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

void Event::TakeTurn(Player& aTargetPlayer)
{
	for (int i = 0; i < GetCurrentEnemies(); i++)
	{
		Enemy& enemy = myEnemies.at(i);
		if (!enemy.IsDead())
		{
			const int attackValue = enemy.GetAttack();
			const int defenseValue = aTargetPlayer.GetDefense();
			const int damageValue = aTargetPlayer.GetTypeData().DamageCalculator(attackValue, defenseValue);
			const int damageReductionValue = attackValue - damageValue;

			aTargetPlayer.TakeDamage(attackValue);
			DisplayManager::EntityAttackShout(enemy.GetTypeData(), aTargetPlayer.GetTypeData(), damageValue, attackValue, damageReductionValue);
		}
	}
}

const EventData::GenerationData Event::GenerateData(EventData::GenerationType aEventType, ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory)
{
	while (aEventType == EventData::GenerationType::Random)
	{
		aEventType = static_cast<EventData::GenerationType>(RandomController::GenerateNumber(0, EventData::TYPE_SIZE - 1));
	}
	int magnitude = 0;
	switch (aEventType)
	{
		default:
		case EventData::GenerationType::EasyCombat:
		{
			magnitude = EventData::EASY_MAGNITUDE;
			break;
		}
		case EventData::GenerationType::MediumCombat:
		{
			magnitude = EventData::MEDIUM_MAGNITUDE;
			break;
		}
		case EventData::GenerationType::HardCombat:
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

	EnemyFactory::Type enemyType = static_cast<EnemyFactory::Type>(myGenerationData.magnitude % (EnemyFactory::TYPE_SIZE));
	for (int i = 0; i < myGenerationData.magnitude; i++)
	{
		if (i % 3 == 0)
		{
			myEnemies.push_back(myGenerationData.enemyFactory.Create(EnemyFactory::Type::CountOrRandom));
		}
		else
		{
			myEnemies.push_back(myGenerationData.enemyFactory.Create(enemyType));
		}
	}
}