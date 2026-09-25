#pragma once
#include "RoomData.h"
#include "Door.h"
//class Door;

class Room
{
public:
	Room(const RoomData::GenerationData aGenerationData, Room* aPreviousRoom);
	Room(const RoomData::GenerationTypes aRoomType, Room* aPreviousRoom, const Door* aInitialForwardDoors[RoomData::maxForwardDoors] = { NULL });
	Room(const RoomData::GenerationTypes aRoomType = RoomData::GenerationTypes::Random, Door* aPreviousDoor = NULL, const Door* aInitialForwardDoors[RoomData::maxForwardDoors] = { NULL });
	Room(const RoomData::GenerationData aGenerationData);

	const Door* GetReturnDoor() const;
	const Door* GetForwardDoor(const int aIndex) const;
	const Door* SetForwardDoor(const int aIndex, const Door* aDoor);
	const int GetForwardDoorTotal() const;
	const int GetDoorTotal() const;
	const char* GetName() const;
private:
	const RoomData::GenerationData myGenerationData;
	const Door* myPreviousDoor;
	const Door* myForwardDoors[RoomData::maxForwardDoors];

	const Door* CreateDoorway(Room* aOtherRoom, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open) const;
	const Door* CreateDoorway(DoorData::GenerationData aDoorData) const;

	const RoomData::GenerationData GenerateData(RoomData::GenerationTypes aRoomType, const Door* aPreviousDoor = NULL, const Door* aInitialForwardDoors[RoomData::maxForwardDoors] = { NULL });

	const std::string GenerateRandomName();

	/*
	const Room* GenerateDoorLinks();
	const Room* GenerateRandomRoom();
	const Room* GenerateTemplateRoom();
	*/
};