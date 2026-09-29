#pragma once
#include <string>
#include <vector>

namespace MenuData
{
	const std::vector<std::string> globalMainOptions =
	{
		"Play",
		"Cheats",
		"Exit"
	};
	const int globalMainOptionsSize = static_cast<int>(globalMainOptions.size());

	const std::vector<std::string> globalCheatOptions =
	{
		"Iron Man (invincibility)",
		"Hulk (instakill)"
	};
	const int globalCheatOptionsSize = static_cast<int>(globalCheatOptions.size());

	const std::vector<std::string> globalRoomOptions =
	{
		"Change room",
		"Show stats"
	};
	const int globalRoomOptionsSize = static_cast<int>(globalRoomOptions.size());

	const std::vector<std::string> globalLockedDoorOptions =
	{
		"Lockpick",
		"Break"
	};
	const int globalLockedDoorOptionsSize = static_cast<int>(globalLockedDoorOptions.size());
}