#pragma once
#include "Event.h"
//#include "Door.h"
// door include may cause recursion issues. "extern class Door;"

#include <vector>
#include <string>
class Door;

namespace RoomData
{
	const int globalMaxForwardDoors = 3;

	enum class GenerationTypes
	{
		Random,
		Empty,
		RandomCombat,
		CountOrUntyped
	};
	const int globalRandomTypeIndex = static_cast<int>(GenerationTypes::Random);
	const int globalTypesSize = static_cast<int>(GenerationTypes::CountOrUntyped);

	const std::vector<std::string> globalPrefixes =
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
	const int globalPrefixAmount = static_cast<int>(RoomData::globalPrefixes.size());

	const std::vector<std::string> globalSuffixes =
	{
		"Pantry",
		"Quaters",
		"Infirmary",
		"Kitchen",
		"Armory",
		"Treasury",
		"Cells"
	};
	const int globalSuffixAmount = static_cast<int>(RoomData::globalSuffixes.size());

	struct GenerationData
	{
		const GenerationTypes roomType;
		const std::string name;
		std::vector<Door*> initialForwardDoors;
		Door* const initialPreviousDoor = NULL;
		Event* event = NULL;
	};
}