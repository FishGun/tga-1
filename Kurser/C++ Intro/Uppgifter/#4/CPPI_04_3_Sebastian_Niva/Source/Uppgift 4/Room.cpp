#include "Room.h"
#include "RandomController.h"

#include <assert.h>

Room::Room(const RoomData::GenerationData aGenerationData, Room* aPreviousRoom, DoorData::GenerationTypes aDoorType) : myGenerationData(aGenerationData), myPreviousDoor(CreateDoorway(aPreviousRoom, aDoorType))
{
	PopulateLoot();
}
Room::Room(ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, const RoomData::GenerationTypes aRoomType, Room* aPreviousRoom, std::vector<Door*> aInitialForwardDoors, DoorData::GenerationTypes aDoorType) : Room(GenerateData(aRoomType, aItemFactory, aEnemyFactory, aInitialForwardDoors, CreateDoorway(aPreviousRoom, aDoorType))) {}
Room::Room(ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, const RoomData::GenerationTypes aRoomType,  Door* aPreviousDoor, std::vector<Door*> aInitialForwardDoors) : Room(GenerateData(aRoomType, aItemFactory, aEnemyFactory, aInitialForwardDoors, aPreviousDoor)) {}
Room::Room(const RoomData::GenerationData aGenerationData) : myGenerationData(aGenerationData), myPreviousDoor(myGenerationData.initialPreviousDoor), myForwardDoors(myGenerationData.initialForwardDoors)
{
	PopulateLoot();
}

Door* Room::GetReturnDoor() const
{
	return myPreviousDoor;
}
Door* const Room::GetForwardDoor(const int aIndex) const
{
	const int totalForwardDoors = GetForwardDoorTotal();
	if (totalForwardDoors > aIndex)
	{
		return myForwardDoors.at(aIndex);
	}
	return NULL;
}
const int Room::GetForwardDoorTotal() const
{
	return static_cast<int>(myForwardDoors.size());
}
const int Room::GetDoorTotal() const
{
	return GetForwardDoorTotal() + (myPreviousDoor == NULL ? 0 : 1);
}

const char* Room::GetName() const
{
	return myGenerationData.name.c_str();
}

Door* const Room::AddForwardDoor(Door* const aDoor)
{
	for (int i = 0; i < GetForwardDoorTotal(); i++)
	{
		if (myForwardDoors.at(i) == NULL)
		{
			myForwardDoors.at(i) = aDoor;
			return aDoor;
		}
	}
	myForwardDoors.push_back(aDoor);
	return aDoor;
}

Event* const Room::GetEvent() const
{
	return myGenerationData.event;
}

const bool Room::HasActiveEvent() const
{
	return myGenerationData.event != NULL && myGenerationData.event->IsActive();
}

const bool Room::HasItem() const
{
	return myDroppedItems.size() > 0;
}
const bool Room::HasChest() const
{
	return myChests.size() > 0;
}
const bool Room::HasSpell() const
{
	return mySpells.size() > 0;
}

void Room::PopulateLoot()
{
	myDroppedItems = myGenerationData.droppedItems;
	// Ideally should be copying these values from myGenerationData, but not a priority right now.
	myChests = ChestData::GenerateWeightedChestVector(myGenerationData.itemFactory);
	mySpells = SpellData::GenerateWeightedSpellVector(ItemType::ROOM_SPELL_SPAWN_CHANCE, 1);
}

Door* const Room::CreateDoorway(Room* aOtherRoom, DoorData::GenerationTypes aDoorType)
{
	return CreateDoorway(Door::GenerateData(aOtherRoom, this, aDoorType));
}
Door* const Room::CreateDoorway(DoorData::GenerationData aDoorData)
{
	Room* const previousRoom = aDoorData.previousRoom;

	assert(previousRoom != NULL && "Fatal Error: A doorway was attempted to be made between a room and NULL");
	assert(previousRoom->GetForwardDoorTotal() < RoomData::MAX_FORWARD_DOORS && "Fatal Error: Doorway attempted to be created at an overpopulated parent");

	Door* const newDoor = new Door(aDoorData);
	return previousRoom->AddForwardDoor(newDoor);
}