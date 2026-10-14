#pragma once
#include "DoorData.h"
#include "RoomData.h"
//class Room;

class Door
{
public:
	Door() = delete;
	Door(Room* aPreviousRoom, const RoomData::GenerationData aNextRoomData, DoorData::GenerationType aDoorType = DoorData::GenerationType::Open);
	Door(Room* aPreviousRoom, Room* const aNextRoom, DoorData::GenerationType aDoorType = DoorData::GenerationType::Open);
	Door(DoorData::GenerationData aGenerationData);

	Room* GetPreviousRoom();
	Room* GetNextRoom();
	const bool IsOpen() const;
	bool TryPick(int aValue);
	bool TryBreak(int aValue);

	static const DoorData::GenerationData GenerateData(Room* aPreviousRoom, Room* aNextRoom, DoorData::GenerationType aDoorType);
	const DoorData::GenerationData myGenerationData;
private:
	bool myIsOpen;

};

