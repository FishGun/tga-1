#pragma once
#include "RoomData.h"
#include "Door.h"

class Room
{
public:
	Room(const RoomData::GenerationData aGenerationData, Room* aPreviousRoom, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Room(const RoomData::GenerationTypes aRoomType, Room* aPreviousRoom, std::vector<Door*> aInitialForwardDoors = { NULL }, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Room(const RoomData::GenerationTypes aRoomType = RoomData::GenerationTypes::Random, Door* aPreviousDoor = NULL, std::vector<Door*> aInitialForwardDoors = { NULL });
	Room(const RoomData::GenerationData aGenerationData);

	Door* GetReturnDoor() const;
	Door* const GetForwardDoor(const int aIndex) const;
	Door* const AddForwardDoor(Door* const aDoor);
	const int GetForwardDoorTotal() const;
	const int GetDoorTotal() const;
	const char* GetName() const;
	Event* const GetEvent() const;
	const bool HasActiveEvent() const;
private:
	const RoomData::GenerationData myGenerationData;
	Door* const myPreviousDoor;
	std::vector<Door*> myForwardDoors;

	Door* const CreateDoorway(Room* aOtherRoom, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open) const;
	Door* const CreateDoorway(DoorData::GenerationData aDoorData) const;

	const RoomData::GenerationData GenerateData(RoomData::GenerationTypes aRoomType, std::vector<Door*> aInitialForwardDoors, Door* aPreviousDoor = NULL);

	const std::string GenerateRandomName();
};