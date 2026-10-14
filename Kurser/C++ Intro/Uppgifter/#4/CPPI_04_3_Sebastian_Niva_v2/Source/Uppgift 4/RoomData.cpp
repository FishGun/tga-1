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

	const GenerationData GenerateData(GenerationType aRoomType, ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, std::vector<Door*> aInitialForwardDoors, Door* aPreviousDoor)
	{
		while (aRoomType == GenerationType::Random)
		{
			aRoomType = static_cast<GenerationType>(RandomController::GenerateNumber(RANDOM_TYPE_INDEX + 1, TYPE_SIZE - 1));
		}
		switch (aRoomType)
		{
			default:
			case GenerationType::Empty:
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
			case GenerationType::RandomCombat:
			{
				return GenerationData
				{
					.roomType = aRoomType,
					.name = GenerateRandomName(),
					.itemFactory = aItemFactory,
					.initialForwardDoors = aInitialForwardDoors,
					.initialPreviousDoor = aPreviousDoor,
					.event = new Event(aItemFactory, aEnemyFactory, EventData::GenerationType::Random),
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