#include "Dungeon.h"
#include "RandomController.h"

#include <assert.h>

Dungeon::Dungeon(DungeonData::GenerationTypes aDungeonType) : myGenerationData(GenerateData(aDungeonType)), myGenerationType(aDungeonType) {}
Dungeon::Dungeon(DungeonData::GenerationData aGenerationData) : myGenerationData(aGenerationData), myGenerationType(DungeonData::GenerationTypes::Untyped) {}

const char* Dungeon::GetName() const
{
	return myGenerationData.name.c_str();
}

const int Dungeon::GetRoomTotal() const
{
	return static_cast<int>(myGenerationData.rooms.size());
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
			int roomTotal = RandomController::GenerateNumber(DungeonData::globalMinDungeonRooms, DungeonData::globalMaxDungeonRooms);
			std::vector<Room*> rooms;
			rooms.reserve(roomTotal);
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
				else if (attachRoom->GetForwardDoorTotal() >= RoomData::globalMaxForwardDoors || (highestRoomIndex > roomAttachIndex && RandomController::GenerateNumber(1,DungeonData::globalOneInValueChanceOfBranch) == 1))
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
			rooms.reserve(3);
			rooms.push_back(new Room(RoomData::GenerationTypes::RandomCombat));
			RoomData::GenerationData room2Generation =
			{
				.roomType = RoomData::GenerationTypes::CountOrUntyped,
				.name = "The Moat House",
				.event = new Event(EventData::GenerationData
					{
						.eventType = EventData::GenerationTypes::CountOrUntyped,
						.magnitude = 2
					}
				)
			};
			RoomData::GenerationData room3Generation =
			{
				.roomType = RoomData::GenerationTypes::CountOrUntyped,
				.name = "The Pillory",
				.event = new Event(EventData::GenerationData
					{
						.eventType = EventData::GenerationTypes::CountOrUntyped,
						.magnitude = 6
					}
				)
			};
			rooms.push_back(new Room(room2Generation, rooms.at(0), DoorData::GenerationTypes::Pickable));
			rooms.push_back(new Room(room3Generation, rooms.at(0), DoorData::GenerationTypes::Breakable));
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
	const std::string pickedPrefix = DungeonData::globalPrefixes[RandomController::GenerateNumber(0, DungeonData::globalPrefixAmount - 1)].c_str();

	const std::string pickedSuffix = DungeonData::globalSuffixes[RandomController::GenerateNumber(0, DungeonData::globalSuffixAmount - 1)].c_str();

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