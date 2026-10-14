#pragma once
#include <string>
class Room;

namespace DoorData
{
	enum class GenerationType
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
		const GenerationType doorType;
		Room* const previousRoom;
		Room* const nextRoom;
		const int pickDC;
		const int breakDC;
	};
}