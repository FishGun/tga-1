#include "Room.h"
#include "RandomController.h"
#include <assert.h>

Room::Room(const RoomData::GenerationData aGenerationData, Room* aPreviousRoom) : myGenerationData(aGenerationData), myPreviousDoor(CreateDoorway(aPreviousRoom)) {}
Room::Room(const RoomData::GenerationTypes aRoomType, Room* aPreviousRoom, const Door* aInitialForwardDoors[RoomData::maxForwardDoors]) : Room(GenerateData(aRoomType, CreateDoorway(aPreviousRoom), aInitialForwardDoors)) {}
Room::Room(const RoomData::GenerationTypes aRoomType, Door* aPreviousDoor, const Door* aInitialForwardDoors[RoomData::maxForwardDoors]) : Room(GenerateData(aRoomType, aPreviousDoor, aInitialForwardDoors)) {}
Room::Room(const RoomData::GenerationData aGenerationData) : myGenerationData(aGenerationData), myPreviousDoor(myGenerationData.initialPreviousDoor), myForwardDoors(*myGenerationData.initialForwardDoors)
{
	//GenerateDoorLinks();
}

const Door* Room::GetReturnDoor() const
{
	return myPreviousDoor;
}
const Door* Room::GetForwardDoor(const int aIndex) const
{
	const int totalForwardDoors = GetForwardDoorTotal();
	if (totalForwardDoors > aIndex)
	{
		return myForwardDoors[aIndex];
	}
	return NULL;
}
const int Room::GetForwardDoorTotal() const
{
	int toReturn = 0;
	for (; toReturn < RoomData::maxForwardDoors; toReturn++)
	{
		if (myForwardDoors[toReturn] == NULL)
		{
			return toReturn;
		}
	}
	return toReturn;
}
const int Room::GetDoorTotal() const
{
	return GetForwardDoorTotal() + (myPreviousDoor == NULL ? 0 : 1);
}

const char* Room::GetName() const
{
	return myGenerationData.name.c_str();
}

const Door* Room::SetForwardDoor(const int aIndex, const Door* aDoor)
{
	return myForwardDoors[aIndex] = aDoor;
}

const Door* Room::CreateDoorway(Room* aOtherRoom, DoorData::GenerationTypes aDoorType) const
{
	return CreateDoorway(Door::GenerateData(aOtherRoom, this, aDoorType));
}
const Door* Room::CreateDoorway(DoorData::GenerationData aDoorData) const
{
	Room* previousRoom = aDoorData.previousRoom;

	assert(previousRoom != NULL && "Fatal Error: A doorway was attempted to be made between a room and NULL");
	assert(previousRoom->GetForwardDoorTotal() < RoomData::maxForwardDoors && "Fatal Error: Doorway attempted to be created at an overpopulated parent");

	const Door* newDoor = new Door(aDoorData);
	return previousRoom->SetForwardDoor(previousRoom->GetForwardDoorTotal(), newDoor);
}

const RoomData::GenerationData Room::GenerateData(RoomData::GenerationTypes aRoomType, const Door* aPreviousDoor, const Door* aInitialForwardDoors[RoomData::maxForwardDoors])
{
	while (aRoomType == RoomData::GenerationTypes::Random)
	{
		aRoomType = static_cast<RoomData::GenerationTypes>(RandomController::GenerateNumber(RoomData::randomTypeIndex + 1, RoomData::typesSize - 1));
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
				.initialPreviousDoor = aPreviousDoor,
				.initialForwardDoors = aInitialForwardDoors == NULL ? NULL : *aInitialForwardDoors,
				.event = NULL
			};
		}
		case RoomData::GenerationTypes::RandomCombat:
		{
			return RoomData::GenerationData
			{
				.roomType = aRoomType,
				.name = GenerateRandomName(),
				.initialPreviousDoor = aPreviousDoor,
				.initialForwardDoors = aInitialForwardDoors == NULL ? NULL : *aInitialForwardDoors,
				.event = new Event(EventData::GenerationTypes::Random)
			};
		}
	}
}

const std::string Room::GenerateRandomName()
{
	const std::string pickedPrefix = RoomData::prefixes[RandomController::GenerateNumber(0, RoomData::prefixAmount - 1)].c_str();

	const std::string pickedSuffix = RoomData::suffixes[RandomController::GenerateNumber(0, RoomData::suffixAmount - 1)].c_str();

	std::string toReturn = "";
	toReturn.append(pickedPrefix);
	toReturn.append(" ");
	toReturn.append(pickedSuffix);
	toReturn.append(" (Room)");
	return toReturn.c_str();
}

/*
const Room* Room::GenerateDoorLinks()
{
	for (int i = 0; i < sizeof(myGenerationData.forwardDoors); i++)
	{
		myForwardDoors.push_back(new Door(this, new Room()));
	}
}
const Room* Room::GenerateRandomRoom();
const Room* Room::GenerateTemplateRoom();
*/