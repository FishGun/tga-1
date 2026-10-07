#pragma once
#include "Event.h"
#include "ItemFactory.h"

#include <vector>
#include <string>
class Door;

namespace RoomData
{
	const int MAX_FORWARD_DOORS = 3;

	enum class GenerationTypes
	{
		Random,
		Empty,
		RandomCombat,
		CountOrUntyped
	};
	const int RANDOM_TYPE_INDEX = static_cast<int>(GenerationTypes::Random);
	const int TYPES_SIZE = static_cast<int>(GenerationTypes::CountOrUntyped);

	const std::vector<std::string> PREFIXES =
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
	const int PREFIXES_AMOUNT = static_cast<int>(PREFIXES.size());

	const std::vector<std::string> SUFFIXES =
	{
		"Pantry",
		"Quaters",
		"Infirmary",
		"Kitchen",
		"Armory",
		"Treasury",
		"Cells"
	};
	const int SUFFIXES_AMOUNT = static_cast<int>(SUFFIXES.size());

	struct GenerationData
	{
		const GenerationTypes roomType;
		const std::string name;
		ItemFactory& itemFactory;
		std::vector<Door*> initialForwardDoors;
		Door* const initialPreviousDoor = NULL;
		Event* event = NULL;
		std::vector<Item> droppedItems;
	};

	const GenerationData GenerateData(GenerationTypes aRoomType, ItemFactory& aItemFactory, EnemyFactory& aEnemyFactory, std::vector<Door*> aInitialForwardDoors, Door* aPreviousDoor = NULL);
	const std::string GenerateRandomName();

}