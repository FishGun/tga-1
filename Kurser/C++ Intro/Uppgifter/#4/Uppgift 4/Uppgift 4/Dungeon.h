#pragma once
#include "DungeonData.h"
#include "Room.h"
#include "Door.h"

class Dungeon
{
public:
	Dungeon(DungeonData::GenerationTypes aDungeonType = DungeonData::GenerationTypes::Random);
	Dungeon(DungeonData::GenerationData aGenerationData);

	const char* GetName();
	const int GetRoomTotal();
	const Room* GetRoom(int aIndex);

	const static DungeonData::GenerationData GenerateData(DungeonData::GenerationTypes aDungeonType);
	const static std::string GenerateRandomName();
private:
	const DungeonData::GenerationData myGenerationData;
	const DungeonData::GenerationTypes myGenerationType;

	/*
	const Room* GenerateDungeon();
	const Room* GenerateRandomDungeon();
	const Room* GenerateTemplateDungeon();
	*/
};