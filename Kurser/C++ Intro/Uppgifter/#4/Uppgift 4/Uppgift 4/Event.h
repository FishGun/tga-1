#pragma once
#include "EventData.h"

#include <vector>

class Event
{
public:
	Event() = delete;
	Event(ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, EventData::GenerationTypes aEventType = EventData::GenerationTypes::Random);
	Event(EventData::GenerationData aEventData);

	static void PlayRound(int aRound);
	
	const bool IsActive() const;
	const int GetMagnitude() const;
	const int GetCurrentEnemies() const;
	Enemy& GetEnemy(int aValue);
	const bool InjureEnemy(std::vector<const Item*>& aLootVector, int aDamage, int aIndex = 0);
	const bool EnemyIsDead(int aIndex);
	void RemoveEnemy(int aIndex);
	void TakeTurn(Entity& aTargetEntity, int aRound);

private:
	const EventData::GenerationData myGenerationData;
	std::vector<Enemy> myEnemies;

	const EventData::GenerationData GenerateData(EventData::GenerationTypes aEventType, ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory);
	void GenerateEvent();
};