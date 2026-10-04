#include "Room.h"
#include "RandomController.h"

#include <assert.h>

Room::Room(const RoomData::GenerationData aGenerationData, Room* aPreviousRoom, DoorData::GenerationTypes aDoorType) : myGenerationData(aGenerationData), myPreviousDoor(CreateDoorway(aPreviousRoom, aDoorType))
{
	PopulateLoot();
}
Room::Room(const RoomData::GenerationTypes aRoomType, Room* aPreviousRoom, std::vector<Door*> aInitialForwardDoors, DoorData::GenerationTypes aDoorType) : Room(GenerateData(aRoomType, aInitialForwardDoors, CreateDoorway(aPreviousRoom, aDoorType))) {}
Room::Room(const RoomData::GenerationTypes aRoomType, Door* aPreviousDoor, std::vector<Door*> aInitialForwardDoors) : Room(GenerateData(aRoomType, aInitialForwardDoors, aPreviousDoor)) {}
Room::Room(const RoomData::GenerationData aGenerationData) : myGenerationData(aGenerationData), myPreviousDoor(myGenerationData.initialPreviousDoor), myForwardDoors(myGenerationData.initialForwardDoors)
{
	PopulateLoot();
}

Door* Room::GetReturnDoor() const
{
	return myPreviousDoor;
}
Door* const Room::GetForwardDoor(const int aIndex) const
{
	const int totalForwardDoors = GetForwardDoorTotal();
	if (totalForwardDoors > aIndex)
	{
		return myForwardDoors.at(aIndex);
	}
	return NULL;
}
const int Room::GetForwardDoorTotal() const
{
	return static_cast<int>(myForwardDoors.size());
}
const int Room::GetDoorTotal() const
{
	return GetForwardDoorTotal() + (myPreviousDoor == NULL ? 0 : 1);
}

const char* Room::GetName() const
{
	return myGenerationData.name.c_str();
}

Door* const Room::AddForwardDoor(Door* const aDoor)
{
	for (int i = 0; i < GetForwardDoorTotal(); i++)
	{
		if (myForwardDoors.at(i) == NULL)
		{
			myForwardDoors.at(i) = aDoor;
			return aDoor;
		}
	}
	myForwardDoors.push_back(aDoor);
	return aDoor;
}

Event* const Room::GetEvent() const
{
	return myGenerationData.event;
}

const bool Room::HasActiveEvent() const
{
	return myGenerationData.event != NULL && myGenerationData.event->IsActive();
}

const bool Room::HasItem() const
{
	return myDroppedItems.size() > 0;
}
const bool Room::HasChest() const
{
	return myChests.size() > 0;
}
const bool Room::HasSpell() const
{
	return mySpells.size() > 0;
}

void Room::PopulateLoot()
{
	myDroppedItems = myGenerationData.droppedItems;
	// Ideally should be copying these values from myGenerationData, but not a priority right now.
	myChests = ChestData::GenerateWeightedChestVector(ItemData::ROOM_CHEST_SPAWN_CHANCE, 1);
	mySpells = SpellData::GenerateWeightedSpellVector(ItemData::ROOM_SPELL_SPAWN_CHANCE, 1);
}

Door* const Room::CreateDoorway(Room* aOtherRoom, DoorData::GenerationTypes aDoorType)
{
	return CreateDoorway(Door::GenerateData(aOtherRoom, this, aDoorType));
}
Door* const Room::CreateDoorway(DoorData::GenerationData aDoorData)
{
	Room* const previousRoom = aDoorData.previousRoom;

	assert(previousRoom != NULL && "Fatal Error: A doorway was attempted to be made between a room and NULL");
	assert(previousRoom->GetForwardDoorTotal() < RoomData::MAX_FORWARD_DOORS && "Fatal Error: Doorway attempted to be created at an overpopulated parent");

	Door* const newDoor = new Door(aDoorData);
	return previousRoom->AddForwardDoor(newDoor);
}

const RoomData::GenerationData Room::GenerateData(RoomData::GenerationTypes aRoomType, std::vector<Door*> aInitialForwardDoors, Door* const aPreviousDoor)
{
	while (aRoomType == RoomData::GenerationTypes::Random)
	{
		aRoomType = static_cast<RoomData::GenerationTypes>(RandomController::GenerateNumber(RoomData::RANDOM_TYPE_INDEX + 1, RoomData::TYPES_SIZE - 1));
	}
	switch (aRoomType)
	{
	default:
	case RoomData::GenerationTypes::Empty:
	{
		return RoomData::GenerationData
		{
			.roomType = aRoomType,
			.name = GenerateRandomName(),
			.initialForwardDoors = aInitialForwardDoors,
			.initialPreviousDoor = aPreviousDoor,
			.event = NULL
		};
	}
	case RoomData::GenerationTypes::RandomCombat:
	{
		return RoomData::GenerationData
		{
			.roomType = aRoomType,
			.name = GenerateRandomName(),
			.initialForwardDoors = aInitialForwardDoors,
			.initialPreviousDoor = aPreviousDoor,
			.event = new Event(EventData::GenerationTypes::Random)
		};
	}
	}
}

const std::string Room::GenerateRandomName()
{
	const std::string pickedPrefix = RoomData::PREFIXES[RandomController::GenerateNumber(0, RoomData::PREFIXES_AMOUNT - 1)].c_str();

	const std::string pickedSuffix = RoomData::SUFFIXES[RandomController::GenerateNumber(0, RoomData::SUFFIXES_AMOUNT - 1)].c_str();

	std::string toReturn = "";
	toReturn.append(pickedPrefix);
	toReturn.append(" ");
	toReturn.append(pickedSuffix);
	toReturn.append(" (Room)");
	return toReturn.c_str();
}