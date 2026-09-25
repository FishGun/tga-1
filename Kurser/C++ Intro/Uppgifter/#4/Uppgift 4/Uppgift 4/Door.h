#pragma once
#include "DoorData.h"
#include "RoomData.h"

class Door
{
public:
	Door() = delete;
	Door(Room* aPreviousRoom, const RoomData::GenerationData aNextRoomData, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Door(Room* aPreviousRoom, const Room* aNextRoom, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Door(DoorData::GenerationData aGenerationData);

	const Room* GetPreviousRoom() const;
	const Room* GetNextRoom() const;
	const bool IsOpen() const;
	bool TryPick(int aValue);
	bool TryBreak(int aValue);

	static const DoorData::GenerationData GenerateData(Room* aPreviousRoom, const Room* aNextRoom, DoorData::GenerationTypes aDoorType);
private:
	const DoorData::GenerationData myGenerationData;
	bool myIsOpen;

};

