#pragma once
#include "Room.h"

#include <vector>
#include <string>

namespace DungeonData
{
	const int maxDungeonRooms = 5;
	const int minDungeonRooms = 3;
	const int oneInValueChanceOfBranch = 3;

	enum class GenerationTypes
	{
		Random,
		TheHold,
		Untyped
	};

	const std::vector<std::string> prefixes =
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
	const int prefixAmount = static_cast<int>(DungeonData::prefixes.size());

	const std::vector<std::string> suffixes =
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
	const int suffixAmount = static_cast<int>(DungeonData::suffixes.size());

	struct GenerationData
	{
		const std::string name;
		std::vector<Room*> rooms;
		//Room rooms[maxDungeonRooms];
	};
}