#include "Dungeon.h"
#include "RandomController.h"

#include <assert.h>

Dungeon::Dungeon(DungeonData::GenerationType aDungeonType) : myGenerationData(GenerateData(aDungeonType)), myGenerationType(aDungeonType) {}
Dungeon::Dungeon(DungeonData::GenerationData aGenerationData) : myGenerationData(aGenerationData), myGenerationType(DungeonData::GenerationType::Untyped) {}

const char* Dungeon::GetName() const
{
	return myGenerationData.name.c_str();
}
const int Dungeon::GetRoomTotal() const
{
	return static_cast<int>(myGenerationData.rooms.size());
}
Room* Dungeon::GetRoom(int aIndex)
{
	return myGenerationData.rooms[aIndex];
}
const int Dungeon::GetCurrentRound() const
{
	return myRoundTracker;
}
void Dungeon::IncrementRound()
{
	myRoundTracker++;
}

const DungeonData::GenerationData Dungeon::GenerateData(DungeonData::GenerationType aDungeonType)
{
	assert(aDungeonType != DungeonData::GenerationType::Untyped && "Fatal Error: Dungeon to generate was type Untyped. May only be applied to self-generated dungeons.");
	switch (aDungeonType)
	{
		case DungeonData::GenerationType::Random:
		case DungeonData::GenerationType::Untyped:
		default:
		{
			ItemFactory& itemFactory = *new ItemFactory();
			EnemyFactory& enemyFactory = *new EnemyFactory();
			int roomTotal = RandomController::GenerateNumber(DungeonData::MIN_DUNGEON_ROOMS, DungeonData::MAX_DUNGEON_ROOMS);
			std::vector<Room*> rooms;
			rooms.reserve(roomTotal);
			Room* attachRoom = NULL;
			int roomAttachIndex = -1;
			int highestRoomIndex = -1;

			for (int i = 0; i < roomTotal; i++)
			{
				if (attachRoom == NULL)
				{
					rooms.push_back(new Room(itemFactory, enemyFactory, RoomData::GenerationType::Random));
				}
				else
				{
					rooms.push_back(new Room(itemFactory, enemyFactory, RoomData::GenerationType::Random, attachRoom));
				}
				highestRoomIndex++;
				if (attachRoom == NULL)
				{
					roomAttachIndex = 0;
				}
				else if (attachRoom->GetForwardDoorTotal() >= RoomData::MAX_FORWARD_DOORS || (highestRoomIndex > roomAttachIndex && RandomController::GenerateNumber(1,DungeonData::ONE_IN_VALUE_CHANCE_OF_BRANCH) == 1))
				{
					roomAttachIndex++;
				}
				attachRoom = rooms.at(roomAttachIndex);
			}
			return DungeonData::GenerationData
			{
				.name = GenerateRandomName(),
				.itemFactory = itemFactory,
				.rooms = rooms
			};
		}
		case DungeonData::GenerationType::TheHold:
		{
			ItemFactory& itemFactory = *new ItemFactory();
			EnemyFactory& enemyFactory = *new EnemyFactory();
			std::vector<Room*> rooms;
			rooms.reserve(3);
			RoomData::GenerationData room1Generation =
			{
				.roomType = RoomData::GenerationType::CountOrUntyped,
				.name = "The Foyer",
				.itemFactory = itemFactory,
				.event = new Event(itemFactory, enemyFactory, EventData::GenerationType::EasyCombat)
			};
			RoomData::GenerationData room2Generation =
			{
				.roomType = RoomData::GenerationType::CountOrUntyped,
				.name = "The Moat House",
				.itemFactory = itemFactory,
				.event = new Event(EventData::GenerationData
					{
						.eventType = EventData::GenerationType::CountOrUntyped,
						.itemFactory = itemFactory,
						.enemyFactory = enemyFactory,
						.magnitude = 3
					}
				)
			};
			RoomData::GenerationData room3Generation =
			{
				.roomType = RoomData::GenerationType::CountOrUntyped,
				.name = "The Pillory",
				.itemFactory = itemFactory,
				.event = new Event(EventData::GenerationData
					{
						.eventType = EventData::GenerationType::CountOrUntyped,
						.itemFactory = itemFactory,
						.enemyFactory = enemyFactory,
						.magnitude = 5
					}
				)
			};
			rooms.push_back(new Room(room1Generation));
			rooms.push_back(new Room(room2Generation, rooms.at(0), DoorData::GenerationType::Pickable));
			rooms.push_back(new Room(room3Generation, rooms.at(0), DoorData::GenerationType::Breakable));
			return DungeonData::GenerationData
			{
				.name = "The Hold (Dungeon)",
				.itemFactory = itemFactory,
				.rooms = rooms
			};
		}
	}
}

const std::string Dungeon::GenerateRandomName()
{
	const std::string pickedPrefix = DungeonData::PREFIXES[RandomController::GenerateNumber(0, DungeonData::PREFIX_AMOUNT - 1)].c_str();

	const std::string pickedSuffix = DungeonData::SUFFIXES[RandomController::GenerateNumber(0, DungeonData::SUFFIX_AMOUNT - 1)].c_str();

	std::string name = "";
	name.append(pickedPrefix);
	name.append(" ");
	name.append(pickedSuffix);
	name.append(" (Dungeon)");
	return name;
}