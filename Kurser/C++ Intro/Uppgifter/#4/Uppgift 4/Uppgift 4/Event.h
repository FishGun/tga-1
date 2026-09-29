#pragma once
#include "EventData.h"
#include "Enemy.h"

#include <vector>

class Event
{
public:
	Event() = delete;
	Event(EventData::GenerationTypes aEventType = EventData::GenerationTypes::Random);
	Event(EventData::GenerationData aEventData);

	static void PlayRound();
	
	const bool IsActive() const;
	const int GetMagnitude() const;
	const int GetCurrentEnemies() const;
	const Enemy& GetEnemy(int aValue) const;
	const bool InjureEnemy(int aDamage, int aIndex = 0);
	const bool EnemyIsDead(int aIndex);
	void RemoveEnemy(int aIndex);
	void TakeTurn(Entity& aTargetEntity);

private:
	const EventData::GenerationData myGenerationData;
	std::vector<Enemy> myEnemies;

	const EventData::GenerationData GenerateData(EventData::GenerationTypes aEventType);
	void GenerateEvent();
};