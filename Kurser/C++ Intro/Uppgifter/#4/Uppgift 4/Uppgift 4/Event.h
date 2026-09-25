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

	const bool IsActive();
private:
	const EventData::GenerationData myGenerationData;
	std::vector<Enemy> myEnemies;
	bool myIsActive = true;

	const EventData::GenerationData GenerateData(EventData::GenerationTypes aEventType);
	void GenerateEvent();
};