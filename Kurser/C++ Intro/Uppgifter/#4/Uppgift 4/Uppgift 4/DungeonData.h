#pragma once
#include "Room.h"

#include <vector>
#include <string>

namespace DungeonData
{
	const int globalMaxDungeonRooms = 5;
	const int globalMinDungeonRooms = 3;
	const int globalOneInValueChanceOfBranch = 3;

	enum class GenerationTypes
	{
		Random,
		TheHold,
		Untyped
	};

	const std::vector<std::string> globalPrefixes =
	{
		"The",
		"Vlad's",
		"Joel's",
		"Qrikko's",
		"Vlad's",
		"Giant's",
		"The Mountian King's",
		"The Rotten",
		"The Soul-Shattering",
		"The Nightmare",
		"The Endless",
		"The Dead"
	};
	const int globalPrefixAmount = static_cast<int>(DungeonData::globalPrefixes.size());

	const std::vector<std::string> globalSuffixes =
	{
		"Dungeon",
		"Lair",
		"Nest",
		"Guts",
		"Circus",
		"Catacombs",
		"Mountians of Madness",
		"Corpse",
		"Blood Caverns",
		"Halls",
		"Ravine"
	};
	const int globalSuffixAmount = static_cast<int>(DungeonData::globalSuffixes.size());

	struct GenerationData
	{
		const std::string name;
		std::vector<Room*> rooms;
		//Room rooms[maxDungeonRooms];
	};
}