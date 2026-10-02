#pragma once
#include <string>
#include <vector>

namespace MenuData
{
	const std::vector<std::string> MAIN_OPTIONS =
	{
		"Play",
		"Cheats",
		"Exit"
	};
	const int MAIN_OPTIONS_SIZE = static_cast<int>(MAIN_OPTIONS.size());

	const std::vector<std::string> CHEAT_OPTIONS =
	{
		"Iron Man (invincibility)",
		"Hulk (instakill)"
	};
	const int CHEAT_OPTIONS_SIZE = static_cast<int>(CHEAT_OPTIONS.size());

	const std::vector<std::string> GENERIC_ROOM_OPTIONS =
	{
		"Change room",
		"Show stats & inventory"
	};
	const int GENERIC_ROOM_OPTIONS_SIZE = static_cast<int>(GENERIC_ROOM_OPTIONS.size());

	const std::vector<std::string> CONTEXTUAL_ROOM_OPTIONS =
	{
		"Pick up an item",
		"Open a chest",
		"Activate a spell"
	};
	const int CONTEXTUAL_ROOM_OPTIONS_SIZE = static_cast<int>(CONTEXTUAL_ROOM_OPTIONS.size());

	const std::vector<std::string> LOCKED_DOOR_OPTIONS =
	{
		"Lockpick",
		"Break"
	};
	const int LOCKED_DOOR_OPTIONS_SIZE = static_cast<int>(LOCKED_DOOR_OPTIONS.size());
}