#include "Dungeon.h"
#include "RandomController.h"

#include <assert.h>

Dungeon::Dungeon(DungeonData::GenerationTypes aDungeonType) : myGenerationData(GenerateData(aDungeonType)), myGenerationType(aDungeonType) {}
Dungeon::Dungeon(DungeonData::GenerationData aGenerationData) : myGenerationData(aGenerationData), myGenerationType(DungeonData::GenerationTypes::Untyped) {}

const char* Dungeon::GetName()
{
	return myGenerationData.name.c_str();
}

const int Dungeon::GetRoomTotal()
{
	return sizeof(myGenerationData.rooms) / sizeof(Room);
}

const Room* Dungeon::GetRoom(int aIndex)
{
	return myGenerationData.rooms[aIndex];
}

const DungeonData::GenerationData Dungeon::GenerateData(DungeonData::GenerationTypes aDungeonType)
{
	assert(aDungeonType != DungeonData::GenerationTypes::Untyped && "Fatal Error: Dungeon to generate was type Untyped. May only be applied to self-generated dungeons.");
	switch (aDungeonType)
	{
		case DungeonData::GenerationTypes::Random:
		case DungeonData::GenerationTypes::Untyped:
		default:
		{
			int roomTotal = RandomController::GenerateNumber(DungeonData::minDungeonRooms, DungeonData::maxDungeonRooms);
			std::vector<Room*> rooms;
			Room* attachRoom = NULL;
			int roomAttachIndex = -1;
			int highestRoomIndex = -1;
			for (int i = 0; i < roomTotal; i++)
			{
				if (attachRoom == NULL)
				{
					rooms.push_back(new Room(RoomData::GenerationTypes::Random));
				}
				else
				{
					rooms.push_back(new Room(RoomData::GenerationTypes::Random, attachRoom));
				}
				highestRoomIndex++;
				if (attachRoom == NULL)
				{
					roomAttachIndex = 0;
				}
				else if (attachRoom->GetForwardDoorTotal() >= RoomData::maxForwardDoors || (highestRoomIndex > roomAttachIndex && RandomController::GenerateNumber(1,DungeonData::oneInValueChanceOfBranch) == 1))
				{
					roomAttachIndex++;
				}
				attachRoom = rooms.at(roomAttachIndex);
			}
			return DungeonData::GenerationData
			{
				.name = GenerateRandomName(),
				.rooms = rooms
			};
		}
		case DungeonData::GenerationTypes::TheHold:
		{
			std::vector<Room*> rooms;
			rooms.push_back(new Room(RoomData::GenerationTypes::Empty));
			rooms.push_back(new Room(RoomData::GenerationTypes::RandomCombat, rooms.at(0)));
			rooms.push_back(new Room(RoomData::GenerationTypes::RandomCombat, rooms.at(0)));
			return DungeonData::GenerationData
			{
				.name = "The Hold (Dungeon)",
				.rooms = rooms
			};
		}
	}
}

const std::string Dungeon::GenerateRandomName()
{
	const std::string pickedPrefix = DungeonData::prefixes[RandomController::GenerateNumber(0, DungeonData::prefixAmount - 1)].c_str();

	const std::string pickedSuffix = DungeonData::suffixes[RandomController::GenerateNumber(0, DungeonData::suffixAmount - 1)].c_str();

	std::string name = "";
	name.append(pickedPrefix);
	name.append(" ");
	name.append(pickedSuffix);
	name.append(" (Dungeon)");
	return name;
}

/*
const Room* Dungeon::GenerateDungeon()
{
	switch (myDungeonType)
	{
		case DungeonData::GenerationTypes::Random: return GenerateRandomDungeon();
			break;
		case DungeonData::GenerationTypes::TheHold: return GenerateTemplateDungeon();
			break;
		default:
			break;
	}
}

const Room* Dungeon::GenerateRandomDungeon()
{
	myRooms.push_back(Room());
	for (int i = 1; i < myGenerationData.roomTotal; i++)
	{

	}



	Room* previousRoom;
	for (int i = 0; i < myGenerationData.roomTotal; i++)
	{
		if (i == 0)
		{
			myRooms.push_back(Room(RoomData::GenerationTypes::Random));
		}
		else
		{
			myRooms.push_back(Room(previousRoom));
		}
		previousRoom = &myRooms.at(i);
	}
}

const Room* Dungeon::GenerateTemplateDungeon()
{
	switch (myDungeonType)
	{
		case DungeonData::GenerationTypes::Random: return GenerateRandomDungeon();
		case DungeonData::GenerationTypes::TheHold:
		{
			myRooms[0] = Room();
			myRooms[1] = Room();
			myRooms[2] = Room();
			myRooms[3] = Room();
			myRooms[4] = Room();
		}
		default:
			break;
	}
}
*/