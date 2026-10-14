#pragma once
#include "ItemFactory.h"
#include "EnemyFactory.h"

namespace EventData
{
	enum class GenerationType
	{
		Random,
		EasyCombat,
		MediumCombat,
		HardCombat,
		CountOrUntyped
	};
	const int TYPE_SIZE = static_cast<int>(GenerationType::CountOrUntyped);
	const int EASY_MAGNITUDE = 1;
	const int MEDIUM_MAGNITUDE = 3;
	const int HARD_MAGNITUDE = 5;

	struct GenerationData
	{
		const GenerationType eventType;
		ItemFactory& itemFactory;
		EnemyFactory& enemyFactory;
		const int magnitude;
	};
}