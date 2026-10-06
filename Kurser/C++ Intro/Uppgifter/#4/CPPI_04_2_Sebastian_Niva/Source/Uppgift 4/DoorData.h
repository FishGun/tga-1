#pragma once
#include <string>
class Room;

namespace DoorData
{
	enum class GenerationTypes
	{
		Open,
		Easy,
		Hard,
		Pickable,
		Breakable,
		UntypedLocked
	};

	struct GenerationData
	{
		const GenerationTypes doorType;
		Room* const previousRoom;
		Room* const nextRoom;
		const int pickDC;
		const int breakDC;
	};
}