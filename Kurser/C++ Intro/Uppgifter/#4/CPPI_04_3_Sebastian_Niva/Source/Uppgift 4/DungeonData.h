#pragma once
#include "Room.h"
#include "ItemFactory.h"

#include <vector>
#include <string>

namespace DungeonData
{
	const int KILLS_TO_WIN = 9;

	const int MAX_DUNGEON_ROOMS = 5;
	const int MIN_DUNGEON_ROOMS = 3;
	const int ONE_IN_VALUE_CHANCE_OF_BRANCH = 3;

	enum class GenerationTypes
	{
		Random,
		TheHold,
		Untyped
	};

	const std::vector<std::string> PREFIXES =
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
	const int PREFIX_AMOUNT = static_cast<int>(DungeonData::PREFIXES.size());

	const std::vector<std::string> SUFFIXES =
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
	const int SUFFIX_AMOUNT = static_cast<int>(DungeonData::SUFFIXES.size());

	struct GenerationData
	{
		const std::string name;
		ItemFactory& itemFactory;
		std::vector<Room*> rooms;
	};
}