#include "Door.h"
#include "Room.h"

Door::Door(Room* aPreviousRoom, const RoomData::GenerationData aNextRoomData, DoorData::GenerationTypes aDoorType) : Door(GenerateData(aPreviousRoom, new Room(aNextRoomData), aDoorType)){}
Door::Door(Room* aPreviousRoom, Room* const aNextRoom, DoorData::GenerationTypes aDoorType) : Door(GenerateData(aPreviousRoom, aNextRoom, aDoorType)) {}
Door::Door(DoorData::GenerationData aGenerationData) : myGenerationData(aGenerationData),
myIsOpen(myGenerationData.doorType == DoorData::GenerationTypes::Open) { }

const Room* const Door::GetPreviousRoom() const
{
	return myGenerationData.previousRoom;
}
const Room* const Door::GetNextRoom() const
{
	return myGenerationData.nextRoom;
}
const bool Door::IsOpen() const
{
	return myIsOpen;
}
bool Door::TryPick(int aValue)
{
	if (aValue >= myGenerationData.pickDC)
	{
		myIsOpen = true;
	}
	return myIsOpen;
}
bool Door::TryBreak(int aValue)
{
	if (aValue >= myGenerationData.breakDC)
	{
		myIsOpen = true;
	}
	return myIsOpen;
}

const DoorData::GenerationData Door::GenerateData(Room* aPreviousRoom, const Room* aNextRoom, DoorData::GenerationTypes aDoorType)
{
	int pickDC;
	int breakDC;
	switch (aDoorType)
	{
		case DoorData::GenerationTypes::Easy:
		{
			pickDC = 7;
			breakDC = 7;
			break;
		}
		case DoorData::GenerationTypes::Hard:
		{
			pickDC = 14;
			breakDC = 14;
			break;
		}
		case DoorData::GenerationTypes::Pickable:
		{
			pickDC = 7;
			breakDC = 30;
			break;
		}
		case DoorData::GenerationTypes::Breakable:
		{
			pickDC = 30;
			breakDC = 7;
			break;
		}
		case DoorData::GenerationTypes::Open:
		default:
		{
			pickDC = 0;
			breakDC = 0;
			break;
		}
	}
	return DoorData::GenerationData
	{
		.doorType = aDoorType,
		.previousRoom = aPreviousRoom,
		.nextRoom = aNextRoom,
		.pickDC = pickDC,
		.breakDC = breakDC
	};
}