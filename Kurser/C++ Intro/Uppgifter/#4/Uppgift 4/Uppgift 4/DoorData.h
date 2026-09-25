#pragma once
//#include "Room.h"
// room include may cause recursion issues. "extern class Room;"

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
		Room* previousRoom;
		const Room* nextRoom;
		const int pickDC;
		const int breakDC;
	};
}