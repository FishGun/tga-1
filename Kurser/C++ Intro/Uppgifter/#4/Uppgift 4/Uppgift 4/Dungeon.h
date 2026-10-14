#pragma once
#include "DungeonData.h"
#include "Room.h"
#include "Door.h"

class Dungeon
{
public:
	Dungeon(DungeonData::GenerationType aDungeonType = DungeonData::GenerationType::Random);
	Dungeon(DungeonData::GenerationData aGenerationData);

	const char* GetName() const;
	const int GetRoomTotal() const;
	Room* GetRoom(int aIndex);
	const int GetCurrentRound() const;
	void IncrementRound();

	const static DungeonData::GenerationData GenerateData(DungeonData::GenerationType aDungeonType);
	const static std::string GenerateRandomName();
private:
	const DungeonData::GenerationData myGenerationData;
	const DungeonData::GenerationType myGenerationType;
	int myRoundTracker = { 0 };
};