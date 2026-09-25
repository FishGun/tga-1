#include "Event.h"
#include "RandomController.h"

Event::Event(EventData::GenerationTypes aEventType) : Event(GenerateData(aEventType)) {}
Event::Event(EventData::GenerationData aEventData) : myGenerationData(aEventData)
{

}

const bool Event::IsActive()
{
	return myIsActive;
}

const EventData::GenerationData Event::GenerateData(EventData::GenerationTypes aEventType)
{
	while (aEventType == EventData::GenerationTypes::Random)
	{
		aEventType = static_cast<EventData::GenerationTypes>(RandomController::GenerateNumber(0, EventData::typesSize - 1));
	}
	switch (aEventType)
	{
		default:
		case EventData::GenerationTypes::EasyCombat:
		{
			return EventData::GenerationData
			{
				.eventType = aEventType,
				.magnitude = EventData::easyMagnitude
			};
		}
		case EventData::GenerationTypes::MediumCombat:
		{
			return EventData::GenerationData
			{
				.eventType = aEventType,
				.magnitude = EventData::mediumMagnitude
			};
		}
		case EventData::GenerationTypes::HardCombat:
		{
			return EventData::GenerationData
			{
				.eventType = aEventType,
				.magnitude = EventData::hardMagnitude
			};
		}
	}
}
void Event::GenerateEvent()
{
	myEnemies.clear();
	for (int i = 0; i < myGenerationData.magnitude; i++)
	{
		myEnemies.push_back(Enemy());
	}
	myIsActive = true;
}