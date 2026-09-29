#pragma once
#include "DoorData.h"
#include "RoomData.h"

class Door
{
public:
	Door() = delete;
	Door(Room* aPreviousRoom, const RoomData::GenerationData aNextRoomData, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Door(Room* aPreviousRoom, Room* const aNextRoom, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Door(DoorData::GenerationData aGenerationData);

	const Room* const GetPreviousRoom() const;
	const Room* const GetNextRoom() const;
	const bool IsOpen() const;
	bool TryPick(int aValue);
	bool TryBreak(int aValue);

	static const DoorData::GenerationData GenerateData(Room* aPreviousRoom, const Room* aNextRoom, DoorData::GenerationTypes aDoorType);
	const DoorData::GenerationData myGenerationData;
private:
	bool myIsOpen;

};

