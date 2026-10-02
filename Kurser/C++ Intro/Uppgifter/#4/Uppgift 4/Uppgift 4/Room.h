#pragma once
#include "RoomData.h"
#include "Door.h"
#include "ItemData.h"
#include "ChestData.h"
#include "SpellData.h"

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

	const bool HasItem() const;
	const bool HasChest() const;
	const bool HasSpell() const;

	// Ideally should be copying these values from myGenerationData, but not a priority right now.
	std::vector<const ItemData::ItemInstanceData*> myDroppedItems = ItemData::GenerateWeightedItemVector(1.0f, 2); //0.34
	std::vector<ChestData::ChestInstance*> myChests = ChestData::GenerateWeightedChestVector(1.0f, 1); //0.5
	std::vector<const SpellData::SpellInstanceData*> mySpells = SpellData::GenerateWeightedSpellVector(1.0f, 1); // 0.2
private:
	const RoomData::GenerationData myGenerationData;
	Door* const myPreviousDoor;
	std::vector<Door*> myForwardDoors;

	Door* const CreateDoorway(Room* aOtherRoom, DoorData::GenerationTypes aDoorType = DoorData::GenerationTypes::Open) const;
	Door* const CreateDoorway(DoorData::GenerationData aDoorData) const;

	const RoomData::GenerationData GenerateData(RoomData::GenerationTypes aRoomType, std::vector<Door*> aInitialForwardDoors, Door* aPreviousDoor = NULL);

	const std::string GenerateRandomName();
};