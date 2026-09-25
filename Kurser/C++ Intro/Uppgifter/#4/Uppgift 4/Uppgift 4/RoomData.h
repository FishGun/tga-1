#pragma once
#include "Event.h"
//#include "Door.h"
// door include may cause recursion issues. "extern class Door;"

#include <vector>
#include <string>
class Door;

namespace RoomData
{
	const int maxForwardDoors = 3;

	enum class GenerationTypes
	{
		Random,
		Empty,
		RandomCombat,
		Count
	};
	const int randomTypeIndex = static_cast<int>(GenerationTypes::Random);
	const int typesSize = static_cast<int>(GenerationTypes::Count);

	const std::vector<std::string> prefixes =
	{
		"The",
		"The Masters",
		"The Servants",
		"The Bleeding",
		"The Ruined",
		"The Golden",
		"The Fragrant",
		"The Hound"
	};
	const int prefixAmount = static_cast<int>(RoomData::prefixes.size());

	const std::vector<std::string> suffixes =
	{
		"Pantry",
		"Quaters",
		"Infirmary",
		"Kitchen",
		"Armory",
		"Treasury",
		"Cells"
	};
	const int suffixAmount = static_cast<int>(RoomData::suffixes.size());

	struct GenerationData
	{
		const GenerationTypes roomType;
		const std::string name;
		const Door* initialPreviousDoor = NULL;
		const Door* initialForwardDoors[maxForwardDoors] = { NULL };
		const Event* event = NULL;
	};
}