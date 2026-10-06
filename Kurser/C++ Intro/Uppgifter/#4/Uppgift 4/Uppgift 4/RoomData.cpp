#include "RoomData.h"
#include "RandomController.h"

namespace RoomData
{
	/*
	GenerationData::GenerationData(ItemFactory& aItemFactory)
	{
		droppedItems = aItemFactory.CreateWeightedVector(Item::ROOM_DROP_SPAWN_CHANCE, Item::ROOM_DROP_SPAWN_TRIES);
	}
	*/

	const GenerationData GenerateData(GenerationTypes aRoomType, ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, std::vector<Door*> aInitialForwardDoors, Door* aPreviousDoor)
	{
		while (aRoomType == GenerationTypes::Random)
		{
			aRoomType = static_cast<GenerationTypes>(RandomController::GenerateNumber(RANDOM_TYPE_INDEX + 1, TYPES_SIZE - 1));
		}
		switch (aRoomType)
		{
			default:
			case GenerationTypes::Empty:
			{
				return GenerationData
				{
					.roomType = aRoomType,
					.name = GenerateRandomName(),
					.itemFactory = aItemFactory,
					.initialForwardDoors = aInitialForwardDoors,
					.initialPreviousDoor = aPreviousDoor,
					.event = NULL,
					.droppedItems = aItemFactory.CreateWeightedVector()
				};
			}
			case GenerationTypes::RandomCombat:
			{
				return GenerationData
				{
					.roomType = aRoomType,
					.name = GenerateRandomName(),
					.itemFactory = aItemFactory,
					.initialForwardDoors = aInitialForwardDoors,
					.initialPreviousDoor = aPreviousDoor,
					.event = new Event(aItemFactory, aEnemyFactory, EventData::GenerationTypes::Random),
					.droppedItems = aItemFactory.CreateWeightedVector()
				};
			}
		}
	}
	const std::string GenerateRandomName()
	{
		const std::string pickedPrefix = PREFIXES[RandomController::GenerateNumber(0, PREFIXES_AMOUNT - 1)].c_str();

		const std::string pickedSuffix = SUFFIXES[RandomController::GenerateNumber(0, SUFFIXES_AMOUNT - 1)].c_str();

		std::string toReturn = "";
		toReturn.append(pickedPrefix);
		toReturn.append(" ");
		toReturn.append(pickedSuffix);
		toReturn.append(" (Room)");
		return toReturn.c_str();
	}
}