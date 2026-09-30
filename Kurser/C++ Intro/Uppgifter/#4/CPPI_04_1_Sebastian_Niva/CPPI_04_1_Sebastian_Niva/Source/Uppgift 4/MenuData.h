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

	const std::vector<std::string> ROOM_OPTIONS =
	{
		"Change room",
		"Show stats"
	};
	const int ROOM_OPTIONS_SIZE = static_cast<int>(ROOM_OPTIONS.size());

	const std::vector<std::string> LOCKED_DOOR_OPTIONS =
	{
		"Lockpick",
		"Break"
	};
	const int LOCKED_DOOR_OPTIONS_SIZE = static_cast<int>(LOCKED_DOOR_OPTIONS.size());
}