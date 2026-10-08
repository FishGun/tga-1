#pragma once
#include "EventData.h"
//#include "Player.h"

#include <vector>

class Player;

class Event
{
public:
	Event() = delete;
	Event(ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, EventData::GenerationTypes aEventType = EventData::GenerationTypes::Random);
	Event(EventData::GenerationData aEventData);

	static void PlayRound();
	
	const bool IsActive() const;
	const int GetMagnitude() const;
	const int GetCurrentEnemies() const;
	Enemy& GetEnemy(int aValue);
	const bool InjureEnemy(std::vector<Item>& aLootVector, int aDamage, int aIndex = 0);
	const bool EnemyIsDead(int aIndex);
	void RemoveEnemy(int aIndex);
	void TakeTurn(Player& aTargetPlayer);

private:
	const EventData::GenerationData myGenerationData;
	std::vector<Enemy> myEnemies;

	const EventData::GenerationData GenerateData(EventData::GenerationTypes aEventType, ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory);
	void PopulateEvent();
};