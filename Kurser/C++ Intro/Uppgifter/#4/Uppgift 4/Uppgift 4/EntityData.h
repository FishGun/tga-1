#pragma once

namespace EntityData
{
	enum class BaseStatsEnum
	{
		Strength,
		Dexterity,
		Physique,
		Length
	};

	const int globalMinNameLength = 3;
	const int globalMaxNameLength = 18;

	struct BaseData
	{
		char name[globalMaxNameLength];
		int strength;
		int dexterity;
		int physique;
	};

	const BaseData playerBaseStats
	{
		.name = "Player",
		.strength = 10,
		.dexterity = 10,
		.physique = 10
	};
	const int globalDefenseDivider = 4;
}