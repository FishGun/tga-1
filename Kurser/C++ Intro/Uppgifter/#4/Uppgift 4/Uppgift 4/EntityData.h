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

	const int MIN_NAME_LENGTH = 3;
	const int MAX_NAME_LENGTH = 25;

	struct BaseData
	{
		char name[MAX_NAME_LENGTH] = "N/A";
		int strength = 0;
		int dexterity = 0;
		int physique = 0;
	};

	const BaseData BASE_PLAYER_STATS
	{
		.name = "Player",
		.strength = 10,
		.dexterity = 10,
		.physique = 10
	};
	struct DerivedData
	{
		int attack = 0;
		int defense = 0;
		int carryingCapacity = 0;
		int hitPointMax = 0;
	};

	const int DEFENSE_DIVIDER = 4;
}