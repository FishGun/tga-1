#pragma once
#include "RoomData.h"
#include "Door.h"
#include "Item.h"
#include "ChestData.h"
#include "SpellData.h"

class Room
{
public:
	Room(const RoomData::GenerationData aGenerationData, Room* aPreviousRoom, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Room(ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, const RoomData::GenerationTypes aRoomType, Room* aPreviousRoom, std::vector<Door*> aInitialForwardDoors = { NULL }, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Room(ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, const RoomData::GenerationTypes aRoomType = RoomData::GenerationTypes::Random, Door* aPreviousDoor = NULL, std::vector<Door*> aInitialForwardDoors = { NULL });
	Room(const RoomData::GenerationData aGenerationData);

	Door* GetReturnDoor() const;
	Door* const GetForwardDoor(const int aIndex) const;
	Door* const AddForwardDoor(Door* const aDoor);
	const int GetForwardDoorTotal() const;
	const int GetDoorTotal() const;
	const char* GetName() const;
	Event* const GetEvent() const;
	const bool HasActiveEvent() const;

	const bool HasItem() const;
	const bool HasChest() const;
	const bool HasSpell() const;

	std::vector<Item> myDroppedItems;
	std::vector<ChestData::ChestInstance*> myChests;
	std::vector<const SpellData::SpellInstanceData*> mySpells;
private:
	void PopulateLoot();

	const RoomData::GenerationData myGenerationData;
	Door* const myPreviousDoor;
	std::vector<Door*> myForwardDoors;

	Door* const CreateDoorway(Room* aOtherRoom, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open);
	Door* const CreateDoorway(DoorData::GenerationData aDoorData);

};